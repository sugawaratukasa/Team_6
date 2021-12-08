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
	m_vPatrolSpot.clear();
	m_nJailerNumber = ZERO_INT;
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
		PATROL_SPOT patrolSpot;

		//スポットの番号を保存
		patrolSpot.nNumber = *itrJaier;

		//スポットの番号に対応した位置を取得
		patrolSpot.pos = GetNodePos(m_eArea, patrolSpot.nNumber);

		//データ追加
		m_vPatrolSpot.push_back(patrolSpot);

		CSpotPolygon *pPolygon = CSpotPolygon::Create(patrolSpot.pos, patrolSpot.nNumber);

		m_pPolygon.push_back(pPolygon);
	}
}

//=============================================================================
//更新処理
//=============================================================================
void CJailerSpot::Update(void)
{
	CDebugProc::Print("前回のインデックス:%d\n", m_nOldIndex);
	CDebugProc::Print("今回のインデックス:%d\n", m_nIndex);

	if (m_pPolygon.at(m_nIndex))
	{
		m_pPolygon.at(m_nIndex)->SetFlashing();
	}
}

//=============================================================================
//ルートの検索
//=============================================================================
D3DXVECTOR3 CJailerSpot::SearchRoute(D3DXVECTOR3 jailerPos, D3DXVECTOR3 playerPos)
{
	//看守の位置に一番近いスポットを検索
	NODE jailerSpot = SearchNearNode(m_eArea, jailerPos);

	//プレイヤーの位置に一番近いスポットを検索
	NODE playerSpot = SearchNearNode(m_eArea, playerPos);

	return playerSpot.pos;
}

//=============================================================================
//ルートへ帰還
//=============================================================================
D3DXVECTOR3 CJailerSpot::BackToRoute(D3DXVECTOR3 jailerPos)
{
	//看守の位置に一番近いスポットを検索
	NODE nearSpot = SearchNearNode(m_eArea, jailerPos);
	SearchTest(nearSpot);
	


	//一番近い巡回ルートの位置を割り出す
	NODE nearPatrolSpot = SearchNearPatrolSpot(jailerPos);

	//近いスポットと近い巡回ルートの番号が同じだった場合
	if (nearSpot.nNumber == nearPatrolSpot.nNumber)
	{
		int nCntIndex = ZERO_INT;

		//サイズを取得
		int nSize = m_vPatrolSpot.size();

		//巡回ルートの中から検出したものと同じナンバーのものを探す
		for (nCntIndex = ZERO_INT; nCntIndex < nSize; nCntIndex++)
		{
			if (m_vPatrolSpot[nCntIndex].nNumber == nearPatrolSpot.nNumber)
			{
				break;
			}
		}

		m_nOldIndex = m_nIndex;

		//検索した配列番号を保存
		m_nIndex = nCntIndex;
	}
	else
	{

	}

	return nearPatrolSpot.pos;
}

void CJailerSpot::SearchTest(const NODE node)
{
	vector<NODE> vRetrunRute;

	//巡回ルートの要素数の取得
	int nSize = m_vPatrolSpot.size();
	int nNextNumOld = 0;
	//開始地点とする
	vRetrunRute.push_back(node);
	
	//現在ノードとして保存
	NODE nowNode = node;
	nNextNumOld = nowNode.nNumber;

	while (1)
	{
		for (int nCntSize = ZERO_INT; nCntSize < nSize; nCntSize)
		{
			//現在ノードと比較
			if (m_vPatrolSpot[nCntSize].nNumber == nowNode.nNumber)
			{
				return;
			}
		}

		//現在ノードからネクストの取得
		vector<NEXT> vNext = GetNextList(m_eArea, nowNode.nNumber);

		//ネクストの要素数の取得
		int nNextSize = vNext.size();

		//要素が一つのみの場合
		if (nNextSize == 1)
		{
			//該当のノード情報を取得
			NODE nodeGet = GetNode(m_eArea, vNext.at(0).nNumber);

			//地点を追加する
			vRetrunRute.push_back(nodeGet);

			//前回ノードの番号を保存
			nNextNumOld = nowNode.nNumber;

			//現在ノードを更新
			nowNode = nodeGet;

			
		}
		//要素が複数ある場合
		else
		{
			//現在ノードが持つネクストの中から一番近いネクストを取得。
			NEXT KeepNext = SearchNearNext(m_eArea, nowNode.nNumber, nNextNumOld);

			NODE nodeGet = GetNode(m_eArea, KeepNext.nNumber);

			//地点を追加する
			vRetrunRute.push_back(nodeGet);

			//前回ノードの番号を保存
			nNextNumOld = nowNode.nNumber;

			//現在ノードを更新
			nowNode = nodeGet;
		}	
	}
}

//=============================================================================
//一番近い巡回スポットを求める
//=============================================================================
CJailerSpot::PATROL_SPOT CJailerSpot::SearchNearPatrolSpot(D3DXVECTOR3 jailerPos)
{
	NODE returnInfo;	//返すスポット情報

	float fKeepRange = ZERO_FLOAT;

	int nSize = m_vPatrolSpot.size();

	for (int nCntNum = ZERO_INT; nCntNum < nSize; nCntNum++)
	{
		//現在地(看守の位置)と目的地（スポットの位置）までの2点間ベクトルを計算
		D3DXVECTOR3 Distance = m_vPatrolSpot.at(nCntNum).pos - jailerPos;

		//長さを求める
		float fRange = sqrtf((Distance.x * Distance.x) + (Distance.z * Distance.z));

		//初めの計算の時はそのまま記録
		if (nCntNum == ZERO_INT)
		{
			fKeepRange = fRange;
			returnInfo = m_vPatrolSpot.at(nCntNum);
		}
		else
		{
			//現在の距離がすでに保存している距離より短いなら
			if (fRange < fKeepRange)
			{
				//データを更新
				fKeepRange = fRange;
				returnInfo = m_vPatrolSpot.at(nCntNum);
			}
		}
	}
	
	return returnInfo;
}

//=============================================================================
//巡回スポットの変更処理
//=============================================================================
D3DXVECTOR3 CJailerSpot::ChangePatrolSpot(void)
{
	//前回番号を保存
	m_nOldIndex = m_nIndex;

	//スポットのサイズを取得
	int nSpotNum = m_vPatrolSpot.size();
	
	//インデックスを1つ進める
	m_nIndex++;

	//インデックスが要素数より大きくなったときは修正
	if (m_nIndex >= nSpotNum)
	{
		//最初に戻す
		m_nIndex = ZERO_INT;
	}
	
	return m_vPatrolSpot[m_nIndex].pos;
}
