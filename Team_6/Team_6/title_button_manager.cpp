//=============================================================================
//
// タイトルボタンマネージャー [title_button_manager.cpp]
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
#include "title_button_manager.h"
#include "button_start.h"
#include "button_guid.h"
#include "button_ranking.h"
#include "button_exit.h"
#include "fade.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define START_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))				//スタートボタンの位置
#define GUID_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 80.0f, 0.0f))	
#define RANKING_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 160.0f, 0.0f))	//ランキングボタンの位置
#define EXIT_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 240.0f, 0.0f))		//終了ボタンの位置
#define SIZE (D3DXVECTOR3(450.0f,50.0f,0.0f))														//サイズ
#define STICK_REACTION		(500.0f)																// スティックの範囲
#define STICK_REACTION_MIN	(0.0f)																	// スティックの範囲

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CTitleButtonManager::CTitleButtonManager()
{
	memset(m_apButton, NULL, sizeof(m_apButton));	//ボタンのポインタ
	m_nButton = BUTTON_NONE;						//ボタン
	m_bStick = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CTitleButtonManager::~CTitleButtonManager()
{
}

//=============================================================================
// 生成処理関数呼び出し
//=============================================================================
CTitleButtonManager * CTitleButtonManager::Create(void)
{
	//タイトルボタンマネージャーのポインタ
	CTitleButtonManager * pTitleButtonManager = nullptr;
	//タイトルボタンマネージャーポインタがnullptrの場合
	if (pTitleButtonManager == nullptr)
	{
		//タイトルボタンマネージャーのメモリ確保
		pTitleButtonManager = new CTitleButtonManager;
		//タイトルボタンマネージャーのポインタがnullptrではない場合
		if (pTitleButtonManager != nullptr)
		{
			//タイトルボタンマネージャーの初期化処理関数呼び出し
			pTitleButtonManager->Init();
		}
	}
	//タイトルボタンマネージャーのポインタを返す
	return pTitleButtonManager;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CTitleButtonManager::Init(void)
{
	//初期全性処理関数呼び出し
	InitCreateAll();
	//ボタンの初期設定
	m_nButton = BUTTON_START;
	//ボタンの初期選択処理関数呼び出し
	m_apButton[m_nButton]->ChangeTranslucent(true);
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CTitleButtonManager::Uninit(void)
{
	//ボタンの最大数分回す
	for (int nCount = 0; nCount < BUTTON_MAX; nCount++)
	{
		//各ボタンの終了処理関数呼び出し
		m_apButton[nCount]->Uninit();
	}
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CTitleButtonManager::Update(void)
{
	//入力処理関数呼び出し
	PlayerItemGet();
	//選択処理関数呼び出し
	Select();
}

//=============================================================================
// 入力処理関数
//=============================================================================
void CTitleButtonManager::PlayerItemGet(void)
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
		m_nButton--;
		//ボタンの選択時音再生処理関数呼び出し
		m_apButton[m_nButton]->PlayButtonSE(CButton::BUTTON_SE_SELECT);
	}
	//下矢印キーが入力された場合
	if (pKeyboard->GetTrigger(DIK_DOWN) && mode == CFade::FADE_MODE_NONE)
	{
		//現在のボタンを減算する
		m_nButton++;
		//ボタンの選択時音再生処理関数呼び出し
		m_apButton[m_nButton]->PlayButtonSE(CButton::BUTTON_SE_SELECT);
	}
	//もしENTERキー又はジョイスティックのAボタンを押されたら
	if (pKeyboard->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE || pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A,0) && mode == CFade::FADE_MODE_NONE)
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
			m_nButton--;
		}
		// スティックが範囲を越えたら
		if (js.lY >= STICK_REACTION)
		{
			// trueに
			m_bStick = true;

			// インクリメント
			m_nButton++;
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
void CTitleButtonManager::Select(void)
{
	//もし現在のボタンがスタートボタンより下だったら
	if (m_nButton < BUTTON_START)
	{
		//現在のボタンを終了ボタンにする
		m_nButton = BUTTON_EXIT;
	}
	//もし現在のボタンが終了ボタンを越えたら
	if (m_nButton > BUTTON_EXIT)
	{
		//現在のボタンをスタートボタンにする
		m_nButton = BUTTON_START;
	}
	//ボタンの最大数分回す
	for (int nCount = 0; nCount < BUTTON_MAX; nCount++)
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
void CTitleButtonManager::InitCreateAll(void)
{
	//スタートボタン生成
	m_apButton[BUTTON_START] = CStartButton::Create(START_BUTTON_POSITION, SIZE);
	//操作説明ボタン生成
	m_apButton[BUTTON_GUID] = CGuidButton::Create(GUID_BUTTON_POSITION, SIZE);
	//ランキングボタン生成
	m_apButton[BUTTON_RANKING] = CRankingButton::Create(RANKING_BUTTON_POSITION, SIZE);
	//終了ボタン
	m_apButton[BUTTON_EXIT] = CExitButton::Create(EXIT_BUTTON_POSITION, SIZE);
}