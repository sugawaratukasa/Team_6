//=============================================================================
// �S�[���G���A [goal_area.cpp]
// Author : Nikaido Taichi
//=============================================================================
#include "goal_area.h"
#include "character.h"
#include "model_collision_box.h"
#include "model.h"
#include "player.h"
#include "manager.h"
#include "mode_base.h"
#include "collision.h"
#include "fade.h"

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CGoalArea::CGoalArea()
{
	m_bGoal = false;		// �S�[�����
}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CGoalArea::~CGoalArea()
{
}

//=============================================================================
// ���������֐�
// Author : Nikaido Taichi
//=============================================================================
CGoalArea * CGoalArea::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�^�C�g���ɖ߂�{�^���̃|�C���^
	CGoalArea * pGoalArea = nullptr;
	//�^�C�g���ɖ߂�{�^���̃|�C���^��nullptr�̏ꍇ
	if (pGoalArea == nullptr)
	{
		//�^�C�g���ɖ߂�{�^���̃������m��
		pGoalArea = new CGoalArea;
		//�^�C�g���ɖ߂�{�^���̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (pGoalArea != nullptr)
		{
			//�^�C�g���ɖ߂�{�^���̏����������֐��Ăяo��
			pGoalArea->Init(pos,rot);
		}
	}
	//�^�C�g���ɖ߂�{�^���̃|�C���^��Ԃ�
	return pGoalArea;
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CGoalArea::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���f���̏����������֐��Ăяo��
	CModel::Init(pos, rot);
	SetSize(D3DXVECTOR3(1200.0f, 1000.0f, 500.0f));
	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CGoalArea::Uninit(void)
{
	// ���f���̏I�������֐��Ăяo��
	CModel::Uninit();
}

//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CGoalArea::Update(void)
{
	// ���f���̍X�V�����֐��Ăяo��
	CModel::Update();
	// �S�[�������֐�
	Goal();
}

//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CGoalArea::Draw(void)
{
}

//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CGoalArea::Goal(void)
{
	// �ʒu���擾����
	D3DXVECTOR3 Position = GetPos();
	// �T�C�Y���擾����
	D3DXVECTOR3 Size = GetSize();
	// �v���C���[�̃|�C���^
	CPlayer * apPlayer[MAX_PLAYER];
	// �v���C���[�̃S�[�����
	bool bPlayerGoal[MAX_PLAYER];
	// �v���C���[�̍ő吔����
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		// �v���C���[�̃|�C���^���擾����
		apPlayer[nCount] = CManager::GetModePtr()->GetPlayer(nCount);
		// !nullcheck
		if (apPlayer[nCount] != nullptr)
		{
			// �v���C���[�̈ʒu���擾����
			D3DXVECTOR3 PlayerPosition = apPlayer[nCount]->GetPos();
			// �v���C���[�̃T�C�Y���擾����
			D3DXVECTOR3 PlayerSize = apPlayer[nCount]->GetSize();
			// �v���C���[�̋�`�^�̓����蔻��
			if (CCollision::CollisionRectangleAndRectangle(Position, PlayerPosition, Size, PlayerSize) == true)
			{
				// �v���C���[�̃S�[����Ԃ�true�ɂ���
				apPlayer[nCount]->SetbGoal(true);
			}
			// �v���C���[�̃S�[����Ԃ��擾����
			bPlayerGoal[nCount] = apPlayer[nCount]->GetbGoal();
		}
	}
	// �����v���C���[1�ƃv���C���[2�̗�����true�̏ꍇ
	if (bPlayerGoal[0] == true && bPlayerGoal[1] == true)
	{
		// �����S�[����Ԃ�false�̏ꍇ
		if (m_bGoal == false)
		{
			// �J��
			CFade *pFade = CManager::GetFade();
			pFade->SetFade(CManager::MODE_TYPE_RANKING_RESULT);
			// �S�[����Ԃ�true�ɂ���
			m_bGoal = true;
		}
	}
}