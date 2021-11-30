#include "jailer_spot.h"
#include "debug_proc.h"

CJailerSpot::CJailerSpot()
{
	m_eArea = MAP_AREA_LEFT;
	m_vSpotDest.clear();
	m_nJailerNumber = ZERO_INT;
	m_nIndex = ZERO_INT;
}

CJailerSpot::~CJailerSpot()
{
}


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

D3DXVECTOR3 CJailerSpot::RouteSearch(D3DXVECTOR3 jailerPos, D3DXVECTOR3 playerPos)
{
	//看守の位置に一番近いスポットを検索
	SPOT jailerSpot = ClosestSpotSearch(m_eArea, jailerPos);

	//プレイヤーの位置に一番近いスポットを検索
	SPOT playerSpot = ClosestSpotSearch(m_eArea, playerPos);


	//そのまま追跡ルートにする
	m_vRoute.push_back(playerSpot);

	Dijkstra(m_eArea, m_vSpotDest[m_nIndex], playerSpot);

	return playerSpot.pos;
}

D3DXVECTOR3 CJailerSpot::BackToRoute(D3DXVECTOR3 jailerPos)
{
	//看守の位置に一番近いスポットを検索
	SPOT jailerSpot = ClosestSpotSearch(m_eArea, jailerPos);

	//一番近い巡回ルートの位置を割り出す
	SPOT jailerMove = ClosestSpotSearchJailer(jailerPos);

	int nCntIndex = ZERO_INT;

	auto itr = m_vSpotDest.begin();
	auto itrEnd = m_vSpotDest.end();
	
	
	int nSpotNum = m_vSpotDest.size();

	for (nCntIndex = 0; nCntIndex < nSpotNum; nCntIndex++)
	{
		if (m_vSpotDest[nCntIndex].nNumber == jailerMove.nNumber)
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

CJailerSpot::MOVE_SPOT CJailerSpot::ClosestSpotSearchJailer(D3DXVECTOR3 jailerPos)
{
	auto itrBase = m_vSpotDest.begin();
	auto itrBaseEnd = m_vSpotDest.end();

	SPOT returnInfo;	//返すスポット情報

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

HRESULT CJailerSpot::Init(const int nJaierNumber)
{
	//看守番号を保存
	m_nJailerNumber = nJaierNumber;

	InitData();

	return S_OK;
}

void CJailerSpot::InitData()
{
	//自分の情報を取得
	JAILER_SPOT jailerInfo = GetJailerInfo(m_nJailerNumber);

	//エリア情報を保存
	m_eArea = jailerInfo.eArea;

	auto itrJaier = jailerInfo.vnNumber.begin();
	auto itrJaierEnd = jailerInfo.vnNumber.end();

	for (itrJaier; itrJaier != itrJaierEnd; ++itrJaier)
	{
		MOVE_SPOT moveSpot;

		//スポットの番号を保存
		moveSpot.nNumber = *itrJaier;

		//番号に対応した位置を取得
		moveSpot.pos = GetSpotPos(m_eArea, moveSpot.nNumber);

		//データ保存
		m_vSpotDest.push_back(moveSpot);
	}
}

D3DXVECTOR3 CJailerSpot::ChangeSpotDest(void)
{
	//前回番号を保存
	m_nOldIndex = m_nIndex;

	//スポットのサイズを取得
	int nSpotNum = m_vSpotDest.size();
	
	//インデックスを1つ進める
	m_nIndex++;

	//インデックスが要素数より大きくなったときは修正
	if (m_nIndex >= nSpotNum)
	{
		//最初に戻す
		m_nIndex = ZERO_INT;
	}
	
	return m_vSpotDest[m_nIndex].pos;
}
