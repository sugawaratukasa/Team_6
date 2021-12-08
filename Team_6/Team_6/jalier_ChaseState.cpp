//=============================================================================
//
// �Ŏ�ǐՏ�ԃN���X [jailer_Hierachystate.cpp]
// Author : Yamada Ryota
//
//=============================================================================
#include "jailer_return_routeState.h"
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
	pJailer->SetTime(0);
}

//=============================================================================
//�X�V�֐�
//=============================================================================
void CChaseState::Update(CJailer *pJailer, CJailerView *pJailerView)
{
	//�ǐՂ���
	pJailer->ChasePlayer();

	//�v���C���[�𔭌����Ă���
	if (pJailerView->GetIsDetection() == true)
	{
		pJailer->SetTime(0);
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
		int nTime = pJailer->AddTime(1);

		if (pJailer->GetDestLength() <= 10.0f || nTime == 60)
		{
			//�x����Ԃ�
			pJailer->ChangeState(CJailer_LostTarget::GetInstance());
		}
	}
}