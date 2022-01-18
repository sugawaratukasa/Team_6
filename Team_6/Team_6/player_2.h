#ifndef _PLAYER_2_H_
#define _PLAYER_2_H_
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
class CPlayer2ItemUI;
class CScene2D;
class CGuidBG;
class CBlackTexture;
class CCaveatBar;

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CPlayer2 : public CPlayer
{
public:
	CPlayer2(PRIORITY Priority = PRIORITY_CHARACTER);				// �R���X�g���N�^
	~CPlayer2();													// �f�X�g���N�^
	static CPlayer2*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		// �N���G�C�g
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �v���C���[�̐���
	void Draw(void);												// �`�揈��
	void PrisonWarp(void);											// �Ɩ[���[�v����
	void SetbGuidCreate(CItemObject::ITEM_OBJECT_LIST Type);
private:
	void InputMove(float fSpeed, float fAngle);					// �L�[�{�[�h�ړ�����
	void UpdateRot(void);											// �����X�V����
	bool m_bBlackTextureCreate;										// ���w�i�̃e�N�X�`���������
	D3DXVECTOR3 m_rotDest;
	CScene2D * m_pItemGuidTexture;
	CGuidBG * m_pGuidBG;
	CBlackTexture * m_pBlackTexture;
	CCaveatBar * m_pCaveatBar;
};
#endif