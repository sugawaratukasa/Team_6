#ifndef _OBJECT_DUCT_WALL_H_
#define _OBJECT_DUCT_WALL_H_
//=============================================================================
// ダクト [object_duct_wall.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// ドア用の壁クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CDuct_Wall : public CObject
{
public:
	CDuct_Wall(PRIORITY Priority = PRIORITY_MAP);				// コンストラクタ
	~CDuct_Wall();												// デストラクタ
	static CDuct_Wall*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理
private:
};
#endif