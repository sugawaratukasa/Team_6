//=============================================================================
//
// �Ŏ�ǐՏ�ԃN���X [jailer_Hierachystate.cpp]
// Author : OgumaAkira
//
//=============================================================================
#include "jailer_WaitState.h"
#include "jailer.h"
#include "jalier_ChaseState.h"
#include "Jailer_AttackState.h"
#include "jailer_LostTargetState.h"
//=============================================================================
//�}�N����`
//=============================================================================
#define CHASE_TIME (60)

//=============================================================================
//�C���X�^���X�����֐�
//=============================================================================
CChaseState * CChaseState::GetInstance()
{
	static CChaseState instance;
	return &instance;
}

//=============================================================================
//�������֐�
//=============================================================================
void CChaseState::Init(CJailer *pJailer, CJailerView *pJailerView)
{
	
}

//=============================================================================
//�X�V�֐�
//=============================================================================
void CChaseState::Update(CJailer *pJailer, CJailerView *pJailerView)
{
	//�ǐՂ���
	pJailer->Chase();

	//�v���C���[�𔭌����Ă���
	if (pJailerView->GetIsDetection() == true)
	{
		//�����蔻����s��
		if (pJailer->IsHitPlayer() == true)
		{
			//�ʂ̏�Ԃֈڍs
			//�x����Ԃ�
			//pJailer->ChangeState(CJailer_LostTarget::GetInstance());
		}
	}
	else
	{
		if (pJailer->GetDistanceRange() <= 10.0f)
		{
			//�x����Ԃ�
			pJailer->ChangeState(CJailer_LostTarget::GetInstance());
		}
	}
}