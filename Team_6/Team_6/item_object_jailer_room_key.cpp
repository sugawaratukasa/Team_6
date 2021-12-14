//=============================================================================
// �Ŏ玺�̌��I�u�W�F�N�g [item_object_jailer_room_key.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Nikaido Taichi
//=============================================================================
#include "item_object_jailer_room_key.h"
#include "manager.h"
#include "resource_manager.h"

//=============================================================================
// �}�N����`
// Author : Nikaido Taichi
//=============================================================================
#define SIZE (D3DXVECTOR3(100.0f,100.0f,100.0f))

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CJailerKeyObject::CJailerKeyObject(PRIORITY Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CJailerKeyObject::~CJailerKeyObject()
{
}

//=============================================================================
// ���������֐�
// Author : Nikaido Taichi
//=============================================================================
CJailerKeyObject * CJailerKeyObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CJailerKeyObject�̃|�C���^
	CJailerKeyObject *pJailerKeyObject = nullptr;

	// nullcheck
	if (pJailerKeyObject == nullptr)
	{
		// �������m��
		pJailerKeyObject = new CJailerKeyObject;

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
HRESULT CJailerKeyObject::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �^�C�v�ݒ�
	SetType(ITEM_OBJECT_KEY_JAILER_ROOM);
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
void CJailerKeyObject::Uninit(void)
{
	// �I������
	CItemObject::Uninit();
}

//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CJailerKeyObject::Update(void)
{
	// �X�V����
	CItemObject::Update();
}

//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CJailerKeyObject::Draw(void)
{
	// �`�揈��
	CItemObject::Draw();
}
