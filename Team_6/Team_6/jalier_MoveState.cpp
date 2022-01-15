//=============================================================================
//
// �Ŏ珄���ԃN���X [jalier_MoveState.cpp]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//�}�N����`
//=============================================================================
#define MOVE_TIME (200)	//�ړ����鎞��

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "jailer_return_routeState.h"
#include "jalier_MoveState.h"
#include "jalier_ChaseState.h"
#include "jailer.h"
#include "jailer_emotion.h"

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
	pJailer->SetTime(ZERO_INT);
	pJailer->GetEmotion()->SetEmotion(CJailer_Emotion::EMOTION_TYPE_NONE);
}

//=============================================================================
//�X�V�֐�
//=============================================================================
void CMoveState::Update(CJailer *pJailer, CJailerView *pJailerView)
{
	if (pJailerView->GetIsDetection() == false)
	{
		pJailer->Patrol();
	}
	//���G�͈͂ɂ�����ꍇ
	else 
	{
		//�ǐՏ�Ԃ�
		pJailer->ChangeState(CChaseState::GetInstance());
	}
}
