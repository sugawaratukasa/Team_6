#ifndef _SPOT_H_
#define _SPOT_H_
//=============================================================================
//
// スポットクラスヘッダー [jailer.h]
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
class CSpot 
{
public:
	enum MAP_AREA
	{
		MAP_AREA_LEFT = 0,
		MAP_AREA_RIGHT,
		MAP_AREA_MAX,
	};

	//=========================================================================
	//スポットデータの構造体
	//=========================================================================
	struct SPOT_DATA
	{
		D3DXVECTOR3 pos;		//位置
		vector<int> vNextNum;	//通行可能な番号
		MAP_AREA eArea;
	};

	struct JAILER_SPOT
	{
		vector<int> vnNumber;		//スポット番号
		vector<D3DXVECTOR3> vPos;	//スポットの位置
		MAP_AREA eArea;				//マップのエリア属性
	};

	//=========================================================================
	//メンバ関数宣言
	//=========================================================================
	CSpot();	//コンストラクタ
	~CSpot();	//デストラクタ

	static CSpot *Create(void);	//クリエイト処理

	static void LoadSpot(void);	//ファイル読み込み処理
	
	void Init(const MAP_AREA eArea);

	int ClosestSpotSearch(const D3DXVECTOR3 pos);	//最も近いスポットの検索

	//publicゲッター
	int GetSpotWorldNum(void) { return (int)m_vaSpotWorld.size(); }									//要素数の取得
	D3DXVECTOR3 GetSpotWorldPos(const int nNumBase) { return m_vaSpotWorld.at(nNumBase).pos; }			//位置の取得
	vector<int> GetWorldNextNumber(const int nNumBase) { return m_vaSpotWorld.at(nNumBase).vNextNum; }	//ネクストの取得

	vector<int> GetJailerSpotNumber(const int nJaierNum) { return m_aJailerMoveSpot[nJaierNum].vnNumber; }	//看守の移動スポットリストの取得
	vector<D3DXVECTOR3> GetJailerMoveSpotList(const int nJaierNum) { return m_aJailerMoveSpot[nJaierNum].vPos; }

	//MAP_AREA GetSpotArea(const int nNumBase) { return m_vaSpotWorld[nNumBase].eArea; }			//スポットのエリア情報を取得
	MAP_AREA GetJailerArea(const int nJaierNum) { return m_aJailerMoveSpot[nJaierNum].eArea; }	//看守のエリア情報を取得
	
private:
	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	static vector<SPOT_DATA> m_vaSpotWorld;	//スポットデータ
	static JAILER_SPOT m_aJailerMoveSpot[4];
	MAP_AREA m_eArea;
};
#endif // !_SPOT_H_
