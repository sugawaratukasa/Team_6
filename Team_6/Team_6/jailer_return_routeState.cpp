//=============================================================================
//
// �Ŏ�ҋ@��ԃN���X [jailer_WaitState.cpp]
// Author : Yamada Ryota
//
//=============================================================================
#include "jailer_return_routeState.h"
#include "jalier_MoveState.h"
#include "jalier_ChaseState.h"
#include "jailer.h"
#include "jailer_emotion.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define WAIT_TIME (100)	//�ҋ@���鎞��

//=============================================================================
//�C���X�^���X�����֐�
//=============================================================================
CReturnRouteState * CReturnRouteState::GetInstance()
{
	static CReturnRouteState instance;
	return &instance;
}

//=============================================================================
//�������֐�
//=============================================================================
void CReturnRouteState::Init(CJailer *pJailer, CJailerView *pJailerView)
{
	pJailer->SetTime(ZERO_INT);
	pJailer->SetRetrunData();
	pJailer->GetEmotion()->SetEmotion(CJailer_Emotion::EMOTION_TYPE_NONE);
}

//=============================================================================
//�X�V�֐�
//=============================================================================
void CReturnRouteState::Update(CJailer *pJailer, CJailerView *pJailerView)
{//���G�͈͂ɂ�����ꍇ

	pJailer->RetrunRoute();

	//���G�͈͂ɂ�����ꍇ
	if (pJailerView->GetIsDetection() == true)
	{
		//�ǐՏ�Ԃ�
		pJailer->ChangeState(CChaseState::GetInstance());
	}
}
