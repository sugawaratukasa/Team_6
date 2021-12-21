//=============================================================================
// �S���̔��� [prison_door_collision.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "object_switch_collision.h"
#include "object_switch.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(120.0f,450.0f,120.0f))	// �T�C�Y
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CSwitch_Collision::CSwitch_Collision(PRIORITY Priority) : CDoor_Collision(Priority)
{
	m_pSwitch = nullptr;
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CSwitch_Collision::~CSwitch_Collision()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CSwitch_Collision * CSwitch_Collision::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CSwitch *pSwitch)
{
	// CSwitch_Collision�̃|�C���^
	CSwitch_Collision *pSwitch_Collision = nullptr;

	// nullcheck
	if (pSwitch_Collision == nullptr)
	{
		// �������m��
		pSwitch_Collision = new CSwitch_Collision;

		// !nullcheck
		if (pSwitch_Collision != nullptr)
		{
			// ����������
			pSwitch_Collision->Init(pos, rot);

			// �|�C���^����
			pSwitch_Collision->m_pSwitch = pSwitch;
		}
	}
	// �|�C���^��Ԃ�
	return pSwitch_Collision;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CSwitch_Collision::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ����������
	CDoor_Collision::Init(pos, rot);

	// �^�C�v�ݒ�
	SetType(TYPE_SWITCH);

	SetSize(COLLISION_SIZE);
	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CSwitch_Collision::Uninit(void)
{
	// �I������
	CDoor_Collision::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CSwitch_Collision::Update(void)
{
	// �X�V����
	CDoor_Collision::Update();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CSwitch_Collision::Draw(void)
{
}
//=============================================================================
// �Ɩ[�̃h�A���J��
// Author : Sugawara Tsukasa
//=============================================================================
void CSwitch_Collision::Open(void)
{
	// !nullcheck
	if (m_pSwitch != nullptr)
	{
		// �{�^������������
		m_pSwitch->Push();
	}
}
