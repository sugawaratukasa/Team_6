//=============================================================================
//
// �|�[�Y�{�^���}�l�[�W���[ [pause_button_manager.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "sound.h"
#include "keyboard.h"
#include "joypad.h"
#include "pause_button_manager.h"
#include "button_quit_game.h"
#include "button_back_to_title.h"
#include "button_guid.h"
#include "bg_pause.h"
#include "fade.h"
#include "pause_logo_texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define START_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))				//�X�^�[�g�{�^���̈ʒu
#define RANKING_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 80.0f, 0.0f))	//�����L���O�{�^���̈ʒu
#define EXIT_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 160.0f, 0.0f))		//�I���{�^���̈ʒu
#define SIZE (D3DXVECTOR3(450.0f,50.0f,0.0f))														//�T�C�Y
#define STICK_REACTION		(500.0f)																// �X�e�B�b�N�͈̔�
#define STICK_REACTION_MIN	(0.0f)																	// �X�e�B�b�N�͈̔�
//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPauseButtonManager::CPauseButtonManager()
{
	memset(m_apButton, NULL, sizeof(m_apButton));	//�{�^���̃|�C���^
	m_pPauseBG = nullptr;
	m_pPauseLogo = nullptr;
	m_nButton = BUTTON_NONE;						//�{�^��
	m_bStick = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPauseButtonManager::~CPauseButtonManager()
{
}

//=============================================================================
// ���������֐��Ăяo��
//=============================================================================
CPauseButtonManager * CPauseButtonManager::Create(void)
{
	//�^�C�g���{�^���}�l�[�W���[�̃|�C���^
	CPauseButtonManager * pPauseButtonManager = nullptr;
	//�^�C�g���{�^���}�l�[�W���[�|�C���^��nullptr�̏ꍇ
	if (pPauseButtonManager == nullptr)
	{
		//�^�C�g���{�^���}�l�[�W���[�̃������m��
		pPauseButtonManager = new CPauseButtonManager;
		//�^�C�g���{�^���}�l�[�W���[�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (pPauseButtonManager != nullptr)
		{
			//�^�C�g���{�^���}�l�[�W���[�̏����������֐��Ăяo��
			pPauseButtonManager->Init();
		}
	}
	//�^�C�g���{�^���}�l�[�W���[�̃|�C���^��Ԃ�
	return pPauseButtonManager;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CPauseButtonManager::Init(void)
{
	//�����S�������֐��Ăяo��
	InitCreateAll();
	//�{�^���̏����ݒ�
	m_nButton = BUTTON_QUIT_GAME;
	//�{�^���̏����I�������֐��Ăяo��
	m_apButton[m_nButton]->ChangeTranslucent(true);
	// �V�[���Ƀ|�[�Y��K��������
	CScene::SetPause(true);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CPauseButtonManager::Uninit(void)
{
	//�{�^���̍ő吔����
	for (int nCount = 0; nCount < BUTTON_MAX; nCount++)
	{
		//�e�{�^���̏I�������֐��Ăяo��
		m_apButton[nCount]->Uninit();
	}
	if (m_pPauseLogo != nullptr)
	{
		m_pPauseLogo->Uninit();
	}
	if (m_pPauseBG != nullptr)
	{
		m_pPauseBG->Uninit();
	}
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CPauseButtonManager::Update(void)
{
	//���͏����֐��Ăяo��
	PlayerItemGet();
	//�I�������֐��Ăяo��
	Select();
}

//=============================================================================
// ���͏����֐�
//=============================================================================
void CPauseButtonManager::PlayerItemGet(void)
{
	// �L�[�{�[�h�擾
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	CInputJoypad * pJoypad = CManager::GetJoypad();
	// �p�b�h�擾
	LPDIRECTINPUTDEVICE8 P1_PAD = CInputJoypad::GetController(0);

	// �X�e�B�b�N�擾
	DIJOYSTATE js = CInputJoypad::GetStick(0);

	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();
	//����L�[�����͂��ꂽ�ꍇ
	if (pKeyboard->GetTrigger(DIK_UP) && mode == CFade::FADE_MODE_NONE)
	{
		//���݂̃{�^�������Z����
		m_nButton++;
		//�{�^���̑I�������Đ������֐��Ăяo��
		m_apButton[m_nButton]->PlayButtonSE(CButton::BUTTON_SE_SELECT);
	}
	//�����L�[�����͂��ꂽ�ꍇ
	if (pKeyboard->GetTrigger(DIK_DOWN) && mode == CFade::FADE_MODE_NONE)
	{
		//���݂̃{�^�������Z����
		m_nButton--;
		//�{�^���̑I�������Đ������֐��Ăяo��
		m_apButton[m_nButton]->PlayButtonSE(CButton::BUTTON_SE_SELECT);
	}
	//����ENTER�L�[���̓W���C�X�e�B�b�N��A�{�^���������ꂽ��
	if (pKeyboard->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE || pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, 0) && mode == CFade::FADE_MODE_NONE)
	{
		//�{�^���̃v���X�����֐��Ăяo��
		m_apButton[m_nButton]->Press();
	}
	// false�̏ꍇ
	if (m_bStick == false)
	{
		// �X�e�B�b�N���͈͂��z������
		if (js.lY <= -STICK_REACTION)
		{
			// true��
			m_bStick = true;

			// �C���N�������g
			m_nButton++;
		}
		// �X�e�B�b�N���͈͂��z������
		if (js.lY >= STICK_REACTION)
		{
			// true��
			m_bStick = true;

			// �C���N�������g
			m_nButton--;
		}
	}
	else
	{
		// �X�e�B�b�N���͈͊O�̏ꍇ
		if (js.lY >= -STICK_REACTION && js.lY <= STICK_REACTION_MIN)
		{
			// false��
			m_bStick = false;
		}
		// �X�e�B�b�N���͈͊O�̏ꍇ
		if (js.lY <= STICK_REACTION && js.lY >= STICK_REACTION_MIN)
		{
			// false��
			m_bStick = false;
		}
	}
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CPauseButtonManager::Select(void)
{
	//�������݂̃{�^�����Q�[���ɖ߂�{�^����艺��������
	if (m_nButton < BUTTON_QUIT_GAME)
	{
		//���݂̃{�^�����^�C�g���ɖ߂�{�^���ɂ���
		m_nButton = BUTTON_BACK_TO_TITLE;
	}
	//�������݂̃{�^�����I���{�^�����z������
	if (m_nButton > BUTTON_BACK_TO_TITLE)
	{
		//���݂̃{�^�����Q�[���ɖ߂�{�^���ɂ���
		m_nButton = BUTTON_QUIT_GAME;
	}
	//�{�^���̍ő吔����
	for (int nCount = BUTTON_QUIT_GAME; nCount < BUTTON_MAX; nCount++)
	{
		//�{�^���̑I������ĂȂ����̐F�ύX�����֐��Ăяo��
		m_apButton[nCount]->ChangeTranslucent(false);
	}
	//�{�^���̑I�����F�ύX�����֐��Ăяo��
	m_apButton[m_nButton]->ChangeTranslucent(true);
}

//=============================================================================
// �������������֐�
//=============================================================================
void CPauseButtonManager::InitCreateAll(void)
{
	if (m_pPauseBG == nullptr)
	{
		m_pPauseBG = CPauseBG::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	}
	//�Q�[���ɖ߂�{�^��
	m_apButton[BUTTON_QUIT_GAME] = CQuitGameButton::Create(START_BUTTON_POSITION, SIZE);
	//�^�C�g���ɖ߂�{�^��
	m_apButton[BUTTON_BACK_TO_TITLE] = CBackToTitleButton::Create(RANKING_BUTTON_POSITION, SIZE);
	if (m_pPauseLogo == nullptr)
	{
		m_pPauseLogo = CPauseLogoTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 5, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f));
	}
}