#ifndef _CHARACTER_COLLISION_BOX_H_
#define _CHARACTER_COLLISION_BOX_H_
//=============================================================================
// �L�����N�^�[�����蔻��`�F�b�N�p�� [character_collision_box.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "character.h"
#include "model.h"

//=============================================================================
// ���N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CCharacterCollisionBox : public CModel
{
public:
	CCharacterCollisionBox(PRIORITY Priority = PRIORITY_CHARACTER);										// �R���X�g���N�^
	~CCharacterCollisionBox();																			// �f�X�g���N�^
	static CCharacterCollisionBox *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CCharacter *pCharacter);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);												// ����������
	void Uninit(void);																			// �I������
	void Update(void);																			// �X�V����
	void Draw(void);																			// �`�揈��
private:
	CCharacter *m_pCharacter;		// CCharacter�̃|�C���^
};
#endif