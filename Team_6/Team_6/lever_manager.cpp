//=============================================================================
// ���o�[�}�l�[�W���[ [lever_manager.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "lever_manager.h"
#include "textlog.h"
#include "texture.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define LEVER_CNT	(150)		// ���o�[�J�E���g
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CLever_Manager::CLever_Manager(PRIORITY Priority)
{
	m_nLeverCnt = ZERO_INT;
	m_bOpen		= false;
	m_pLever1	= nullptr;
	m_pLever2	= nullptr;
}
//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CLever_Manager::~CLever_Manager()
{
}
//=============================================================================
// ���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
CLever_Manager * CLever_Manager::Create(CLever * pLever1, CLever * pLever2)
{
	// CLever_Manager�̃|�C���^
	CLever_Manager *pLeverManager = nullptr;

	// nullcheck
	if (pLeverManager == nullptr)
	{
		// �������m��
		pLeverManager = new CLever_Manager;

		// !nullcheck
		if (pLeverManager != nullptr)
		{
			// �|�C���^���
			pLeverManager->m_pLever1 = pLever1;
			pLeverManager->m_pLever2 = pLever2;

			// ������
			pLeverManager->Init(ZeroVector3, ZeroVector3);
		}
	}
	// �|�C���^��Ԃ�
	return pLeverManager;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CLever_Manager::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CLever_Manager::Uninit(void)
{
	// �|�C���^������
	if (m_pLever1 != nullptr)
	{
		// nullptr���
		m_pLever1 = nullptr;
	}
	// �|�C���^������
	if (m_pLever2 != nullptr)
	{
		// nullptr���
		m_pLever2 = nullptr;
	}
	// �j������
	Release();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CLever_Manager::Update(void)
{
	// �������Ă��邩�擾
	bool bDown1 = m_pLever1->GetbDownLever();
	bool bDown2 = m_pLever2->GetbDownLever();

	// ���o�[��1���������Ă���ꍇ
	if (bDown1 == true && bDown2 == false)
	{
		// �C���N�������g
		m_nLeverCnt++;

		// 2.5�b�𒴂����ꍇ
		if (m_nLeverCnt > LEVER_CNT)
		{
			// �e�L�X�g���O����
			CTextLog::Create(CTexture::TEXTURE_LOG_P1_NOT_SHUTTER_DOWN);

			// 0�ɖ߂�
			m_nLeverCnt = ZERO_INT;
		}
	}
	// ���o�[��1���������Ă���ꍇ
	if (bDown1 == false && bDown2 == true)
	{
		// �C���N�������g
		m_nLeverCnt++;

		// 2.5�b�𒴂����ꍇ
		if (m_nLeverCnt > LEVER_CNT)
		{
			// 0�ɖ߂�
			m_nLeverCnt = ZERO_INT;

			// �e�L�X�g���O����
			CTextLog::Create(CTexture::TEXTURE_LOG_P2_NOT_SHUTTER_DOWN);
		}
	}
	// ���o�[�������������Ă��邩
	if (bDown1 == true && bDown2 == true)
	{
		// �h�A���J���Ă��Ȃ��ꍇ
		if (m_bOpen == false)
		{
			// �h�A���J��������ݒ肷��
			m_pLever1->SetOpen(true);

			m_pLever2->SetOpen(true);

			// �e�L�X�g���O����
			CTextLog::Create(CTexture::TEXTURE_LOG_P1_SHUTTER_DOWN);

			// �e�L�X�g���O����
			CTextLog::Create(CTexture::TEXTURE_LOG_P2_SHUTTER_DOWN);

			// true��
			m_bOpen = true;
		}
	}
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CLever_Manager::Draw(void)
{
}