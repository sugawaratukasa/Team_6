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

	pJailerSpot = new CJailerSpot;

	if (pJailerSpot)
	{
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

void CJailerSpot::Update(void)
{
	CDebugProc::Print("前回のインデックス:%d\n", m_nOldIndex);
	CDebugProc::Print("今回のインデックス:%d\n", m_nIndex);

	if (m_pPolygon.at(m_nIndex))
	{
		m_pPolygon.at(m_nIndex)->SetFlashing();
	}
}

D3DXVECTOR3 CJailerSpot::SearchRoute(D3DXVECTOR3 jailerPos, D3DXVECTOR3 playerPos)
{
	//看守の位置に一番近いスポットを検索
	NODE jailerSpot = SearchNearNode(m_eArea, jailerPos);

	//プレイヤーの位置に一番近いスポットを検索
	NODE playerSpot = SearchNearNode(m_eArea, playerPos);


	//そのまま追跡ルートにする
	m_vRoute.push_back(playerSpot);


	return playerSpot.pos;
}

D3DXVECTOR3 CJailerSpot::BackToRoute(D3DXVECTOR3 jailerPos)
{
	//看守の位置に一番近いスポットを検索
	NODE jailerSpot = SearchNearNode(m_eArea, jailerPos);

	//一番近い巡回ルートの位置を割り出す
	NODE jailerMove = SearchNearPatrolSpot(jailerPos);

	int nCntIndex = ZERO_INT;

	auto itr = m_vPatrolSpot.begin();
	auto itrEnd = m_vPatrolSpot.end();
	
	int nSpotNum = m_vPatrolSpot.size();

	for (nCntIndex = 0; nCntIndex < nSpotNum; nCntIndex++)
	{
		if (m_vPatrolSpot[nCntIndex].nNumber == jailerMove.nNumber)
		{
			break;
		}
	}

	m_nIndex = nCntIndex;

	//設定したインデックスが前回と同じだった場合
	if (m_nIndex == m_nOldIndex)
	{
		m_nIndex++;

		//インデックスが要素数より大きくなったときは修正
		if (m_nIndex >= nSpotNum)
		{
			//最初に戻す
			m_nIndex = ZERO_INT;
		}
	}

	return jailerSpot.pos;
}

//=============================================================================
//一番近い巡回スポットを求める
//=============================================================================
CJailerSpot::PATROL_SPOT CJailerSpot::SearchNearPatrolSpot(D3DXVECTOR3 jailerPos)
{
	auto itrBase = m_vPatrolSpot.begin();
	auto itrBaseEnd = m_vPatrolSpot.end();

	NODE returnInfo;	//返すスポット情報

	int nCnt = 0;
	float fKeepRange = ZERO_FLOAT;

	for (itrBase; itrBase != itrBaseEnd; ++itrBase)
	{
		//現在地(看守の位置)と目的地（スポットの位置）までの2点間ベクトルを計算
		D3DXVECTOR3 Distance = itrBase->pos - jailerPos;

		//長さを求める
		float fRange = sqrtf((Distance.x * Distance.x) + (Distance.z * Distance.z));

		//初めの計算の時はそのまま記録
		if (nCnt == ZERO_INT)
		{
			fKeepRange = fRange;
			returnInfo = *itrBase;

			nCnt++;
		}
		else
		{
			//現在の距離がすでに保存している距離より短いなら
			if (fRange < fKeepRange)
			{
				//データを更新
				fKeepRange = fRange;
				returnInfo = *itrBase;
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
