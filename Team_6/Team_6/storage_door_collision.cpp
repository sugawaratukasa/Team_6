//=============================================================================
// �Ŏ玺�h�A�̔��� [guards_door_collision.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "storage_door_collision.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(120.0f,450.0f,120.0f))	// �T�C�Y
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CStorage_Door_Collision::CStorage_Door_Collision(PRIORITY Priority) : CDoor_Collision(Priority)
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CStorage_Door_Collision::~CStorage_Door_Collision()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CStorage_Door_Collision * CStorage_Door_Collision::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CDoor *pDoor)
{
	// CStorage_Door_Collision�̃|�C���^
	CStorage_Door_Collision *pControl_Room_Door_Collision = nullptr;

	// nullcheck
	if (pControl_Room_Door_Collision == nullptr)
	{
		// �������m��
		pControl_Room_Door_Collision = new CStorage_Door_Collision;

		// !nullcheck
		if (pControl_Room_Door_Collision != nullptr)
		{
			// ����������
			pControl_Room_Door_Collision->Init(pos, rot);

			// �|�C���^����
			pControl_Room_Door_Collision->SetpDoor(pDoor);
		}
	}
	// �|�C���^��Ԃ�
	return pControl_Room_Door_Collision;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CStorage_Door_Collision::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ����������
	CDoor_Collision::Init(pos, rot);

	// �^�C�v�ݒ�
	SetType(TYPE_STORAGE);

	// �T�C�Y�ݒ�
	SetSize(COLLISION_SIZE);
	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CStorage_Door_Collision::Uninit(void)
{
	// �I������
	CDoor_Collision::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CStorage_Door_Collision::Update(void)
{
	// �X�V����
	CDoor_Collision::Update();

	// CDoor�̃|�C���^�擾
	CDoor *pDoor = GetpDoor();

	// ���b�N��Ԑݒ�
	SetLock(pDoor->GetLock());
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CStorage_Door_Collision::Draw(void)
{
}