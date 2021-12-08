#ifndef _SPOT_POLYGON_H_
#define _SPOT_POLYGON_H_
//=============================================================================
//
// スポットポリゴンヘッダー [spot_polygon.h]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "scene3d.h"

//=============================================================================
//スポットポリゴンクラス
//=============================================================================
class CSpotPolygon :public CScene3D
{
public:
	//=========================================================================
	//点滅情報の列挙
	//=========================================================================
	enum FLASHING
	{
		FLASHING_NONE = 0,	//何もしない
		FLASHING_ADD,		//加算
		FLASHING_SUB,		//減算
		FLASHING_MAX,
	};

	//=========================================================================
	//メンバ関数宣言
	//=========================================================================
	CSpotPolygon(PRIORITY Priority = PRIORITY_FADE);	//コンストラクタ
	~CSpotPolygon();									//デストラクタ

	static CSpotPolygon *Create(D3DXVECTOR3 pos, int nNumber);	//クリエイト

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//初期化処理
	void Uninit(void);									//終了処理
	void Update(void);									//更新処理
	void Draw(void);									//描画処理
	void SetFlashing(void);								//点滅開始
	void EndFlashing(void);								//点滅終了
	
	//publicセッター
	void SetIsDraw(const bool bIsDraw) { m_bIsDraw = bIsDraw; }	//描画フラグの設定
	void SetNumber(int nNumber) { m_nNumber = nNumber; }		//番号の設定

private:
	void Flasing(void);		//点滅処理

	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	FLASHING m_eFlashing;	//点滅情報
	bool m_bIsDraw;			//描画するかどうか
	int m_nNumber;			//番号
};
#endif // !_SPOT_POLYGON_H_
