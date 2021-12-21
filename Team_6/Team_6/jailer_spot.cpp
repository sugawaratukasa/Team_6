//=============================================================================
//
// 看守スポットクラス [jailer_spot.cpp]
// Author : Yamada Ryota
//
//=============================================================================
#include "jailer_spot.h"
#include "debug_proc.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CJailerSpot::CJailerSpot()
{
	m_eArea = MAP_AREA_LEFT;
	m_vPatrolRoute.clear();
	m_vRetrunRoute.clear();
	m_nJailerNumber = ZERO_INT;
	m_nRetrunIndex = ZERO_INT;
	m_nIndex = ZERO_INT;
}

//=============================================================================
//デストラクタ
//=============================================================================
CJailerSpot::~CJailerSpot()
{
}


//=============================================================================
//クリエイト処理
//=============================================================================
CJailerSpot * CJailerSpot::Create(const int nJaierNumber)
{
	CJailerSpot *pJailerSpot = nullptr;

	//インスタンス生成
	pJailerSpot = new CJailerSpot;

	if (pJailerSpot)
	{
		//初期化処理
		pJailerSpot->Init(nJaierNumber);

		return pJailerSpot;
	}

	return nullptr;
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CJailerSpot::Init(const int nJaierNumber)
{
	//看守番号を保存
	m_nJailerNumber = nJaierNumber;

	//パトロールデータの初期化
	InitializePatrolSpot();

	return S_OK;
}

//=============================================================================
//各種データの初期化
//=============================================================================
void CJailerSpot::InitializePatrolSpot(void)
{
	//自分の巡回データを取得
	PATROL_DATA patrolData = GetPatrolData(m_nJailerNumber);

	//エリア情報を保存
	m_eArea = patrolData.eArea;

	//イテレーターを取得
	auto itrJaier = patrolData.vnNumber.begin();
	auto itrJaierEnd = patrolData.vnNumber.end();

	for (itrJaier; itrJaier != itrJaierEnd; ++itrJaier)
	{
		PATROL_ROUTE patrolSpot;

		//スポットの番号を保存
		patrolSpot.node.nNumber = itrJaier->nNumber;

		patrolSpot.bGuard = itrJaier->bGuard;
		
		//部屋タイプの取得
		patrolSpot.eRoom = GetRoomType(m_eArea, patrolSpot.node.nNumber);

		//スポットの番号に対応した位置を取得
		patrolSpot.node.pos = GetNodePos(m_eArea, patrolSpot.node.nNumber);

		//データ追加
		m_vPatrolRoute.push_back(patrolSpot);

#ifdef _DEBUG
		//スポットのポリゴンを作成
		CSpotPolygon *pPolygon = CSpotPolygon::Create(patrolSpot.node.pos, patrolSpot.node.nNumber);

		m_pPolygon.push_back(pPolygon);
#endif // !_DEBUG
	}
}

//=============================================================================
//更新処理
//=============================================================================
void CJailerSpot::Update(void)
{
#ifdef _DEBUG

	CDebugProc::Print("前回のインデックス:%d\n", m_nOldIndex);
	CDebugProc::Print("今回のインデックス:%d\n", m_nIndex);

	if (m_pPolygon.at(m_nIndex))
	{
		m_pPolygon.at(m_nIndex)->SetFlashing();
	}

#endif // !_DEBUG
}

//=============================================================================
//巡回ルートへ帰還するための移動ルート検索
//=============================================================================
D3DXVECTOR3 CJailerSpot::SearchBackToRoute(const D3DXVECTOR3 jailerPos)
{
	m_vRetrunRoute.clear();
	m_nRetrunIndex = 0;

	//看守の位置に一番近いスポットを検索
	NODE nearSpot = SearchNearNode(m_eArea, jailerPos);

	//看守の位置に一番近い巡回スポットを検索
	NODE nearPatrol = SearchNearPatrolNode(jailerPos);

	//ルートを検索する
	m_vRetrunRoute = PathSearch(m_eArea, nearSpot, nearPatrol);

	return m_vRetrunRoute.at(m_nRetrunIndex).pos;
}

//=============================================================================
//一番近い巡回スポットを求める
//=============================================================================
CJailerSpot::NODE CJailerSpot::SearchNearPatrolNode(D3DXVECTOR3 jailerPos)
{
	NODE returnInfo;	//返すスポット情報

	float fKeepRange = ZERO_FLOAT;

	int nSize = m_vPatrolRoute.size();

	for (int nCntNum = ZERO_INT; nCntNum < nSize; nCntNum++)
	{
		//部屋が到達可能かどうか知らべる
		bool bIsRoomOpen = GetIsOpenRoom(m_eArea, m_vPatrolRoute.at(nCntNum).eRoom);

		//到達が不可能
		if (bIsRoomOpen == false)
		{
			continue;
		}

		//現在地(看守の位置)と目的地（スポットの位置）までの2点間ベクトルを計算
		D3DXVECTOR3 Distance = m_vPatrolRoute.at(nCntNum).node.pos - jailerPos;

		//長さを求める
		float fRange = sqrtf((Distance.x * Distance.x) + (Distance.z * Distance.z));

		//初めの計算の時はそのまま記録
		if (nCntNum == ZERO_INT)
		{
			fKeepRange = fRange;
			returnInfo = m_vPatrolRoute.at(nCntNum).node;
		}
		else
		{
			//現在の距離がすでに保存している距離より短いなら
			if (fRange < fKeepRange)
			{
				//データを更新
				fKeepRange = fRange;
				returnInfo = m_vPatrolRoute.at(nCntNum).node;
			}
		}
	}
	
	return returnInfo;
}

//=============================================================================
//巡回スポットの変更処理
//=============================================================================
D3DXVECTOR3 CJailerSpot::ChangePatrolRoute(void)
{
	//前回番号を保存
	m_nOldIndex = m_nIndex;

	//スポットのサイズを取得
	int nSpotNum = m_vPatrolRoute.size();
	
	bool bIsOpenRoom = false;

	//未開放の部屋だった場合、解放済みの部屋になるまで繰り返す
	while (bIsOpenRoom == false)
	{
		//インデックスを1つ進める
		m_nIndex++;

		//インデックスが要素数より大きくなったときは修正
		if (m_nIndex >= nSpotNum)
		{
			//最初に戻す
			m_nIndex = ZERO_INT;
		}

		//部屋が到達可能かどうか知らべる
		bIsOpenRoom = GetIsOpenRoom(m_eArea, m_vPatrolRoute.at(m_nIndex).eRoom);
	}

	return m_vPatrolRoute.at(m_nIndex).node.pos;
}

//=============================================================================
//帰還ルートのインデックス変更
//=============================================================================
D3DXVECTOR3 CJailerSpot::ChangeBackToRoute(void)
{
	//スポットのサイズを取得
	int nSpotNum = m_vRetrunRoute.size();

	//インデックスを1つ進める
	m_nRetrunIndex++;

	//インデックスが要素数より大きくなったときは修正
	if (m_nRetrunIndex >= nSpotNum)
	{
		int nCntIndex = 0;

		//帰還ルートの最後のスポットの番号が、巡回ルートのどこの番号か探す。
		for (int nCnt0 = 0; nCnt0 < (int)m_vPatrolRoute.size(); nCnt0++)
		{
			if (m_vPatrolRoute.at(nCnt0).node.nNumber == m_vRetrunRoute.at(m_nRetrunIndex - 1).nNumber)
			{
				m_nIndex = nCntIndex;

				break;
			}

			nCntIndex++;
		}
		return ZeroVector3;
	}

	return m_vRetrunRoute.at(m_nRetrunIndex).pos;
}
