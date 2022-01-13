//=============================================================================
// PC�̊� [pc_desk.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================

#define COLLISION_SIZE	(D3DXVECTOR3(180.0f,400.0f,90.0f))	// �T�C�Y
#define COLLISION_SIZE2	(D3DXVECTOR3(90.0f,400.0f,180.0f))	// �T�C�Y
#define ROT_90			(D3DXToRadian(89.0f))				// ����
#define ROT_180			(D3DXToRadian(179.0f))				// ����
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "pc_desk.h"
#include "resource_manager.h"

//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CPC_Desk::CPC_Desk(PRIORITY Priority) : CObject(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CPC_Desk::~CPC_Desk()
{
}
//=============================================================================
// ���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
CPC_Desk * CPC_Desk::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CPC_Desk�̃|�C���^
	CPC_Desk *pPC_Desk = nullptr;

	// nullcheck
	if (pPC_Desk == nullptr)
	{
		// �������m��
		pPC_Desk = new CPC_Desk;

		// !nullcheck
		if (pPC_Desk != nullptr)
		{
			// ����������
			pPC_Desk->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pPC_Desk;
}

//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CPC_Desk::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_PC_DESK);

		// ���f���̏���n��
		BindModel(model);
	}

	// 90�ȏ�̏ꍇ
	if (rot.y >= ROT_90 && rot.y < ROT_180)
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
void CPC_Desk::Uninit(void)
{
	// �I������
	CObject::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPC_Desk::Update(void)
{
	// �X�V����
	CObject::Update();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPC_Desk::Draw(void)
{
	// �`�揈��
	CObject::Draw();
}