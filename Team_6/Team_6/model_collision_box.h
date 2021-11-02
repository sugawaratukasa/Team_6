#ifndef _MODEL_COLLISION_BOX_H_
#define _MODEL_COLLISION_BOX_H_
//=============================================================================
// ���f���Փ˃`�F�b�N�p�� [model_collision_box.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//============================================================================="
#include "model.h"

//=============================================================================
// ���N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CModelCollisionBox : public CModel
{
public:
	CModelCollisionBox(PRIORITY Priority = PRIORITY_CHARACTER);									// �R���X�g���N�^
	~CModelCollisionBox();																		// �f�X�g���N�^
	static CModelCollisionBox *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel *pModel);		// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);										// ����������
	void Uninit(void);																	// �I������
	void Update(void);																	// �X�V����
	void Draw(void);																	// �`�揈��
private:
	CModel *m_pModel;																// CCharacter�̃|�C���^
};
#endif
