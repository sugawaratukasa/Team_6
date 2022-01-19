//=============================================================================
//
// �Ŏ�̒ʕ���󂯂���Ԃ̏��� [jailer_notice.cpp]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "jailer_notice.h"
#include "jalier_ChaseState.h"
#include "jailer.h"
#include "jailer_view.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
CJailer_Notice* CJailer_Notice::m_pShingleton = nullptr;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CJailer_Notice::CJailer_Notice()
{
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CJailer_Notice::~CJailer_Notice()
{
}

//=============================================================================
//�C���X�^���X�擾
//=============================================================================
CJailer_Notice * CJailer_Notice::GetInstance(void)
{
	if (m_pShingleton == nullptr)
	{
		//�C���X�^���X����
		m_pShingleton = new CJailer_Notice;

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
//���
//=============================================================================
void CJailer_Notice::Release(void)
{
	if (m_pShingleton)
	{
		//�������̉��
		delete m_pShingleton;

		m_pShingleton = nullptr;
	}
}

//=============================================================================
//����������
//=============================================================================
void CJailer_Notice::Init(CJailer * pJailer, CJailerView * pJailerView)
{
	pJailer->SetTime(0);
	//�����̐ݒ�
	pJailer->SetSpeed(6.0f);
}

//=============================================================================
//�X�V����
//=============================================================================
void CJailer_Notice::Update(CJailer * pJailer, CJailerView * pJailerView)
{
	pJailer->Notice();

	//���G�͈͂ɂ�����ꍇ
	if (pJailerView->GetIsDetection() == true)
	{
		//�ǐՏ�Ԃ�
		pJailer->ChangeState(CChaseState::GetInstance());
	}
}