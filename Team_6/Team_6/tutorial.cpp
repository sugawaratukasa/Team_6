//=======================================================================================
//
// チュートリアルクラス [tutorial.cpp]
// Author : Sugawara Tsukasa
//
//=======================================================================================

//=======================================================================================
// インクルードファイル
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
// コンストラクタ
//=======================================================================================
CTutorial::CTutorial()
{
	m_pKeyboardTexture = nullptr;
	m_pPadTexture = nullptr;
}

//=======================================================================================
// デストラクタ
//=======================================================================================
CTutorial::~CTutorial()
{
	// 終了処理
	Uninit();
}

//=======================================================================================
// 初期化処理
//=======================================================================================
HRESULT CTutorial::Init(void)
{
	// キーボード取得
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	// パッド取得
	CInputJoypad * pJoypad = CManager::GetJoypad();
	// パッド取得
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
// 終了処理
//=======================================================================================
void CTutorial::Uninit(void)
{
}

//=======================================================================================
// 更新処理
//=======================================================================================
void CTutorial::Update(void)
{
	// キーボード取得
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	// パッド取得
	CInputJoypad * pJoypad = CManager::GetJoypad();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();
	if (pKeyboard->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE || pJoypad != nullptr && pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, 0) && mode == CFade::FADE_MODE_NONE)
	{
		// 遷移
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_TITLE);
	}
}

//=======================================================================================
// 描画処理
//=======================================================================================
void CTutorial::Draw(void)
{

}
