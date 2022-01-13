#ifndef _OBJECT_WOOD_BOX_H_
#define _OBJECT_WOOD_BOX_H_
//=============================================================================
// 木箱 [object_wood_box.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// 木箱クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CWood_Box : public CObject
{
public:
	CWood_Box(PRIORITY Priority = PRIORITY_MAP);					// コンストラクタ
	~CWood_Box();													// デストラクタ
	static CWood_Box*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
private:
};
#endif#pragma once
