//=======================================================================================
//
// �`���[�g���A���N���X [tutorial.cpp]
// Author : Sugawara Tsukasa
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h�t�@�C��
//=======================================================================================
#include "tutorial.h"
#include "scene_2d.h"
#include "manager.h"
#include "keyboard.h"
#include "joypad.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "sound.h"
#include "joypad.h"
#include "resource_manager.h"
#include "keyboard_texture.h"
#include "pad_texture.h"
#include "mode_base.h"

//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CTutorial::CTutorial()
{
	m_pKeyboardTexture = nullptr;
	m_pPadTexture = nullptr;
}

//=======================================================================================
// �f�X�g���N�^
//=======================================================================================
CTutorial::~CTutorial()
{
	// �I������
	Uninit();
}

//=======================================================================================
// ����������
//=======================================================================================
HRESULT CTutorial::Init(void)
{
	// �L�[�{�[�h�擾
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	// �p�b�h�擾
	CInputJoypad * pJoypad = CManager::GetJoypad();
	// �p�b�h�擾
	LPDIRECTINPUTDEVICE8 P1_PAD = CInputJoypad::GetController(0);
	if (P1_PAD == nullptr)
	{
		m_pKeyboardTexture = CKeyboardTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	}
	else
	{
		m_pPadTexture = CPadTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	}
	return S_OK;
}

//=======================================================================================
// �I������
//=======================================================================================
void CTutorial::Uninit(void)
{
}

//=======================================================================================
// �X�V����
//=======================================================================================
void CTutorial::Update(void)
{
	// �L�[�{�[�h�擾
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	// �p�b�h�擾
	CInputJoypad * pJoypad = CManager::GetJoypad();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();
	if (pKeyboard->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE || pJoypad != nullptr && pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, 0) && mode == CFade::FADE_MODE_NONE)
	{
		// �J��
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_TITLE);
	}
}

//=======================================================================================
// �`�揈��
//=======================================================================================
void CTutorial::Draw(void)
{

}
