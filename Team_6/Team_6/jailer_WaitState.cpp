//=============================================================================
//
// �Ŏ�ҋ@��ԃN���X [jailer_WaitState.cpp]
// Author : OgumaAkira
//
//=============================================================================
#include "jailer_WaitState.h"
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
void CWaitState::Init(CJailer *jailer, CFan3D *fan3d)
{
	jailer->SetTimer(ZERO_INT);
}
//=============================================================================
//�X�V�֐�
//=============================================================================
void CWaitState::Update(CJailer *jailer, CFan3D *fan3d)
{//���G�͈͂ɂ�����ꍇ
	if (fan3d->GetDetection() == false)
	{	
		//�ҋ@����
		if (jailer->AddTimer(ADD_TIME) >= WAIT_TIME)
		{
			jailer->AddIndex();
			//�����Ԃ�
			jailer->ChangeState(CMoveState::GetInstance());
		}
		else
		{
			jailer->Wait();
		}
	}
	//���G�͈͂ɂ�����ꍇ
	else if (fan3d->GetDetection() == true)
	{
		//�ǐՏ�Ԃ�
		jailer->ChangeState(CChaseState::GetInstance());
	}

}
