//=============================================================================
// �q�ɂ̌��I�u�W�F�N�g [item_object_storage_key.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Nikaido Taichi
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "item_object_storage_key.h"

//=============================================================================
// �}�N����`
// Author : Nikaido Taichi
//=============================================================================
#define SIZE (D3DXVECTOR3(100.0f,100.0f,100.0f))

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CStorageKeyObject::CStorageKeyObject(PRIORITY Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CStorageKeyObject::~CStorageKeyObject()
{
}

//=============================================================================
// ���������֐�
// Author : Nikaido Taichi
//=============================================================================
CStorageKeyObject * CStorageKeyObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CPrisonKeyObject�̃|�C���^
	CStorageKeyObject *pStorageKeyObject = nullptr;

	// nullcheck
	if (pStorageKeyObject == nullptr)
	{
		// �������m��
		pStorageKeyObject = new CStorageKeyObject;

		// !nullcheck
		if (pStorageKeyObject != nullptr)
		{
			// ����������
			pStorageKeyObject->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pStorageKeyObject;
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CStorageKeyObject::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �^�C�v�ݒ�
	SetType(ITEM_OBJECT_KEY_STORAGE);
	// �T�C�Y�ݒ�
	SetSize(SIZE);

	// ����������
	CItemObject::Init(pos, ZeroVector3);
	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CStorageKeyObject::Uninit(void)
{
	// �I������
	CItemObject::Uninit();
}

//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CStorageKeyObject::Update(void)
{
	// �X�V����
	CItemObject::Update();
}

//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CStorageKeyObject::Draw(void)
{
	// �`�揈��
	CItemObject::Draw();
}
