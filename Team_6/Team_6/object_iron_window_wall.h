#ifndef _OBJECT_IRON_WINDOW_WALL_H_
#define _OBJECT_IRON_WINDOW_WALL_H_
//=============================================================================
// 鉄窓の壁 [object_iron_window_wall.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// 壁クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CIronWindow_Wall : public CObject
{
public:
	CIronWindow_Wall(PRIORITY Priority = PRIORITY_MAP);					// コンストラクタ
	~CIronWindow_Wall();												// デストラクタ
	static CIronWindow_Wall*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);						// 初期化処理
	void Uninit(void);													// 終了処理
	void Update(void);													// 更新処理
	void Draw(void);													// 描画処理
private:
};
#endif