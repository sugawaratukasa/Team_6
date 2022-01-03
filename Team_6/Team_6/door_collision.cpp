//=============================================================================
// �h�A�̔��� [door_collision.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "collision.h"
#include "game.h"
#include "door_collision.h"
#include "model_collision_box.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CDoor_Collision::CDoor_Collision(PRIORITY Priority) : CModel(Priority)
{
	m_Type = TYPE_NONE;
	m_bLock = true;
	m_pDoor = nullptr;
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CDoor_Collision::~CDoor_Collision()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CDoor_Collision * CDoor_Collision::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CDoor *pDoor)
{
	// CDoor_Collision�̃|�C���^
	CDoor_Collision *pDoor_Collision = nullptr;

	// nullcheck
	if (pDoor_Collision == nullptr)
	{
		// �������m��
		pDoor_Collision = new CDoor_Collision;

		// !nullcheck
		if (pDoor_Collision != nullptr)
		{
			// ����������
			pDoor_Collision->Init(pos, rot);

			// �|�C���^����
			pDoor_Collision->m_pDoor = pDoor;
		}
	}
	// �|�C���^��Ԃ�
	return pDoor_Collision;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CDoor_Collision::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ����������
	CModel::Init(pos, rot);

	CModelCollisionBox::Create(pos, rot, this);
	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CDoor_Collision::Uninit(void)
{
	// �I������
	CModel::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CDoor_Collision::Update(void)
{
	// �X�V����
	CModel::Update();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CDoor_Collision::Draw(void)
{
}
//=============================================================================
// �����J�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CDoor_Collision::Open(int nPlayer)
{
	// !nullcheck
	if (m_pDoor != nullptr)
	{
		// �h�A���J��
		m_pDoor->SetLock(false);
	}
}
//=============================================================================
// �����J���Ȃ������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CDoor_Collision::NotOpen(int nPlayer)
{
}
