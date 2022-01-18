#include "mode_gameover.h"
#include "bg_gameover.h"
#include "keyboard.h"
#include "joypad.h"
#include "manager.h"
#include "fade.h"
#include "joypad.h"
CGameOver::CGameOver()
{
}

CGameOver::~CGameOver()
{
}

HRESULT CGameOver::Init(void)
{
	CGameOverBG::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	return S_OK;
}

void CGameOver::Uninit(void)
{
}

void CGameOver::Update(void)
{
	// キーボード取得
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	CInputJoypad *pPad = CManager::GetJoypad();

	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();

	if (pKeyboard->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE || 
		pPad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, 0) && mode == CFade::FADE_MODE_NONE)
	{
		// 遷移
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_TITLE);
	}
}

void CGameOver::Draw(void)
{
}
