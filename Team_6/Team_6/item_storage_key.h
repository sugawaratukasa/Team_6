#ifndef _ITEM_STORAGE_KEY_H_
#define _ITEM_STORAGE_KEY_H_
//=============================================================================
//
// �q�ɂ̌����� [item_storage_key.h]
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
class CStorageKey : public CItem
{
public:
	CStorageKey();
	~CStorageKey();
	static CStorageKey * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void ItemCreate(int nPlayer);
private:
};
#endif