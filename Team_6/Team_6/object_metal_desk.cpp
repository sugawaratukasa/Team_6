//=============================================================================
// �����̊��N���X [object_metal_desk.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(100.0f,120.0f,100.0f))	// �T�C�Y
#define COLLISION_SIZE2	(D3DXVECTOR3(100.0f,120.0f, 100.0f))	// �T�C�Y
#define ROT_90			(D3DXToRadian(89.0f))				// ����
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "object_metal_desk.h"
#include "resource_manager.h"

//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CMetal_Desk::CMetal_Desk(PRIORITY Priority) : CObject(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CMetal_Desk::~CMetal_Desk()
{
}
//=============================================================================
// ���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
CMetal_Desk * CMetal_Desk::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CMetal_Desk�̃|�C���^
	CMetal_Desk *pMetal_Desk = nullptr;

	// nullcheck
	if (pMetal_Desk == nullptr)
	{
		// �������m��
		pMetal_Desk = new CMetal_Desk;

		// !nullcheck
		if (pMetal_Desk != nullptr)
		{
			// ����������
			pMetal_Desk->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pMetal_Desk;
}

//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CMetal_Desk::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �T�C�Y
	SetSize(COLLISION_SIZE);

	// ����������
	CObject::Init(pos, rot);

	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f�����擾
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_METAL_DESK);

		// ���f���̏���n��
		BindModel(model);
	}

	// 90�ȏ�̏ꍇ
	if (rot.y >= ROT_90)
	{
		// �T�C�Y
		SetSize(COLLISION_SIZE2);
	}

	// ��ސݒ�
	SetType(TYPE_WALL);

	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CMetal_Desk::Uninit(void)
{
	// �I������
	CObject::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CMetal_Desk::Update(void)
{
	// �X�V����
	CObject::Update();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CMetal_Desk::Draw(void)
{
	// �`�揈��
	CObject::Draw();
}