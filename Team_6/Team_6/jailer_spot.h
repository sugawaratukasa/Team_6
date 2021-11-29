#ifndef _JAILER_SPOT_H_
#define _JAILER_SPOT_H_

#include "map_spot.h"

class CJailerSpot :public CMapSpot
{
public:
	typedef SPOT_INFO MOVE_SPOT;

	CJailerSpot();
	~CJailerSpot();

	static CJailerSpot *Create(const int nJaierNumber);
	
	D3DXVECTOR3 RouteSearch(D3DXVECTOR3 jailerPos, D3DXVECTOR3 playerPos);
	D3DXVECTOR3 BackToRoute(D3DXVECTOR3 jailerPos);

	MOVE_SPOT ClosestSpotSearchJailer(D3DXVECTOR3 jailerPos);
private:
	HRESULT Init(const int nJaierNumber);

	void InitData();
	
public:
	D3DXVECTOR3 ChangeTarget(void);

	MAP_AREA GetArea(void) { return m_eArea; }							//エリアの取得
	vector<MOVE_SPOT> GetMoveSpotList(void) { return m_vMoveSpot; }		//ムーブリストの取得
	int GetSpotNum(void) { return m_vMoveSpot[m_nIndex].nNumber; }		//現在の目的地の番号を取得
	D3DXVECTOR3 GetSpotPos(void) { return m_vMoveSpot[m_nIndex].pos; }	//現在の目的地の位置を取得

private:
	MAP_AREA m_eArea;				//担当エリア
	vector<MOVE_SPOT> m_vMoveSpot;	//移動可能な位置
	vector<MOVE_SPOT> m_vRoute;
	int m_nJailerNumber;			//看守番号
	int m_nIndex;					//インデックス
};
#endif // !_JAILER_SPOT_H_
