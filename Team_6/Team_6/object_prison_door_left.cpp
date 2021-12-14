//=============================================================================
// �S���̔� [object_prison_door_right.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "object_prison_door_left.h"
#include "object.h"
#include "manager.h"
#include "resource_manager.h"
#include "prison_door_collision.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(180.0f,450.0f,50.0f))	// �T�C�Y
#define COLLISION_SIZE2	(D3DXVECTOR3(50.0f,450.0f,180.0f))	// �T�C�Y
#define ROT_90			(D3DXToRadian(89.0f))				// ����
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CPrison_Door_Left::CPrison_Door_Left(PRIORITY Priority)
{
}
//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CPrison_Door_Left::~CPrison_Door_Left()
{
}
//=============================================================================
// ���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
CPrison_Door_Left * CPrison_Door_Left::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CPrison_Door_Left�̃|�C���^
	CPrison_Door_Left *pPrison_Door = nullptr;

	// nullcheck
	if (pPrison_Door == nullptr)
	{
		// �������m��
		pPrison_Door = new CPrison_Door_Left;

		// !nullcheck
		if (pPrison_Door != nullptr)
		{
			// ����������
			pPrison_Door->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pPrison_Door;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CPrison_Door_Left::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �h�A�̏����������֐��Ăяo��
	CDoor::Init(pos, rot);

	// �T�C�Y
	SetSize(COLLISION_SIZE);

	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f�����擾
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_PRISON_DOOR_LEFT);

		// ���f���̏���n��
		BindModel(model);
	}

	// 90�ȏ�̏ꍇ
	if (rot.y >= ROT_90)
	{
		// �T�C�Y
		SetSize(COLLISION_SIZE2);
	}

	// ����p�I�u�W�F�N�g����
	CPrison_Door_Collision::Create(pos, rot, this);
	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPrison_Door_Left::Uninit(void)
{
	// �h�A�̏I�������֐��Ăяo��
	CDoor::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPrison_Door_Left::Update(void)
{
	// �h�A�̍X�V�����֐��Ăяo��
	CDoor::Update();

	// �J�����
	Open();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPrison_Door_Left::Draw(void)
{
	// �h�A�̕`�揈���֐��Ăяo��
	CDoor::Draw();
}
