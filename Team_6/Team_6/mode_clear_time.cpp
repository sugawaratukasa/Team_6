//=============================================================================
//
// クリアタイムクラス [mode_clear_time.cpp]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "mode_clear_time.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"
#include "keyboard.h"
#include "texture.h"
#include "sound.h"
#include "joypad.h"
#include "resource_manager.h"
#include "clear_time_bg.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define KEYBORAD_MAX	(256)														// キー
#define BG_POS			(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))	// 位置
#define TIME_POS		(D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, SCREEN_HEIGHT / 2, 0.0f))	// タイム位置
#define TIME_SIZE		(D3DXVECTOR3(100.0f, 100.0f, 0.0f))							// タイムサイズ
//=============================================================================
// コンストラクタ
//=============================================================================
CMode_Clear_Time::CMode_Clear_Time()
{
	m_pTime = nullptr;
	m_nPlayerTime = ZERO_INT;
}

//=============================================================================
// デストラクタ
//=============================================================================
CMode_Clear_Time::~CMode_Clear_Time()
{
	// 終了
	Uninit();
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMode_Clear_Time::Init(void)
{
	// プレイヤーのファイル読み込み
	ReadPlayerFile();

	// 背景生成
	CClear_Time_bg::Create(BG_POS);

	// 位置
	m_pTime = CTime::Create(TIME_POS, TIME_SIZE);

	// タイム設定
	m_pTime->SetTime(m_nPlayerTime);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMode_Clear_Time::Uninit(void)
{
	// nullptrでない場合
	if (m_pTime != nullptr)
	{
		// 終了処理
		m_pTime->Uninit();

		// nullptrに
		m_pTime = nullptr;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CMode_Clear_Time::Update(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();

	// どこのキーでも反応する様に
	for (int nCnt = ZERO_INT; nCnt <= KEYBORAD_MAX; nCnt++)
	{
		// キーが押されたかつモード遷移中でない場合
		if (pKey->GetTrigger(nCnt) && mode == CFade::FADE_MODE_NONE)
		{
			// 画面遷移
			ModeTransition();
		}
	}
	// コントローラのボタンを押した場合
	for (int nCnt = ZERO_INT; nCnt < CInputJoypad::JOY_BUTTON_MAX; nCnt++)
	{
		// キーが押されたかつモード遷移中でない場合
		if (CManager::GetJoypad()->GetJoystickTrigger(nCnt, 0) && mode == CFade::FADE_MODE_NONE)
		{
			// 画面遷移
			ModeTransition();
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CMode_Clear_Time::Draw(void)
{

}
//=============================================================================
// モード遷移
//=============================================================================
void CMode_Clear_Time::ModeTransition(void)
{
	// 遷移
	CFade *pFade = CManager::GetFade();
	pFade->SetFade(CManager::MODE_TYPE_RANKING_RESULT);
}
//=============================================================================
// プレイヤーのファイル読み込み
// Author : SugawaraTsukasa
//=============================================================================
void CMode_Clear_Time::ReadPlayerFile(void)
{
	FILE * pFile;
	// ファイルの読み込み
	pFile = fopen("data/Text/Time/Player_Time.txt", "r");

	// ファイルが空じゃないか
	if (pFile != NULL)
	{
		// 読み込み
		fscanf(pFile, "%d\n", &m_nPlayerTime);
		// ファイルを閉じる
		fclose(pFile);
	}
}
