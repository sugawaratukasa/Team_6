//=============================================================================
// �_�N�g [object_duct_wall.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "object_duct_wall.h"
#include "resource_manager.h"
#include "duct_collision.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(180.0f,500.0f,25.0f))		// �T�C�Y
#define COLLISION_SIZE2	(D3DXVECTOR3(25.0f,500.0f,180.0f))		// �T�C�Y
#define COLLISION_POS	(D3DXVECTOR3(pos.x + 50.0f,0.0f,pos.z))	// �ʒu
#define COLLISION_POS2	(D3DXVECTOR3(pos.x - 50.0f,0.0f,pos.z))	// �ʒu
#define ROT_90			(D3DXToRadian(89.0f))					// ����

//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CDuct_Wall::CDuct_Wall(PRIORITY Priority) : CObject(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CDuct_Wall::~CDuct_Wall()
{
}
//=============================================================================
// ���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
CDuct_Wall * CDuct_Wall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CKeepOut_Wall�̃|�C���^
	CDuct_Wall *pDuct_Wall = nullptr;

	// nullcheck
	if (pDuct_Wall == nullptr)
	{
		// �������m��
		pDuct_Wall = new CDuct_Wall;

		// !nullcheck
		if (pDuct_Wall != nullptr)
		{
			// ����������
			pDuct_Wall->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pDuct_Wall;
}

//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CDuct_Wall::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_DUCT);

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

	// ���萶��
	CDuct_Collision::Create(COLLISION_POS, ZeroVector3, CDuct_Collision::TYPE_LEFT);
	CDuct_Collision::Create(COLLISION_POS2, ZeroVector3, CDuct_Collision::TYPE_RIGHT);
	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CDuct_Wall::Uninit(void)
{
	// �I������
	CObject::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CDuct_Wall::Update(void)
{
	// �X�V����
	CObject::Update();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CDuct_Wall::Draw(void)
{
	// �`�揈��
	CObject::Draw();
}