#include "goal_area.h"
#include "character.h"
#include "model_collision_box.h"
#include "model.h"

CGoalArea::CGoalArea()
{
}

CGoalArea::~CGoalArea()
{
}

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

HRESULT CGoalArea::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CModel::Init(pos, rot);
	CModelCollisionBox::Create(pos, rot, this);
	return S_OK;
}

void CGoalArea::Uninit(void)
{
	CModel::Uninit();
}

void CGoalArea::Update(void)
{
	CModel::Update();
	Goal();
}

void CGoalArea::Draw(void)
{
	CModel::Draw();
}

void CGoalArea::Goal(void)
{
}
