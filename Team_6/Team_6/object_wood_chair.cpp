//=============================================================================
// �؂̈֎q�N���X [object_wood_chair.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================

#define COLLISION_SIZE	(D3DXVECTOR3(70.0f,70.0f,70.0f))	// �T�C�Y
#define COLLISION_SIZE2	(D3DXVECTOR3(70.0f,70.0f,70.0f))	// �T�C�Y
#define ROT_90			(D3DXToRadian(89.0f))				// ����
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "object_wood_chair.h"
#include "resource_manager.h"

//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CWood_Chair::CWood_Chair(PRIORITY Priority) : CObject(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CWood_Chair::~CWood_Chair()
{
}
//=============================================================================
// ���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
CWood_Chair * CWood_Chair::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CWood_Chair�̃|�C���^
	CWood_Chair *pWood_Chair = nullptr;

	// nullcheck
	if (pWood_Chair == nullptr)
	{
		// �������m��
		pWood_Chair = new CWood_Chair;

		// !nullcheck
		if (pWood_Chair != nullptr)
		{
			// ����������
			pWood_Chair->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pWood_Chair;
}

//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CWood_Chair::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_WOOD_CHAIR);

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
void CWood_Chair::Uninit(void)
{
	// �I������
	CObject::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CWood_Chair::Update(void)
{
	// �X�V����
	CObject::Update();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CWood_Chair::Draw(void)
{
	// �`�揈��
	CObject::Draw();
}