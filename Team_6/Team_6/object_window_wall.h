#ifndef _OBJECT_WINDOW_WALL_H_
#define _OBJECT_WINDOW_WALL_H_
//=============================================================================
// 窓付き壁 [object_window_wall.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// 窓付き壁
// Author : Sugawara Tsukasa
//=============================================================================
class CWindow_Wall : public CObject
{
public:
	CWindow_Wall(PRIORITY Priority = PRIORITY_MAP);					// コンストラクタ
	~CWindow_Wall();													// デストラクタ
	static CWindow_Wall*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
private:
};
#endif#pragma once
