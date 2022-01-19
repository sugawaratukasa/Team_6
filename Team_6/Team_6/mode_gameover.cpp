#include "mode_gameover.h"
#include "bg_gameover.h"
#include "keyboard.h"
#include "joypad.h"
#include "manager.h"
#include "fade.h"
#include "joypad.h"
#include "Movie.h"
#include "renderer.h"

CGameOver::CGameOver()
{
	m_bIsPlayedMovie = false;
}

CGameOver::~CGameOver()
{
}

HRESULT CGameOver::Init(void)
{
	CGameOverBG::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	m_bIsPlayedMovie = false;
	return S_OK;
}

void CGameOver::Uninit(void)
{
}

void CGameOver::Update(void)
{
	if (!CManager::GetRenderer()->GetIsUseMovie() && m_bIsPlayedMovie)
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
	else if (!m_bIsPlayedMovie)
	{
		CMovie *pMovie = CManager::GetMovie();
		pMovie->ChangeMovie(L"./data/Movie/MovieClear.avi", false);
		pMovie->Play();
		m_bIsPlayedMovie = true;
	}
}

void CGameOver::Draw(void)
{
}
