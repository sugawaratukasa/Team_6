#ifndef _OBJECT_METAL_DESK_H_
#define _OBJECT_METAL_DESK_H_
//=============================================================================
// 金属の机 [object_metal_desk.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// 金属の机クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CMetal_Desk : public CObject
{
public:
	CMetal_Desk(PRIORITY Priority = PRIORITY_MAP);					// コンストラクタ
	~CMetal_Desk();													// デストラクタ
	static CMetal_Desk*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
private:
};
#endif#pragma once
