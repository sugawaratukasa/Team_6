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
#include <list>
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

	enum A_STAR_STATE
	{
		A_STAR_STATE_NONE = 0,
		A_STAR_STATE_OPEN,
		A_STAR_STATE_CLOSE,
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
	
	struct A_STAR_COST
	{
		float fStratToNow;	//スタートからここまでのコスト(g*(n))
		float fHeuristic;	//ここからゴールまでのコスト(h*(n))
		float fTotal;		//推定最短コスト(f*(n))
	};
	struct A_SPOT
	{
		A_STAR_STATE state;
		NODE node;
		int nParentNumber;		//親の番号
		A_STAR_COST cost;
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
	vector<NODE> PathSearch(const MAP_AREA eArea, const NODE startNode, const NODE goalNode);	//経路探索

	//protectedゲッター
	SPOT GetSpot(const MAP_AREA eArea, const int nSpotNumber) { return m_vaSpot[eArea].at(nSpotNumber); }						//スポットデータの取得
	NODE GetNode(const MAP_AREA eArea, const int nSpotNumber) { return m_vaSpot[eArea].at(nSpotNumber).node; }					//スポットが持つノードの取得
	vector<NEXT> GetNextList(const MAP_AREA eArea, const int nSpotNumber) { return m_vaSpot[eArea].at(nSpotNumber).vNext; }		//スポットが持つネクストの取得
	D3DXVECTOR3 GetNodePos(const MAP_AREA eArea, const int nSpotNumber) { return m_vaSpot[eArea].at(nSpotNumber).node.pos; }	//スポットの位置の取得
	PATROL_DATA GetPatrolData(const int nJailer) { return m_aPatrolData[nJailer]; }												//看守の巡回データの取得
	
private:
	float CalculationDistance(const D3DXVECTOR3 StartPoint, const D3DXVECTOR3 EndPoint);	//距離の計算
	int CountOpenList(vector<A_SPOT>& rvSpot);												//オープンリストの計算
	int SearchMinTotal(vector<A_SPOT>& rvSpot, const NODE startNode, const NODE goalNode);	//トータルの最小のものを探す
	void DeletCloseList(const int nNum);													//クローズリストから削除

	//privateゲッター
	int GetOpenNum(void) { return (int)m_vOpenList.size(); }

	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	static vector<SPOT> m_vaSpot[MAP_AREA_MAX];	//スポットデータ
	static PATROL_DATA m_aPatrolData[4];	//看守のスポットデータ
	vector<A_SPOT>  m_vOpenList;
	list<A_SPOT> m_CloseList;
};
#endif // !_SPOT_H_
