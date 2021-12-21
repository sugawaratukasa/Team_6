//=============================================================================
// �x�_�I�u�W�F�N�g [item_object_baton.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Nikaido Taichi
//=============================================================================
#include "item_object_baton.h"
#include "manager.h"
#include "resource_manager.h"
#include "particle_manager.h"
#include "particle_emitter.h"

//=============================================================================
// �}�N����`
// Author : Nikaido Taichi
//=============================================================================
#define SIZE (D3DXVECTOR3(100.0f,100.0f,100.0f))

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CBatonObject::CBatonObject(PRIORITY Priority)
{
	m_pParticleEmitter = nullptr;
}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CBatonObject::~CBatonObject()
{
}

//=============================================================================
// ���������֐�
// Author : Nikaido Taichi
//=============================================================================
CBatonObject * CBatonObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CJailerKeyObject�̃|�C���^
	CBatonObject *pJailerKeyObject = nullptr;

	// nullcheck
	if (pJailerKeyObject == nullptr)
	{
		// �������m��
		pJailerKeyObject = new CBatonObject;

		// !nullcheck
		if (pJailerKeyObject != nullptr)
		{
			// ����������
			pJailerKeyObject->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pJailerKeyObject;
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CBatonObject::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �^�C�v�ݒ�
	SetType(ITEM_OBJECT_BATON);
	// �T�C�Y�ݒ�
	SetSize(SIZE);
	if (m_pParticleEmitter == nullptr)
	{
		m_pParticleEmitter = CParticle_Emitter::Create(pos, CParticle_Manager::TYPE_ITEM_SILVER);
	}
	// ����������
	CItemObject::Init(pos, ZeroVector3);
	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CBatonObject::Uninit(void)
{
	if (m_pParticleEmitter != nullptr)
	{
		m_pParticleEmitter->Uninit();
	}
	// �I������
	CItemObject::Uninit();
}

//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CBatonObject::Update(void)
{
	// �X�V����
	CItemObject::Update();
}

//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CBatonObject::Draw(void)
{
	// �`�揈��
	CItemObject::Draw();
}
