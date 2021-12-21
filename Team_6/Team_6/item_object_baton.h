#ifndef _ITEM_OBJECT_BATON_H_
#define _ITEM_OBJECT_BATON_H_
//=============================================================================
// �x�_�I�u�W�F�N�g [item_object_baton.h]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Nikaido Taichi
//=============================================================================
#include "item_object.h"

//=============================================================================
// �O���錾
// Author : Nikaido Taichi
//=============================================================================
class CParticle_Emitter;

//=============================================================================
// �x�_�I�u�W�F�N�g�N���X
// Author : Nikaido Taichi
//=============================================================================
class CBatonObject : public CItemObject
{
public:
	CBatonObject(PRIORITY Priority = PRIORITY_MODEL);		// �R���X�g���N�^
	virtual ~CBatonObject();								// �f�X�g���N�^
	static CBatonObject * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void Draw(void);										// �`�揈��
private:
	CParticle_Emitter * m_pParticleEmitter;
};
#endif