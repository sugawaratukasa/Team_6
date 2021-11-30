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
	//=========================================================================
	//マップのエリア情報の列挙
	//=========================================================================
	enum MAP_AREA
	{
		MAP_AREA_LEFT = 0,
		MAP_AREA_RIGHT,
		MAP_AREA_MAX,
	};

	//=========================================================================
	//スポットの構造体
	//=========================================================================
	struct SPOT
	{
		int nNumber;		//スポットの番号
		D3DXVECTOR3 pos;	//スポットの位置
	};

	//=========================================================================
	//ネクストの構造体
	//=========================================================================
	struct NEXT
	{
		int nNum;		//ネクストの番号
		float fLength;	//ネクストまでの長さ
	};
	//=========================================================================
	//スポットデータの構造体
	//=========================================================================
	struct SPOT_DATA
	{
		SPOT spot;			//スポット
		vector<NEXT> vNext;	//通行可能な番号
	};

	//=========================================================================
	//看守の巡回スポットデータの構造体
	//=========================================================================
	struct JAILER_SPOT
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
	SPOT ClosestSpotSearch(const MAP_AREA eArea,const D3DXVECTOR3 pos);	//最も近いスポットの検索

	void Dijkstra(const MAP_AREA eArea,SPOT Begin, SPOT end);

	//ゲッター
	SPOT_DATA GetALLSpotData(const MAP_AREA eArea, const int nNumBase) { return m_vaSpotWorld[eArea].at(nNumBase); }				//スポットの全データの取得
	SPOT GetWorldSpot(const MAP_AREA eArea, const int nNumBase) { return m_vaSpotWorld[eArea].at(nNumBase).spot; }				//スポットの情報の取得
	D3DXVECTOR3 GetSpotPos(const MAP_AREA eArea, const int nNumBase) { return m_vaSpotWorld[eArea].at(nNumBase).spot.pos; }	//スポットの位置の取得
	JAILER_SPOT GetJailerInfo(const int nJailer) { return m_aJailerMoveSpot[nJailer]; }	//看守の巡回データの取得
	
private:
	
	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	static vector<SPOT_DATA> m_vaSpotWorld[MAP_AREA_MAX];	//スポットデータ
	static JAILER_SPOT m_aJailerMoveSpot[4];				//看守のスポットデータ
	vector<DIJKSTRA> m_vDijkstra;

};
#endif // !_SPOT_H_
