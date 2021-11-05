//=============================================================================
// �h�A�̕ǃN���X [object_door.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(500.0f,500.0f,500.0f))
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "object_door_wall.h"
#include "resource_manager.h"
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CDoor_Wall::CDoor_Wall(PRIORITY Priority) : CObject(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CDoor_Wall::~CDoor_Wall()
{
}
//=============================================================================
// ���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
CDoor_Wall * CDoor_Wall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CDoor_Wall�̃|�C���^
	CDoor_Wall *pDoor_Wall = nullptr;

	// nullcheck
	if (pDoor_Wall == nullptr)
	{
		// �������m��
		pDoor_Wall = new CDoor_Wall;

		// !nullcheck
		if (pDoor_Wall != nullptr)
		{
			// ����������
			pDoor_Wall->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pDoor_Wall;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CDoor_Wall::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ����������
	CObject::Init(pos, rot);

	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f�����擾
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_DOOR_WALL);

		// ���f���̏���n��
		BindModel(model);
	}
	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CDoor_Wall::Uninit(void)
{
	// �I������
	CObject::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CDoor_Wall::Update(void)
{
	// �X�V����
	CObject::Update();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CDoor_Wall::Draw(void)
{
	// �`�揈��
	CObject::Draw();
}