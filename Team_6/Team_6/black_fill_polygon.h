//=============================================================================
// 埋める用の黒いポリゴン [black_fill_polygon.h]
// Author : Sugawara Tsukasa
//=============================================================================
#ifndef _BLACK_FILL_POLYGON_H_
#define _BLACK_FILL_POLYGON_H_
//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "scene3D.h"
//=============================================================================
// マップクラス
// Author : Sugawara Tsukasa
//=============================================================================
class CBlack_Fill_Polygon : public CScene3D
{
public:
	CBlack_Fill_Polygon(PRIORITY Priority = PRIORITY_1);					// コンストラクタ
	~CBlack_Fill_Polygon();													// デストラクタ
	static CBlack_Fill_Polygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);						// 初期化処理
	void Uninit(void);														// 終了処理
	void Update(void);														// 更新処理
	void Draw(void);														// 描画処理
private:
};
#endif