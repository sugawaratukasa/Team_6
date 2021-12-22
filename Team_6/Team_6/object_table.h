#ifndef _OBJECT_TABLE_H_
#define _OBJECT_TABLE_H_
//=============================================================================
// テーブル [object_table.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// テーブルクラス
// Author : Sugawara Tsukasa
//=============================================================================
class CTable : public CObject
{
public:
	CTable(PRIORITY Priority = PRIORITY_MAP);					// コンストラクタ
	~CTable();													// デストラクタ
	static CTable*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
private:
};
#endif#pragma once
