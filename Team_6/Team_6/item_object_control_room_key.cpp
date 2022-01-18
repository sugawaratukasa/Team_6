//=============================================================================
// ���䎺�̌��I�u�W�F�N�g [item_object_control_room_key.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Nikaido Taichi
//=============================================================================
#include "item_object_control_room_key.h"
#include "manager.h"
#include "resource_manager.h"
#include "particle_manager.h"
#include "particle_emitter.h"

//=============================================================================
// �}�N����`
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CControlRoomKeyObject::CControlRoomKeyObject(PRIORITY Priority)
{
	m_pParticleEmitter = nullptr;
}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CControlRoomKeyObject::~CControlRoomKeyObject()
{
}

//=============================================================================
// ���������֐�
// Author : Nikaido Taichi
//=============================================================================
CControlRoomKeyObject * CControlRoomKeyObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CControlRoomKeyObject�̃|�C���^
	CControlRoomKeyObject *pControlRoomKeyObject = nullptr;

	// nullcheck
	if (pControlRoomKeyObject == nullptr)
	{
		// �������m��
		pControlRoomKeyObject = new CControlRoomKeyObject;

		// !nullcheck
		if (pControlRoomKeyObject != nullptr)
		{
			// ����������
			pControlRoomKeyObject->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pControlRoomKeyObject;
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CControlRoomKeyObject::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �^�C�v�ݒ�
	SetType(ITEM_OBJECT_KEY_CONTOROL_ROOM);
	if (m_pParticleEmitter == nullptr)
	{
		m_pParticleEmitter = CParticle_Emitter::Create(pos, CParticle_Manager::TYPE_ITEM_GOLD);
	}
	// ����������
	CItemObject::Init(pos, ZeroVector3);
	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CControlRoomKeyObject::Uninit(void)
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
void CControlRoomKeyObject::Update(void)
{
	// �X�V����
	CItemObject::Update();
}

//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CControlRoomKeyObject::Draw(void)
{
	// �`�揈��
	CItemObject::Draw();
}
