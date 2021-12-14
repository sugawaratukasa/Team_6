//=============================================================================
// �}�b�v�I�u�W�F�N�g [item_object_map.cpp]
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
#include "item_object_map.h"

//=============================================================================
// �}�N����`
// Author : Nikaido Taichi
//=============================================================================
#define SIZE (D3DXVECTOR3(100.0f,100.0f,100.0f))

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CMapObject::CMapObject(PRIORITY Priority) : CItemObject(Priority)
{
}
//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CMapObject::~CMapObject()
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CMapObject * CMapObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CMapObject�̃|�C���^
	CMapObject *pMapObject = nullptr;

	// nullcheck
	if (pMapObject == nullptr)
	{
		// �������m��
		pMapObject = new CMapObject;

		// !nullcheck
		if (pMapObject != nullptr)
		{
			// ����������
			pMapObject->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pMapObject;
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CMapObject::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �^�C�v�ݒ�
	SetType(ITEM_OBJECT_MAP);
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
void CMapObject::Uninit(void)
{
	// �I������
	CItemObject::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CMapObject::Update(void)
{
	// �X�V����
	CItemObject::Update();
}
//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CMapObject::Draw(void)
{
	// �`�揈��
	CItemObject::Draw();
}