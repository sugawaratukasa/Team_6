//=============================================================================
// �؂̊��N���X [object_wood_desk.cpp]
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
#include "object_wood_desk.h"
#include "resource_manager.h"

//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CWood_Desk::CWood_Desk(PRIORITY Priority) : CObject(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CWood_Desk::~CWood_Desk()
{
}
//=============================================================================
// ���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
CWood_Desk * CWood_Desk::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CWood_Desk�̃|�C���^
	CWood_Desk *pWood_Desk = nullptr;

	// nullcheck
	if (pWood_Desk == nullptr)
	{
		// �������m��
		pWood_Desk = new CWood_Desk;

		// !nullcheck
		if (pWood_Desk != nullptr)
		{
			// ����������
			pWood_Desk->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pWood_Desk;
}

//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CWood_Desk::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_WOOD_DESK);

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
void CWood_Desk::Uninit(void)
{
	// �I������
	CObject::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CWood_Desk::Update(void)
{
	// �X�V����
	CObject::Update();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CWood_Desk::Draw(void)
{
	// �`�揈��
	CObject::Draw();
}