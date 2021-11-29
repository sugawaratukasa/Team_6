#ifndef _ITEM_JAILER_ROOM_KEY_H_
#define _ITEM_JAILER_ROOM_KEY_H_
//=============================================================================
//
// 看守室のカギ効果 [item_jailer_room_key.h]
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
class CJailerRoomKey : public CItem
{
public:
	CJailerRoomKey();
	~CJailerRoomKey();
	static CJailerRoomKey * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void ItemCreate(int nPlayer);
private:
};
#endif
