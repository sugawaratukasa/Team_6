#ifndef _JAILER_SPOT_H_
#define _JAILER_SPOT_H_
//=============================================================================
//
// 看守スポットクラスヘッダー [jailer_spot.h]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "map_spot.h"

//=============================================================================
//看守スポットクラス
//=============================================================================
class CJailerSpot :public CMapSpot
{
public:
	struct PATROL_ROUTE
	{
		NODE node;
		ROOM_TYPE eRoom;
		bool bGuard;
	};
	//=========================================================================
	//メンバ関数宣言
	//=========================================================================
	CJailerSpot();	//コンストラクタ
	~CJailerSpot();	//デストラクタ

	static CJailerSpot *Create(const int nJaierNumber);	//クリエイト処理
	
	HRESULT Init(const int nJaierNumber);	//初期化処理
	void InitializePatrolSpot(void);		//各種データの初期化処理
	void Update(void);						//更新処理

	D3DXVECTOR3 SearchBackToRoute(const D3DXVECTOR3 jailerPos);	//帰還ルートの検索処理
	D3DXVECTOR3 SearchNoticeRoute(const D3DXVECTOR3 jailerPos,const D3DXVECTOR3 detectionPos);

	NODE SearchNearPatrolNode(D3DXVECTOR3 jailerPos);	//近い巡回スポットを求める
	D3DXVECTOR3 ChangePatrolRoute(void);				//巡回の変更処理
	D3DXVECTOR3 ChangeBackToRoute(void);				//帰還ルートの変更処理
	bool GetGarud(void) { return m_vPatrolRoute.at(m_nOldIndex).bGuard; }

	//publicゲッター
	MAP_AREA GetArea(void) { return m_eArea; }								//エリアの取得
	vector<PATROL_ROUTE> GetPatrolList(void) { return m_vPatrolRoute; }		//巡回リストの取得
	int GetSpotNumber(void) { return m_vPatrolRoute[m_nIndex].node.nNumber; }		//現在の目的地の番号を取得
	D3DXVECTOR3 GetSpotDest(void) { return m_vPatrolRoute[m_nIndex].node.pos; }	//現在の目的地の位置を取得

private:
	//=============================================================================
	//メンバ変数宣言
	//=============================================================================
	MAP_AREA m_eArea;					//担当エリア
	vector<PATROL_ROUTE> m_vPatrolRoute;	//巡回スポット情報
	vector<NODE> m_vRetrunRoute;
	int m_nJailerNumber;				//看守番号
	int m_nIndex;						//インデックス
	int m_nRetrunIndex;
	int m_nOldIndex;					//1フレーム前の目的地
};
#endif // !_JAILER_SPOT_H_
