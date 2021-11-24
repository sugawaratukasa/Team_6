#ifndef _ITEM_BATON_H_
#define _ITEM_BATON_H_
//=============================================================================
//
// 警棒効果 [item_baton.h]
// Author : Nikaido Taichi
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "item.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// 前方宣言
//=============================================================================

//=============================================================================
// プレイヤークラス
//=============================================================================
class CItemBaton : public CItem
{
public:
	CItemBaton();
	~CItemBaton();
	static CItemBaton * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void ItemCreate(int nPlayer);
private:
};
#endif
