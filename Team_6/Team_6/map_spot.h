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
//マクロ定義
//=============================================================================
#define INFINITY_COST (999999.0f)	//A*Starの各ノードのデフォルトコスト
#define JAILER_NUM 6

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
		MAP_AREA_LEFT = 0,	//左側
		MAP_AREA_RIGHT,		//右側
		MAP_AREA_MAX,
	};

	//=========================================================================
	//A*のノードの状態
	//=========================================================================
	enum A_STAR_STATE
	{
		A_STAR_STATE_NONE = 0,	//どの状態にも属さない
		A_STAR_STATE_OPEN,		//Open状態
		A_STAR_STATE_CLOSE,		//Close状態
	};

	//=========================================================================
	//部屋情報の列挙
	//=========================================================================
	enum ROOM_TYPE
	{
		ROOM_TYPE_AISLE = 0,	//通路
		ROOM_TYPE_CONTROL_ROOM,	//制御室
		ROOM_TYPE_STORAGE,		//倉庫
		ROOM_TYPE_POWER_ROOM,	//電源室
		ROOM_TYPE_CAMERA_ROOM,	//カメラ室
		ROOM_TYPE_JAILER_ROOM,	//看守室
		ROOM_TYPE_MAX,
	};

	//=========================================================================
	//ノードの構造体
	//=========================================================================
	struct NODE
	{
		int nNumber;		//ノードの番号
		D3DXVECTOR3 pos;	//ノードの位置
	};

	//=========================================================================
	//ネクストの構造体
	//=========================================================================
	struct NEXT
	{
		int nNumber;	//ネクストの番号
		float fLength;	//ネクストまでの長さ
	};

	//=========================================================================
	//スポットデータの構造体
	//=========================================================================
	struct SPOT
	{
		NODE node;			//ノード
		ROOM_TYPE eRoom;	//部屋情報
		vector<NEXT> vNext;	//通行可能なネクスト
	};

	//=========================================================================
	//看守のポイント
	//=========================================================================
	struct JAILER_POINT
	{
		int nNumber;
		bool bGuard;	//警戒行動をするかどうか
	};

	//=========================================================================
	//巡回データの構造体
	//=========================================================================
	struct PATROL_DATA
	{
		vector<JAILER_POINT> vPoint;	//スポット番号
		MAP_AREA eArea;					//マップのエリア属性
	};
	
	//=========================================================================
	//A*のコストの構造体
	//=========================================================================
	struct A_STAR_COST
	{
		float fStratToNow;	//スタートからここまでのコスト(g*(n))
		float fHeuristic;	//ゴールまでのコスト(h*(n))
		float fTotal;		//推定最短コスト(f*(n))
	};

	//=========================================================================
	//巡回データの構造体
	//=========================================================================
	struct A_SPOT
	{
		A_STAR_STATE state;		//状態
		A_STAR_COST cost;		//コスト
		SPOT spot;				//スポット
		int nParentNumber;		//親の番号
	};

	//=========================================================================
	//メンバ関数宣言
	//=========================================================================
	CMapSpot();	//コンストラクタ
	~CMapSpot();	//デストラクタ

	static CMapSpot *Create(void);	//クリエイト処理

	static void LoadSpot(void);	//ファイル読み込み処理

	static void Init(void);
	static void SetIsOpenRoom(const MAP_AREA eArea, const ROOM_TYPE eRoom) { m_abIsOpenRoom[eArea][eRoom] = true; }
	static bool GetIsOpenRoom(const MAP_AREA eArea, const ROOM_TYPE eRoom) { return m_abIsOpenRoom[eArea][eRoom]; }

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
	ROOM_TYPE GetRoomType(const MAP_AREA eArea, const int nSpotNumber) { return m_vaSpot[eArea].at(nSpotNumber).eRoom; }
	bool GetGuard(const int nJailer, const int nSpotNumber) { return m_aPatrolData[nJailer].vPoint.at(nSpotNumber).bGuard; }

private:
	float CalculationDistanceLength(const D3DXVECTOR3 StartPoint, const D3DXVECTOR3 EndPoint);	//2点間ベクトルの長さの計算
	int CountOpenList(vector<A_SPOT>& rvSpot);												//オープンリストの計算
	int SearchMinTotalCostNodeNumber(vector<A_SPOT>& rvSpot, const NODE startNode, const NODE goalNode);	//トータルの最小のものを探す

	//privateゲッター
	int GetOpenNum(void) { return (int)m_vOpenList.size(); }

	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	static vector<SPOT> m_vaSpot[MAP_AREA_MAX];	//スポットデータ
	static PATROL_DATA m_aPatrolData[JAILER_NUM];	//看守のスポットデータ
	static bool m_abIsOpenRoom[MAP_AREA_MAX][ROOM_TYPE_MAX];
	vector<A_SPOT>  m_vOpenList;	//オープンリスト
};
#endif // !_SPOT_H_
