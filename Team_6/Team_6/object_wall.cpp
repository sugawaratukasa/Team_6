//=============================================================================
// �ǃN���X [object_wall.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================

#define COLLISION_SIZE	(D3DXVECTOR3(180.0f,500.0f,30.0f))	// �T�C�Y
#define COLLISION_SIZE2	(D3DXVECTOR3(30.0f,500.0f,180.0f))	// �T�C�Y
#define ROT_90			(D3DXToRadian(89.0f))				// ����
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "object_wall.h"
#include "resource_manager.h"

//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CWall::CWall(PRIORITY Priority) : CObject(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CWall::~CWall()
{
}
//=============================================================================
// ���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
CWall * CWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CWall�̃|�C���^
	CWall *pWall = nullptr;

	// nullcheck
	if (pWall == nullptr)
	{
		// �������m��
		pWall = new CWall;

		// !nullcheck
		if (pWall != nullptr)
		{
			// ����������
			pWall->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pWall;
}

//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CWall::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_WALL);

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
void CWall::Uninit(void)
{
	// �I������
	CObject::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CWall::Update(void)
{
	// �X�V����
	CObject::Update();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CWall::Draw(void)
{
	// �`�揈��
	CObject::Draw();
}