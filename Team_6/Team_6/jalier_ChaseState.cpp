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
#include "manager.h"
#include "renderer.h"
#include "fog.h"
#include "jailer_emotion.h"

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

	//���o�����v���C���[�ԍ����擾
	int nPlayerNumber = pJailerView->GetDetectionNumber();

	//�t�H�O�̃|�C���^���擾
	CFog *pFog = CManager::GetRenderer()->GetFog(nPlayerNumber);

	//�t�H�O�����[�j���O�Ɏw��
	pFog->SetFogState(CFog::FOG_WARNING);

	pJailer->GetEmotion()->SetEmotion(CJailer_Emotion::EMOTION_TYPE_ANGER);
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
			//���o�����v���C���[�ԍ����擾
			int nPlayerNumber = pJailerView->GetDetectionNumber();

			//�t�H�O�̃|�C���^���擾
			CFog *pFog = CManager::GetRenderer()->GetFog(nPlayerNumber);

			//�t�H�O�̏I��
			pFog->SetFogState(CFog::FOG_END);

			//�ʂ̏�Ԃֈڍs
			//�x����Ԃ�
			pJailer->ChangeState(CJailer_LostTarget::GetInstance());
		}
	}
	else
	{
		int nTime = pJailer->AddTime(1);

		if (pJailer->GetDestLength() <= 10.0f || nTime == 60)
		{
			//���o�����v���C���[�ԍ����擾
			int nPlayerNumber = pJailerView->GetDetectionNumber();

			//�t�H�O�̃|�C���^���擾
			CFog *pFog = CManager::GetRenderer()->GetFog(nPlayerNumber);

			//�t�H�O�̏I��
			pFog->SetFogState(CFog::FOG_END);

			//�x����Ԃ�
			pJailer->ChangeState(CJailer_LostTarget::GetInstance());
		}
	}
}