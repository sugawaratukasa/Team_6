//=============================================================================
//
// �Ŏ�ҋ@��ԃN���X [jailer_WaitState.cpp]
// Author : OgumaAkira
//
//=============================================================================
#include "jailer_return_routeState.h"
#include "jalier_MoveState.h"
#include "jalier_ChaseState.h"
#include "jailer.h"
//=============================================================================
//�}�N����`
//=============================================================================
#define WAIT_TIME (100)	//�ҋ@���鎞��

//=============================================================================
//�C���X�^���X�����֐�
//=============================================================================
CWaitState * CWaitState::GetInstance()
{
	static CWaitState instance;
	return &instance;
}

//=============================================================================
//�������֐�
//=============================================================================
void CWaitState::Init(CJailer *pJailer, CJailerView *pJailerView)
{
	pJailer->SetTimer(ZERO_INT);

	pJailer->SetRetrunData();
}
//=============================================================================
//�X�V�֐�
//=============================================================================
void CWaitState::Update(CJailer *pJailer, CJailerView *pJailerView)
{//���G�͈͂ɂ�����ꍇ

	pJailer->RetrunRoute();
	//if (pJailerView->GetIsDetection() == false)
	//{	
	//	//�ҋ@����
	//	if (pJailer->AddTimer(ADD_TIME) >= WAIT_TIME)
	//	{
	//		pJailer->SettingPosDest();
	//		//�����Ԃ�
	//		pJailer->ChangeState(CMoveState::GetInstance());
	//	}
	//	else
	//	{
	//		
	//	}
	//}
	////���G�͈͂ɂ�����ꍇ
	//else if (pJailerView->GetIsDetection() == true)
	//{
	//	//�ǐՏ�Ԃ�
	//	pJailer->ChangeState(CChaseState::GetInstance());
	//}

}
