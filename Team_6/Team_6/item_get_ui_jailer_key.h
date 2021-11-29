#ifndef _ITEM_GET_UI_JAILER_KEY_H_
#define _ITEM_GET_UI_JAILER_KEY_H_
//=============================================================================
//
// �v���C���[UI�N���X�w�b�_�[ [item_get_ui.h]
// Author : Nikaido Taichi
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "item_get_ui.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���錾
//=============================================================================

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CItemGetUIJailerKey: public CItemGetUI
{
public:
	CItemGetUIJailerKey();														// �R���X�g���N�^
	~CItemGetUIJailerKey();														// �f�X�g���N�^
	static CItemGetUIJailerKey * Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size);		// ��������
	HRESULT Init(D3DXVECTOR3 Pos, D3DXVECTOR3 Size);							// ����������
	void Uninit(void);															// �I������
	void Draw(void);															// �`�揈��
	void Update(void);															// �v���C���[�̐���
private:
};
#endif