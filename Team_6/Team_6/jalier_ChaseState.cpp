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
	//�ǐՎ���
	if (pJailer->AddTimer(ADD_TIME) >= CHASE_TIME)
	{
		//������Ԃ����Z�b�g����
		pJailerView->ResetDetection();

		//���G�Ώۂ����Ȃ��ꍇ
		if (pJailerView->GetIsDetection() == false)
		{
			//�߂��C���f�b�N�X������

			//�x����Ԃ�
			pJailer->ChangeState(CJailer_LostTarget::GetInstance());

		}
	}
	else
	{
		//�ǐՂ���
		pJailer->Chase();
	}
}