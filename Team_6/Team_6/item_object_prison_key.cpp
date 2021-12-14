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
#include "item_object_prison_key.h"

//=============================================================================
// �}�N����`
// Author : Nikaido Taichi
//=============================================================================
#define SIZE (D3DXVECTOR3(100.0f,100.0f,100.0f))

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CPrisonKeyObject::CPrisonKeyObject(PRIORITY Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CPrisonKeyObject::~CPrisonKeyObject()
{
}

//=============================================================================
// ���������֐�
// Author : Nikaido Taichi
//=============================================================================
CPrisonKeyObject * CPrisonKeyObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CPrisonKeyObject�̃|�C���^
	CPrisonKeyObject *pPrisonKeyObject = nullptr;

	// nullcheck
	if (pPrisonKeyObject == nullptr)
	{
		// �������m��
		pPrisonKeyObject = new CPrisonKeyObject;

		// !nullcheck
		if (pPrisonKeyObject != nullptr)
		{
			// ����������
			pPrisonKeyObject->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pPrisonKeyObject;
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CPrisonKeyObject::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �^�C�v�ݒ�
	SetType(ITEM_OBJECT_KEY_PRISON);
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
void CPrisonKeyObject::Uninit(void)
{
	// �I������
	CItemObject::Uninit();
}

//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CPrisonKeyObject::Update(void)
{
	// �X�V����
	CItemObject::Update();
}

//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CPrisonKeyObject::Draw(void)
{
	// �`�揈��
	CItemObject::Draw();
}
