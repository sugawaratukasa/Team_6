//=============================================================================
//
// �Ŏ�̃^�[�Q�b�g������������ԏ��� [jailer_LostTargetState.cpp]
// Author : Yamada Ryota
//
//=============================================================================
#include "jailer_LostTargetState.h"
#include "jailer.h"
#include "jailer_view.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
CJailer_LostTarget *CJailer_LostTarget::m_pShingleton = nullptr;

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CJailer_LostTarget::~CJailer_LostTarget()
{
	if (m_pShingleton)
	{
		delete m_pShingleton;

		m_pShingleton = nullptr;
	}
}

//=============================================================================
//�C���X�^���X�擾
//=============================================================================
CJailer_LostTarget * CJailer_LostTarget::GetInstance()
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
//����������
//=============================================================================
void CJailer_LostTarget::Init(CJailer * pJailer, CJailerView * pJailerView)
{
	//�^�C�}�[�̃Z�b�g
	pJailer->SetTimer(ZERO_INT);
}

//=============================================================================
//�X�V����
//=============================================================================
void CJailer_LostTarget::Update(CJailer * pJailer, CJailerView * pJailerView)
{
}

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CJailer_LostTarget::CJailer_LostTarget()
{
}
