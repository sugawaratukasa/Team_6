#ifndef _UI_PLAYER2_ITEM_H_
#define _UI_PLAYER2_ITEM_H_
//=============================================================================
//
// �v���C���[2�A�C�e��UI [ui_player2_item.h]
// Author : Nikaido Taichi
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "ui_player_item.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;
class CSelectItemFlame;

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CPlayer2ItemUI :public CPlayerItemUI
{
public:
	CPlayer2ItemUI();												// �R���X�g���N�^
	~CPlayer2ItemUI();												// �f�X�g���N�^
	static CPlayer2ItemUI * Create(void);							// ��������
	HRESULT Init(void);											// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �v���C���[�̐���
private:
	void PlayerItemGet(void);									// ���͏���
	void ItemGetGuideUICreate(void);							// UI��������
	int m_nItemTextureCount;									// �A�C�e���e�N�X�`��������
	int m_nSelectCount;											// �A�C�e���I���̃J�E���g
	CSelectItemFlame * m_pSelectItemFlame;						// �A�C�e���I��g�̃|�C���^
	CScene2D * m_apItemTexture[CItemObject::ITEM_OBJECT_MAX];	// �A�C�e���e�N�X�`���̃|�C���^
};
#endif
