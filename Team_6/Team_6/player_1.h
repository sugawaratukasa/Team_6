#ifndef _PLAYER_1_H_
#define _PLAYER_1_H_
//=============================================================================
//
// �v���C���[1 [player_1.h]
// Author : Nikaido Taichi
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "player.h"

//=============================================================================
// �O���錾
//=============================================================================
class CPlayer1ItemUI;
class CScene2D;
class CGuidBG;
class CBlackTexture;
class CCaveatBar;
//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CPlayer1 : public CPlayer
{
public:
	CPlayer1(PRIORITY Priority = PRIORITY_CHARACTER);				// �R���X�g���N�^
	~CPlayer1();													// �f�X�g���N�^
	static CPlayer1*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		// �N���G�C�g
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �v���C���[�̐���
	void Draw(void);												// �`�揈��
	void PrisonWarp(void);											// �Ɩ[���[�v����
	void SetbGuidCreate(CItemObject::ITEM_OBJECT_LIST Type);
private:
	void KeyboardMove(float fSpeed, float fAngle);					// �L�[�{�[�h�ړ�����
	void PadMove(float fSpeed, float fAngle);						// �W���C�p�b�h�ړ�����
	void UpdateRot(void);											// �����X�V����
	bool m_bBlackTextureCreate;										// ���w�i�̃e�N�X�`���������
	D3DXVECTOR3 m_rotDest;								
	CScene2D * m_pItemGuidTexture;
	CGuidBG * m_pGuidBG;
	CBlackTexture * m_pBlackTexture;
	CCaveatBar * m_pCaveatBar;
};
#endif