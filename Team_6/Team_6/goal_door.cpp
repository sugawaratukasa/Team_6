//=============================================================================
// �S�[���̔� [goal_door.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "goal_door.h"
#include "object.h"
#include "manager.h"
#include "resource_manager.h"
#include "jailer_door_collision.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(180.0f,330.0f,25.0f))	// �T�C�Y
#define COLLISION_SIZE2	(D3DXVECTOR3(25.0f,330.0f,180.0f))	// �T�C�Y
#define ROT_90			(D3DXToRadian(89.0f))				// ����
#define MOVE_Y			(10.0f)								// �ړ�
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CGoal_Door::CGoal_Door(PRIORITY Priority)
{
	m_pLever1 = nullptr;
	m_pLever2 = nullptr;
	m_InitPos = ZeroVector3;
}
//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================

CGoal_Door::~CGoal_Door()
{
}
//=============================================================================
// ���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
CGoal_Door * CGoal_Door::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CLever *pLever1, CLever *pLever2)
{
	// CGoal_Door�̃|�C���^
	CGoal_Door *pGoal_Door = nullptr;

	// nullcheck
	if (pGoal_Door == nullptr)
	{
		// �������m��
		pGoal_Door = new CGoal_Door;

		// !nullcheck
		if (pGoal_Door != nullptr)
		{
			// CLever�̃|�C���^���
			pGoal_Door->m_pLever1 = pLever1;

			// CLever�̃|�C���^���
			pGoal_Door->m_pLever2 = pLever2;

			// ����������
			pGoal_Door->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pGoal_Door;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CGoal_Door::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �h�A�̏����������֐��Ăяo��
	CDoor::Init(pos, rot);

	// �T�C�Y
	SetSize(COLLISION_SIZE);

	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f�����擾
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_GOAL_DOOR);

		// ���f���̏���n��
		BindModel(model);
	}

	// 90�ȏ�̏ꍇ
	if (rot.y >= ROT_90)
	{
		// �T�C�Y
		SetSize(COLLISION_SIZE2);
	}

	//OBB�̍쐬
	SetObb(CObb::Create(pos, rot, GetMesh()));

	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CGoal_Door::Uninit(void)
{
	// �h�A�̏I�������֐��Ăяo��
	CDoor::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CGoal_Door::Update(void)
{
	// �h�A�̍X�V�����֐��Ăяo��
	CDoor::Update();

	// �������Ă��邩�擾
	bool bDown1 = m_pLever1->GetbDownLever();
	bool bDown2 = m_pLever2->GetbDownLever();

	// ���o�[�������������Ă��邩
	if (bDown1 == true && bDown2 == true)
	{
		// �J��
		Open();
	}
	// ���o�[�Ƃ��������Ă��Ȃ��ꍇ
	else
	{
		// �J��
		Close();
	}
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CGoal_Door::Draw(void)
{
	// �h�A�̕`�揈���֐��Ăяo��
	CDoor::Draw();
}
//=============================================================================
// �J�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CGoal_Door::Open(void)
{
	// �ʒu
	D3DXVECTOR3 pos = GetPos();

	// �ʒu
	if (pos.y >= m_InitPos.y - COLLISION_SIZE.y)
	{
		// �ړ�
		pos.y -= MOVE_Y;

		// �ʒu�ݒ�
		SetPos(pos);
	}
}
//=============================================================================
// ���鏈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CGoal_Door::Close(void)
{
	// �ʒu
	D3DXVECTOR3 pos = GetPos();
	// �ʒu
	if (pos.y <= m_InitPos.y)
	{
		// �ړ�
		pos.y += MOVE_Y;

		// �ʒu�ݒ�
		SetPos(pos);
	}
}
