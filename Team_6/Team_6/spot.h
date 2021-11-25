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
	//=========================================================================
	//スポットデータの構造体
	//=========================================================================
	struct SPOT_DATA
	{
		D3DXVECTOR3 pos;		//位置
		vector<int> NumNext;	//通行可能な番号
	};

	struct JAILER_SPOT
	{
		vector<int> nNumber;		//スポット番号
		vector<D3DXVECTOR3> pos;	//スポットの位置
	};
	//=========================================================================
	//メンバ関数宣言
	//=========================================================================
	CSpot();	//コンストラクタ
	~CSpot();	//デストラクタ

	static CSpot *Create(void);	//クリエイト処理

	HRESULT Init(void);	//初期化処理
	void Uninit(void);
	
	//publicゲッター
	int GetSpotNum(void) { return (int)m_SpotData.size(); }									//要素数の取得
	D3DXVECTOR3 GetSpotPos(const int nNumBase) { return m_SpotData[nNumBase].pos; }			//位置の取得
	vector<int> GetNextNumber(const int nNumBase) { return m_SpotData[nNumBase].NumNext; }	//ネクストの取得

	vector<int> GetJailerSpotNumber(const int nJaierNum) { return m_JailerMoveSpot[nJaierNum].nNumber; }	//看守の移動スポットリストの取得
	vector<D3DXVECTOR3> GetJailerMoveSpotList(const int nJaierNum) { return m_JailerMoveSpot[nJaierNum].pos; }
	static void LoadSpot(void);	//ファイル読み込み処理
private:

	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	static vector<SPOT_DATA> m_SpotData;	//スポットデータ
	static JAILER_SPOT m_JailerMoveSpot[4];
	int m_nJailerNum;
};
#endif // !_SPOT_H_
