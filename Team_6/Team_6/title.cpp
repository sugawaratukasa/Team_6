//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "title.h"
#include "renderer.h"
#include "input.h"
#include "scene_2d.h"
#include "logo_title.h"
#include "bg_title.h"
#include "title_button_manager.h"
#include "fade.h"
//=============================================================================
// �}�N����`
//=============================================================================

#define TRANSITION_WAIT_LENGTH	(300)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{
	m_pTitleButtonManager = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{
	// �I������
	Uninit();
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTitle::Init(void)
{
	// ���������֐��Ăяo��
	CreateAll();
	// �J�E���^������
	m_nCountToMovie = 0;
	m_bCount = true;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTitle::Uninit(void)
{
	if (m_pTitleButtonManager != nullptr)
	{
		// �^�C�g���{�^���}�l�[�W���[�̏I�������֐��Ăяo��
		m_pTitleButtonManager->Uninit();
		m_pTitleButtonManager = nullptr;
	}


}

//=============================================================================
// �X�V����
//=============================================================================
void CTitle::Update(void)
{
	if (m_pTitleButtonManager != nullptr)
	{
		// �^�C�g���{�^���}�l�[�W���[�̍X�V�����֐��Ăяo��
		m_pTitleButtonManager->Update();
	}


	// ����J�n�܂ł̃J�E���^�[�����Z
	if (m_bCount)
	{
		m_nCountToMovie++;
	}
	if (m_nCountToMovie >= TRANSITION_WAIT_LENGTH)
	{
		m_nCountToMovie = 0;
		// ��ʑJ��
		ModeTransition(CManager::MODE_TYPE_MOVIE);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTitle::Draw(void)
{
}
//=============================================================================
// ���������֐�
//=============================================================================
void CTitle::CreateAll(void)
{
	CTitleBG::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	CTitleLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 200.0f, 0.0f), D3DXVECTOR3(700.0f, 130.0f, 0.0f));
	if (m_pTitleButtonManager == nullptr)
	{
		// �^�C�g���{�^���}�l�[�W���[�̐���
		m_pTitleButtonManager = CTitleButtonManager::Create();
	}
}


//=============================================================================
// ���[�h�J��
//=============================================================================
void CTitle::ModeTransition(CManager::MODE_TYPE mode)
{
	// �J��
	CFade *pFade = CManager::GetFade();
	pFade->SetFade(mode);
	m_bCount = false;
	m_nCountToMovie = 0;
}