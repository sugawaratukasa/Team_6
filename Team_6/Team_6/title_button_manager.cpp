//=============================================================================
//
// �^�C�g���{�^���}�l�[�W���[ [title_button_manager.cpp]
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
#include "title_button_manager.h"
#include "button_start.h"
#include "button_guid.h"
#include "button_ranking.h"
#include "button_exit.h"
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define START_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))				//�X�^�[�g�{�^���̈ʒu
#define GUID_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 80.0f, 0.0f))	
#define RANKING_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 160.0f, 0.0f))	//�����L���O�{�^���̈ʒu
#define EXIT_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 240.0f, 0.0f))		//�I���{�^���̈ʒu
#define SIZE (D3DXVECTOR3(450.0f,50.0f,0.0f))														//�T�C�Y
#define STICK_REACTION		(500.0f)																// �X�e�B�b�N�͈̔�
#define STICK_REACTION_MIN	(0.0f)																	// �X�e�B�b�N�͈̔�

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitleButtonManager::CTitleButtonManager()
{
	memset(m_apButton, NULL, sizeof(m_apButton));	//�{�^���̃|�C���^
	m_nButton = BUTTON_NONE;						//�{�^��
	m_bStick = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitleButtonManager::~CTitleButtonManager()
{
}

//=============================================================================
// ���������֐��Ăяo��
//=============================================================================
CTitleButtonManager * CTitleButtonManager::Create(void)
{
	//�^�C�g���{�^���}�l�[�W���[�̃|�C���^
	CTitleButtonManager * pTitleButtonManager = nullptr;
	//�^�C�g���{�^���}�l�[�W���[�|�C���^��nullptr�̏ꍇ
	if (pTitleButtonManager == nullptr)
	{
		//�^�C�g���{�^���}�l�[�W���[�̃������m��
		pTitleButtonManager = new CTitleButtonManager;
		//�^�C�g���{�^���}�l�[�W���[�̃|�C���^��nullptr�ł͂Ȃ��ꍇ
		if (pTitleButtonManager != nullptr)
		{
			//�^�C�g���{�^���}�l�[�W���[�̏����������֐��Ăяo��
			pTitleButtonManager->Init();
		}
	}
	//�^�C�g���{�^���}�l�[�W���[�̃|�C���^��Ԃ�
	return pTitleButtonManager;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CTitleButtonManager::Init(void)
{
	//�����S�������֐��Ăяo��
	InitCreateAll();
	//�{�^���̏����ݒ�
	m_nButton = BUTTON_START;
	//�{�^���̏����I�������֐��Ăяo��
	m_apButton[m_nButton]->ChangeTranslucent(true);
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CTitleButtonManager::Uninit(void)
{
	//�{�^���̍ő吔����
	for (int nCount = 0; nCount < BUTTON_MAX; nCount++)
	{
		//�e�{�^���̏I�������֐��Ăяo��
		m_apButton[nCount]->Uninit();
	}
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CTitleButtonManager::Update(void)
{
	//���͏����֐��Ăяo��
	PlayerItemGet();
	//�I�������֐��Ăяo��
	Select();
}

//=============================================================================
// ���͏����֐�
//=============================================================================
void CTitleButtonManager::PlayerItemGet(void)
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
		m_nButton--;
		//�{�^���̑I�������Đ������֐��Ăяo��
		m_apButton[m_nButton]->PlayButtonSE(CButton::BUTTON_SE_SELECT);
	}
	//�����L�[�����͂��ꂽ�ꍇ
	if (pKeyboard->GetTrigger(DIK_DOWN) && mode == CFade::FADE_MODE_NONE)
	{
		//���݂̃{�^�������Z����
		m_nButton++;
		//�{�^���̑I�������Đ������֐��Ăяo��
		m_apButton[m_nButton]->PlayButtonSE(CButton::BUTTON_SE_SELECT);
	}
	//����ENTER�L�[���̓W���C�X�e�B�b�N��A�{�^���������ꂽ��
	if (pKeyboard->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE || pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A,0) && mode == CFade::FADE_MODE_NONE)
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
			m_nButton--;
		}
		// �X�e�B�b�N���͈͂��z������
		if (js.lY >= STICK_REACTION)
		{
			// true��
			m_bStick = true;

			// �C���N�������g
			m_nButton++;
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
void CTitleButtonManager::Select(void)
{
	//�������݂̃{�^�����X�^�[�g�{�^����艺��������
	if (m_nButton < BUTTON_START)
	{
		//���݂̃{�^�����I���{�^���ɂ���
		m_nButton = BUTTON_EXIT;
	}
	//�������݂̃{�^�����I���{�^�����z������
	if (m_nButton > BUTTON_EXIT)
	{
		//���݂̃{�^�����X�^�[�g�{�^���ɂ���
		m_nButton = BUTTON_START;
	}
	//�{�^���̍ő吔����
	for (int nCount = 0; nCount < BUTTON_MAX; nCount++)
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
void CTitleButtonManager::InitCreateAll(void)
{
	//�X�^�[�g�{�^������
	m_apButton[BUTTON_START] = CStartButton::Create(START_BUTTON_POSITION, SIZE);
	//��������{�^������
	m_apButton[BUTTON_GUID] = CGuidButton::Create(GUID_BUTTON_POSITION, SIZE);
	//�����L���O�{�^������
	m_apButton[BUTTON_RANKING] = CRankingButton::Create(RANKING_BUTTON_POSITION, SIZE);
	//�I���{�^��
	m_apButton[BUTTON_EXIT] = CExitButton::Create(EXIT_BUTTON_POSITION, SIZE);
}