//=============================================================================
//
// �Ŏ珄���ԃN���X [jalier_MoveState.cpp]
// Author : OgumaAkira
//
//=============================================================================

//=============================================================================
//�}�N����`
//=============================================================================
#define MOVE_TIME (200)	//�ړ����鎞��

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "jailer_WaitState.h"
#include "jalier_MoveState.h"
#include "jalier_ChaseState.h"
#include "jailer.h"

//=============================================================================
//�C���X�^���X�����֐�
//=============================================================================
CMoveState * CMoveState::GetInstance()
{
	static CMoveState instance;
	return &instance;
}

//=============================================================================
//�������֐�
//=============================================================================
void CMoveState::Init(CJailer *pJailer, CJailerView *pJailerView)
{
	pJailer->SetTimer(ZERO_INT);
}

//=============================================================================
//�X�V�֐�
//=============================================================================
void CMoveState::Update(CJailer *pJailer, CJailerView *pJailerView)
{
	int time = pJailer->AddTimer(ADD_TIME);
	
	if (pJailerView->GetIsDetection() == false)
	{
		pJailer->Move();
		//�ړ�����
		if (time >= MOVE_TIME)
		{
			//�ҋ@��Ԃ�
			pJailer->ChangeState(CWaitState::GetInstance());
		}
	}
	//���G�͈͂ɂ�����ꍇ
	else 
	{
		//�ǐՏ�Ԃ�
		pJailer->ChangeState(CChaseState::GetInstance());
	}
}
