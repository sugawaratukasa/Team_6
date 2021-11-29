#ifndef _ITEM_PC_ROOM_KEY_H_
#define _ITEM_PC_ROOM_KEY_H_
//=============================================================================
//
// PC���̌����� [item_pc_room_key.h]
// Author : Nikaido Taichi
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "item.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���錾
//=============================================================================

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CPCRoomKey : public CItem
{
public:
	CPCRoomKey();
	~CPCRoomKey();
	static CPCRoomKey * Create(void);
	HRESULT Init(void);
	void Uninit(void);	
	void Update(void);
	void ItemCreate(int nPlayer);
private:
};
#endif