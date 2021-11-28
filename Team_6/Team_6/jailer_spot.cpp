#include "jailer_spot.h"

CJailerSpot::CJailerSpot()
{
	m_eArea = MAP_AREA_LEFT;
	m_vMoveSpot.clear();
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

void CJailerSpot::Update(D3DXVECTOR3 pos)
{
	SPOT_INFO spot = ClosestSpotSearch(m_eArea, pos);

}

void CJailerSpot::RouteSearch(D3DXVECTOR3 jailerPos, D3DXVECTOR3 playerPos)
{
	//看守の位置に一番近いスポットを検索
	SPOT_INFO jailerSpot = ClosestSpotSearch(m_eArea, jailerPos);

	//プレイヤーの位置に一番近いスポットを検索
	SPOT_INFO playerSpot = ClosestSpotSearch(m_eArea, playerPos);
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
	JAILER_INFO jailerInfo = GetJailerInfo(m_nJailerNumber);

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
		moveSpot.pos = GetSpotWorldPos(m_eArea, moveSpot.nNumber);

		//データ保存
		m_vMoveSpot.push_back(moveSpot);
	}
}

D3DXVECTOR3 CJailerSpot::ChangeTarget(void)
{
	//スポットのサイズを取得
	int nSpotNum = m_vMoveSpot.size();
	
	//インデックスを1つ進める
	m_nIndex++;

	//インデックスが要素数より大きくなったときは修正
	if (m_nIndex >= nSpotNum)
	{
		m_nIndex = ZERO_INT;
	}
	
	return m_vMoveSpot[m_nIndex].pos;
}
