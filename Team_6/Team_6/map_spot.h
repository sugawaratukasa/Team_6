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
	struct NODE
	{
		int nNumber;		//スポットの番号
		D3DXVECTOR3 pos;	//スポットの位置
	};

	//=========================================================================
	//ネクストの構造体
	//=========================================================================
	struct NEXT
	{
		int nNumber;		//ネクストの番号
		float fLength;	//ネクストまでの長さ
	};

	//=========================================================================
	//スポットデータの構造体
	//=========================================================================
	struct SPOT
	{
		NODE node;			//スポット
		vector<NEXT> vNext;	//通行可能なネクスト
	};

	//=========================================================================
	//巡回データの構造体
	//=========================================================================
	struct PATROL_DATA
	{
		vector<int> vnNumber;		//スポット番号
		MAP_AREA eArea;				//マップのエリア属性
	};

	//=========================================================================
	//メンバ関数宣言
	//=========================================================================
	CMapSpot();	//コンストラクタ
	~CMapSpot();	//デストラクタ

	static CMapSpot *Create(void);	//クリエイト処理

	static void LoadSpot(void);	//ファイル読み込み処理

protected:
	NODE SearchNearNode(const MAP_AREA eArea,const D3DXVECTOR3 pos);	//最も近いスポットの検索
	NEXT SearchNearNext(const MAP_AREA eArea, const int nSearchNumber, const int nExclusionNumber);
	//ゲッター
	SPOT GetSpot(const MAP_AREA eArea, const int nSpotNumber) { return m_vaSpot[eArea].at(nSpotNumber); }						//スポットデータの取得
	NODE GetNode(const MAP_AREA eArea, const int nSpotNumber) { return m_vaSpot[eArea].at(nSpotNumber).node; }					//スポットが持つノードの取得
	vector<NEXT> GetNextList(const MAP_AREA eArea, const int nSpotNumber) { return m_vaSpot[eArea].at(nSpotNumber).vNext; }		//スポットが持つネクストの取得
	D3DXVECTOR3 GetNodePos(const MAP_AREA eArea, const int nSpotNumber) { return m_vaSpot[eArea].at(nSpotNumber).node.pos; }	//スポットの位置の取得
	PATROL_DATA GetPatrolData(const int nJailer) { return m_aPatrolData[nJailer]; }												//看守の巡回データの取得
	
private:
	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	static vector<SPOT> m_vaSpot[MAP_AREA_MAX];	//スポットデータ
	static PATROL_DATA m_aPatrolData[4];				//看守のスポットデータ

};
#endif // !_SPOT_H_
