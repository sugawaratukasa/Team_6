#ifndef _OBJECT_GENERATOR_H_
#define _OBJECT_GENERATOR_H_
//=============================================================================
// 発電機 [object_generator.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// 発電機クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CGenerator : public CObject
{
public:
	CGenerator(PRIORITY Priority = PRIORITY_MAP);					// コンストラクタ
	~CGenerator();													// デストラクタ
	static CGenerator*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
private:
};
#endif#pragma once
