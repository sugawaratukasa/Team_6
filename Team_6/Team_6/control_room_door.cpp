//=============================================================================
// ���䎺�̔� [control_room_door.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "control_room_door.h"
#include "object.h"
#include "manager.h"
#include "resource_manager.h"
#include "control_room_door_collision.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(130.0f,330.0f,25.0f))	// �T�C�Y
#define COLLISION_SIZE2	(D3DXVECTOR3(25.0f,330.0f,130.0f))	// �T�C�Y
#define ROT_90			(D3DXToRadian(89.0f))				// ����
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CControl_Room_Door::CControl_Room_Door(PRIORITY Priority)
{
}
//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CControl_Room_Door::~CControl_Room_Door()
{
}
//=============================================================================
// ���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
CControl_Room_Door * CControl_Room_Door::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CControl_Room_Door�̃|�C���^
	CControl_Room_Door *pControl_Room_Door = nullptr;

	// nullcheck
	if (pControl_Room_Door == nullptr)
	{
		// �������m��
		pControl_Room_Door = new CControl_Room_Door;

		// !nullcheck
		if (pControl_Room_Door != nullptr)
		{
			// ����������
			pControl_Room_Door->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pControl_Room_Door;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CControl_Room_Door::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_DOOR);

		// ���f���̏���n��
		BindModel(model);
	}

	// 90�ȏ�̏ꍇ
	if (rot.y >= ROT_90)
	{
		// �T�C�Y
		SetSize(COLLISION_SIZE2);
	}

	//OBB�̍쐬
	SetObb(CObb::Create(pos, rot, GetMesh()));

	// ����p�̃I�u�W�F�N�g����
	CControl_Room_Door_Collision::Create(pos, rot, this);
	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CControl_Room_Door::Uninit(void)
{
	// �h�A�̏I�������֐��Ăяo��
	CDoor::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CControl_Room_Door::Update(void)
{
	// �h�A�̍X�V�����֐��Ăяo��
	CDoor::Update();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CControl_Room_Door::Draw(void)
{
	// �h�A�̕`�揈���֐��Ăяo��
	CDoor::Draw();
}