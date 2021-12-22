//=============================================================================
// �e�[�u���N���X [object_table.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(100.0f,100.0f,100.0f))	// �T�C�Y
#define COLLISION_SIZE2	(D3DXVECTOR3(100.0f,100.0f, 100.0f))	// �T�C�Y
#define ROT_90			(D3DXToRadian(89.0f))				// ����
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "object_table.h"
#include "resource_manager.h"

//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CTable::CTable(PRIORITY Priority) : CObject(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CTable::~CTable()
{
}
//=============================================================================
// ���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
CTable * CTable::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CTable�̃|�C���^
	CTable *pTable = nullptr;

	// nullcheck
	if (pTable == nullptr)
	{
		// �������m��
		pTable = new CTable;

		// !nullcheck
		if (pTable != nullptr)
		{
			// ����������
			pTable->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pTable;
}

//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CTable::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_TABLE);

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
void CTable::Uninit(void)
{
	// �I������
	CObject::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CTable::Update(void)
{
	// �X�V����
	CObject::Update();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CTable::Draw(void)
{
	// �`�揈��
	CObject::Draw();
}