//=============================================================================
// PC���̌��I�u�W�F�N�g [item_object.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Nikaido Taichi
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "character.h"
#include "collision.h"
#include "game.h"
#include "player.h"
#include "item_object_pc_room_key.h"

//=============================================================================
// �}�N����`
// Author : Nikaido Taichi
//=============================================================================
#define SIZE (D3DXVECTOR3(100.0f,100.0f,100.0f))

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CPCRoomKeyObject::CPCRoomKeyObject(PRIORITY Priority) : CItemObject(Priority)
{
}
//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CPCRoomKeyObject::~CPCRoomKeyObject()
{
}

//=============================================================================
// ���������֐�
// Author : Nikaido Taichi
//=============================================================================
CPCRoomKeyObject * CPCRoomKeyObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CPlayer1�̃|�C���^
	CPCRoomKeyObject *pPCRoomKeyObject = nullptr;

	// nullcheck
	if (pPCRoomKeyObject == nullptr)
	{
		// �������m��
		pPCRoomKeyObject = new CPCRoomKeyObject;

		// !nullcheck
		if (pPCRoomKeyObject != nullptr)
		{
			// ����������
			pPCRoomKeyObject->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pPCRoomKeyObject;
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CPCRoomKeyObject::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f�����擾
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_KEY_OBJECT);

		// ���f���̏���n��
		BindModel(model);
	}

	// �T�C�Y�ݒ�
	SetSize(SIZE);
	// �^�C�v�ݒ�
	SetType(ITEM_OBJECT_KEY_PC_ROOM);
	// ����������
	CItemObject::Init(pos, ZeroVector3);

	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CPCRoomKeyObject::Uninit(void)
{
	// �I������
	CItemObject::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CPCRoomKeyObject::Update(void)
{
	// �X�V����
	CItemObject::Update();
}
//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CPCRoomKeyObject::Draw(void)
{
	// �`�揈��
	CItemObject::Draw();
}