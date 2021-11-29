//=============================================================================
//
// �Ŏ�̃^�[�Q�b�g������������ԏ��� [jailer_LostTargetState.cpp]
// Author : Yamada Ryota
//
//=============================================================================
#include "jailer_LostTargetState.h"
#include "jailer.h"
#include "jailer_view.h"
#include "Jalier_MoveState.h"
#include "jalier_ChaseState.h"
#include "jailer_return_routeState.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define CAUTION_TIME (60)	//�x�����鎞��

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
CJailer_LostTarget *CJailer_LostTarget::m_pShingleton = nullptr;

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CJailer_LostTarget::~CJailer_LostTarget()
{
}

//=============================================================================
//�C���X�^���X�擾
//=============================================================================
CJailer_LostTarget * CJailer_LostTarget::GetInstance(void)
{
	if (!m_pShingleton)
	{
		//�C���X�^���X����
		m_pShingleton = new CJailer_LostTarget;

		if (m_pShingleton)
		{
			return m_pShingleton;
		}
		else
		{
			return nullptr;
		}
	}
	return m_pShingleton;
}

//=============================================================================
//�C���X�^���X���
//=============================================================================
void CJailer_LostTarget::Release(void)
{
	if (m_pShingleton)
	{
		delete m_pShingleton;

		m_pShingleton = nullptr;
	}
}

//=============================================================================
//����������
//=============================================================================
void CJailer_LostTarget::Init(CJailer * pJailer, CJailerView * pJailerView)
{
	//�^�C�}�[�̃Z�b�g
	pJailer->SetTimer(ZERO_INT);
	pJailer->SetSpeed(ZERO_FLOAT);
	pJailer->SetMove(ZeroVector3);
	pJailerView->JailerCaution(false);
}

//=============================================================================
//�X�V����
//=============================================================================
void CJailer_LostTarget::Update(CJailer * pJailer, CJailerView * pJailerView)
{
	//�x��
	pJailer->Caution();

	//����������
	if (pJailerView->GetIsDetection() == true)
	{
		//�ǐՏ�Ԃ�
		pJailer->ChangeState(CChaseState::GetInstance());
	}
	else
	{
		//��������Ԃ���莞�ԑ�������
		if (pJailer->AddTimer(ADD_TIME) >= CAUTION_TIME)
		{
			//�����Ԃ�
			pJailer->ChangeState(CWaitState::GetInstance());
		}
	}
}

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CJailer_LostTarget::CJailer_LostTarget()
{
}
