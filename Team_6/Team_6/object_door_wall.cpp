//=============================================================================
// �h�A�̕ǃN���X [object_door.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define ROT_90				(D3DXToRadian(89.0f))						// 90����
#define COLLISION_POS_ADDX	(D3DXVECTOR3(pos.x + 85.0f,pos.y,pos.z))	// �ʒu
#define COLLISION_POS_SUBX	(D3DXVECTOR3(pos.x - 85.0f, pos.y, pos.z))	// �ʒu
#define COLLISION_POS_ADDZ	(D3DXVECTOR3(pos.x, pos.y, pos.z + 85.0f))	// �ʒu
#define COLLISION_POS_SUBZ	(D3DXVECTOR3(pos.x, pos.y, pos.z - 85.0f))	// �ʒu
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "object_door_wall.h"
#include "resource_manager.h"
#include "door_wall_collision.h"
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
	// 90�ȏ�̏ꍇ
	if (rot.y >= ROT_90)
	{
		// ����
		CDoorWallCollision::Create(COLLISION_POS_ADDZ, rot);
		CDoorWallCollision::Create(COLLISION_POS_SUBZ, rot);
	}
	// ��O
	else
	{
		// ����
		CDoorWallCollision::Create(COLLISION_POS_ADDX, rot);
		CDoorWallCollision::Create(COLLISION_POS_SUBX, rot);
	}

	// ��ސݒ�
	SetType(TYPE_WALL);

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