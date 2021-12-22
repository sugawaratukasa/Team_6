#ifndef _UI_ITEM_GUID_H_
#define _UI_ITEM_GUID_H_
//=============================================================================
//
// �A�C�e���K�C�hUI [ui_item_guid.h]
// Author : Nikaido Taichi
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "scene_2d.h"
#include "item_object.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���錾
//=============================================================================

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CItemGuidUI
{
public:
	CItemGuidUI();						// �R���X�g���N�^
	virtual ~CItemGuidUI();				// �f�X�g���N�^
	virtual HRESULT Init(void) = 0;		// ����������
	virtual void Uninit(void) = 0;		// �I������
	virtual void Update(void) = 0;		// �X�V����
private:
};
#endif