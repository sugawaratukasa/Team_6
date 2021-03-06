#ifndef _ITEM_H_
#define _ITEM_H_
//=============================================================================
//
// アイテム効果 [item.h]
// Author : Nikaido Taichi
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "player.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// 前方宣言
//=============================================================================

//=============================================================================
// プレイヤークラス
//=============================================================================
class CItem
{
public:
	CItem();
	virtual ~CItem();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void ItemCreate(int nPlayer) = 0;
	virtual void DuctPass(D3DXVECTOR3 pos) = 0;
	void SetPlayerItemGetList(CPlayer::ITEM_GET_LIST PlayerItemGetList){ m_ItemType  = PlayerItemGetList;}
	CPlayer::ITEM_GET_LIST GetItemType(void) { return m_ItemType; }
private:
	CPlayer::ITEM_GET_LIST m_ItemType;
};
#endif
