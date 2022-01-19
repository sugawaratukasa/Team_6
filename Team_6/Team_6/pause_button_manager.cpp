//=============================================================================
//
// ポーズボタンマネージャー [pause_button_manager.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
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
// マクロ定義
//*****************************************************************************
#define START_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))				//スタートボタンの位置
#define RANKING_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 80.0f, 0.0f))	//ランキングボタンの位置
#define EXIT_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 160.0f, 0.0f))		//終了ボタンの位置
#define SIZE (D3DXVECTOR3(450.0f,50.0f,0.0f))														//サイズ
#define STICK_REACTION		(500.0f)																// スティックの範囲
#define STICK_REACTION_MIN	(0.0f)																	// スティックの範囲
//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CPauseButtonManager::CPauseButtonManager()
{
	memset(m_apButton, NULL, sizeof(m_apButton));	//ボタンのポインタ
	m_pPauseBG = nullptr;
	m_pPauseLogo = nullptr;
	m_nButton = BUTTON_NONE;						//ボタン
	m_bStick = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPauseButtonManager::~CPauseButtonManager()
{
}

//=============================================================================
// 生成処理関数呼び出し
//=============================================================================
CPauseButtonManager * CPauseButtonManager::Create(void)
{
	//タイトルボタンマネージャーのポインタ
	CPauseButtonManager * pPauseButtonManager = nullptr;
	//タイトルボタンマネージャーポインタがnullptrの場合
	if (pPauseButtonManager == nullptr)
	{
		//タイトルボタンマネージャーのメモリ確保
		pPauseButtonManager = new CPauseButtonManager;
		//タイトルボタンマネージャーのポインタがnullptrではない場合
		if (pPauseButtonManager != nullptr)
		{
			//タイトルボタンマネージャーの初期化処理関数呼び出し
			pPauseButtonManager->Init();
		}
	}
	//タイトルボタンマネージャーのポインタを返す
	return pPauseButtonManager;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CPauseButtonManager::Init(void)
{
	//初期全性処理関数呼び出し
	InitCreateAll();
	//ボタンの初期設定
	m_nButton = BUTTON_QUIT_GAME;
	//ボタンの初期選択処理関数呼び出し
	m_apButton[m_nButton]->ChangeTranslucent(true);
	// シーンにポーズを適応させる
	CScene::SetPause(true);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CPauseButtonManager::Uninit(void)
{
	//ボタンの最大数分回す
	for (int nCount = 0; nCount < BUTTON_MAX; nCount++)
	{
		//各ボタンの終了処理関数呼び出し
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
// 更新処理関数
//=============================================================================
void CPauseButtonManager::Update(void)
{
	//入力処理関数呼び出し
	PlayerItemGet();
	//選択処理関数呼び出し
	Select();
}

//=============================================================================
// 入力処理関数
//=============================================================================
void CPauseButtonManager::PlayerItemGet(void)
{
	// キーボード取得
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	CInputJoypad * pJoypad = CManager::GetJoypad();
	// パッド取得
	LPDIRECTINPUTDEVICE8 P1_PAD = CInputJoypad::GetController(0);

	// スティック取得
	DIJOYSTATE js = CInputJoypad::GetStick(0);

	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();
	//上矢印キーが入力された場合
	if (pKeyboard->GetTrigger(DIK_UP) && mode == CFade::FADE_MODE_NONE)
	{
		//現在のボタンを減算する
		m_nButton++;
		//ボタンの選択時音再生処理関数呼び出し
		m_apButton[m_nButton]->PlayButtonSE(CButton::BUTTON_SE_SELECT);
	}
	//下矢印キーが入力された場合
	if (pKeyboard->GetTrigger(DIK_DOWN) && mode == CFade::FADE_MODE_NONE)
	{
		//現在のボタンを減算する
		m_nButton--;
		//ボタンの選択時音再生処理関数呼び出し
		m_apButton[m_nButton]->PlayButtonSE(CButton::BUTTON_SE_SELECT);
	}
	//もしENTERキー又はジョイスティックのAボタンを押されたら
	if (pKeyboard->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE || pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, 0) && mode == CFade::FADE_MODE_NONE)
	{
		//ボタンのプレス処理関数呼び出し
		m_apButton[m_nButton]->Press();
	}
	// falseの場合
	if (m_bStick == false)
	{
		// スティックが範囲を越えたら
		if (js.lY <= -STICK_REACTION)
		{
			// trueに
			m_bStick = true;

			// インクリメント
			m_nButton++;
		}
		// スティックが範囲を越えたら
		if (js.lY >= STICK_REACTION)
		{
			// trueに
			m_bStick = true;

			// インクリメント
			m_nButton--;
		}
	}
	else
	{
		// スティックが範囲外の場合
		if (js.lY >= -STICK_REACTION && js.lY <= STICK_REACTION_MIN)
		{
			// falseに
			m_bStick = false;
		}
		// スティックが範囲外の場合
		if (js.lY <= STICK_REACTION && js.lY >= STICK_REACTION_MIN)
		{
			// falseに
			m_bStick = false;
		}
	}
}

//=============================================================================
// 選択処理関数
//=============================================================================
void CPauseButtonManager::Select(void)
{
	//もし現在のボタンがゲームに戻るボタンより下だったら
	if (m_nButton < BUTTON_QUIT_GAME)
	{
		//現在のボタンをタイトルに戻るボタンにする
		m_nButton = BUTTON_BACK_TO_TITLE;
	}
	//もし現在のボタンが終了ボタンを越えたら
	if (m_nButton > BUTTON_BACK_TO_TITLE)
	{
		//現在のボタンをゲームに戻るボタンにする
		m_nButton = BUTTON_QUIT_GAME;
	}
	//ボタンの最大数分回す
	for (int nCount = BUTTON_QUIT_GAME; nCount < BUTTON_MAX; nCount++)
	{
		//ボタンの選択されてない時の色変更処理関数呼び出し
		m_apButton[nCount]->ChangeTranslucent(false);
	}
	//ボタンの選択時色変更処理関数呼び出し
	m_apButton[m_nButton]->ChangeTranslucent(true);
}

//=============================================================================
// 初期生成処理関数
//=============================================================================
void CPauseButtonManager::InitCreateAll(void)
{
	if (m_pPauseBG == nullptr)
	{
		m_pPauseBG = CPauseBG::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	}
	//ゲームに戻るボタン
	m_apButton[BUTTON_QUIT_GAME] = CQuitGameButton::Create(START_BUTTON_POSITION, SIZE);
	//タイトルに戻るボタン
	m_apButton[BUTTON_BACK_TO_TITLE] = CBackToTitleButton::Create(RANKING_BUTTON_POSITION, SIZE);
	if (m_pPauseLogo == nullptr)
	{
		m_pPauseLogo = CPauseLogoTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 5, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f));
	}
}