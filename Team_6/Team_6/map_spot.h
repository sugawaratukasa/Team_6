#ifndef _MAP_SPOT_H_
#define _MAP_SPOT_H_
//=============================================================================
//
// スポットクラスヘッダー [map_spot.h]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
//スポットクラス
//=============================================================================
class CMapSpot
{
public:
	enum MAP_AREA
	{
		MAP_AREA_LEFT = 0,
		MAP_AREA_RIGHT,
		MAP_AREA_MAX,
	};
	struct SPOT_INFO
	{
		int nNumber;		//スポットの番号
		D3DXVECTOR3 pos;	//スポットの位置
	};

	//=========================================================================
	//スポットデータの構造体
	//=========================================================================
	struct SPOT_DATA
	{
		SPOT_INFO info;
		vector<int> vNextNum;	//通行可能な番号
	};

	struct JAILER_INFO
	{
		vector<int> vnNumber;		//スポット番号
		MAP_AREA eArea;				//マップのエリア属性
	};

	struct DIJKSTRA
	{
		SPOT_DATA point;
		vector<float> vfCost;
	};

	//=========================================================================
	//メンバ関数宣言
	//=========================================================================
	CMapSpot();	//コンストラクタ
	~CMapSpot();	//デストラクタ

	static CMapSpot *Create(void);	//クリエイト処理

	static void LoadSpot(void);	//ファイル読み込み処理


protected:
	void InitializeDijkstra(const MAP_AREA eArea);
	SPOT_INFO ClosestSpotSearch(const MAP_AREA eArea,const D3DXVECTOR3 pos);	//最も近いスポットの検索

	void Dijkstra(const MAP_AREA eArea,SPOT_INFO Begin, SPOT_INFO end);
	SPOT_DATA GetWorldSpotData(const MAP_AREA eArea, int nNumBase);
	SPOT_INFO GetWorldSpotInfo(const MAP_AREA eArea, int nNumBase);
	D3DXVECTOR3 GetSpotWorldPos(const MAP_AREA eArea, int nNumBase);	//位置の取得
	JAILER_INFO GetJailerInfo(const int nJailer) { return m_aJailerMoveSpot[nJailer]; }
	
private:
	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	static vector<SPOT_DATA> m_vaSpotWorld[MAP_AREA_MAX];	//スポットデータ
	static JAILER_INFO m_aJailerMoveSpot[4];
	vector<DIJKSTRA> m_vDijkstra;

};
#endif // !_SPOT_H_
