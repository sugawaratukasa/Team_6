//=============================================================================
// �d�C���̌��I�u�W�F�N�g [item_object_electrical_room_key.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Nikaido Taichi
//=============================================================================
#include "item_object_electrical_room_key.h"
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
CElectricalRoomKeyObject::CElectricalRoomKeyObject(PRIORITY Priority)
{
	m_pParticleEmitter = nullptr;
}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CElectricalRoomKeyObject::~CElectricalRoomKeyObject()
{
}

//=============================================================================
// ���������֐�
// Author : Nikaido Taichi
//=============================================================================
CElectricalRoomKeyObject * CElectricalRoomKeyObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CElectricalRoomKeyObject�̃|�C���^
	CElectricalRoomKeyObject *pElectricalRoomKeyObject = nullptr;

	// nullcheck
	if (pElectricalRoomKeyObject == nullptr)
	{
		// �������m��
		pElectricalRoomKeyObject = new CElectricalRoomKeyObject;

		// !nullcheck
		if (pElectricalRoomKeyObject != nullptr)
		{
			// ����������
			pElectricalRoomKeyObject->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pElectricalRoomKeyObject;
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CElectricalRoomKeyObject::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �^�C�v�ݒ�
	SetType(ITEM_OBJECT_KEY_ELECTRICAL_ROOM);
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
void CElectricalRoomKeyObject::Uninit(void)
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
void CElectricalRoomKeyObject::Update(void)
{
	// �X�V����
	CItemObject::Update();
}

//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CElectricalRoomKeyObject::Draw(void)
{
	// �`�揈��
	CItemObject::Draw();
}
