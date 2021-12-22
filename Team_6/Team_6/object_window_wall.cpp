//=============================================================================
// ���t���� [object_window_wall.cpp]
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
#include "object_window_wall.h"
#include "resource_manager.h"

//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CWindow_Wall::CWindow_Wall(PRIORITY Priority) : CObject(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CWindow_Wall::~CWindow_Wall()
{
}
//=============================================================================
// ���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
CWindow_Wall * CWindow_Wall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CWindow_Wall�̃|�C���^
	CWindow_Wall *pWindow_Wall = nullptr;

	// nullcheck
	if (pWindow_Wall == nullptr)
	{
		// �������m��
		pWindow_Wall = new CWindow_Wall;

		// !nullcheck
		if (pWindow_Wall != nullptr)
		{
			// ����������
			pWindow_Wall->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pWindow_Wall;
}

//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CWindow_Wall::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_WINDOW_WALL);

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
void CWindow_Wall::Uninit(void)
{
	// �I������
	CObject::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CWindow_Wall::Update(void)
{
	// �X�V����
	CObject::Update();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CWindow_Wall::Draw(void)
{
	// �`�揈��
	CObject::Draw();
}