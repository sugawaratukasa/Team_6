//=============================================================================
// �h�A�̕ǂ̓����蔻��p�N���X [door_wall_collision.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(20.0f,550.0f,20.0f))	// �T�C�Y
#define COLLISION_SIZE2	(D3DXVECTOR3(20.0f,550.0f,20.0f))	// �T�C�Y
#define ROT_90			(D3DXToRadian(89.0f))				// ����
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "door_wall_collision.h"
#include "resource_manager.h"

//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CDoorWallCollision::CDoorWallCollision(PRIORITY Priority) : CObject(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CDoorWallCollision::~CDoorWallCollision()
{
}
//=============================================================================
// ���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
CDoorWallCollision * CDoorWallCollision::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CWall�̃|�C���^
	CDoorWallCollision *pWall = nullptr;

	// nullcheck
	if (pWall == nullptr)
	{
		// �������m��
		pWall = new CDoorWallCollision;

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
HRESULT CDoorWallCollision::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �T�C�Y
	SetSize(COLLISION_SIZE);

	// ����������
	CObject::Init(pos, rot);

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
void CDoorWallCollision::Uninit(void)
{
	// �I������
	CObject::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CDoorWallCollision::Update(void)
{
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CDoorWallCollision::Draw(void)
{
}