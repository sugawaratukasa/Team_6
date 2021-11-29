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
#include "button_ranking.h"
#include "button_exit.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define START_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))				//スタートボタンの位置
#define RANKING_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 80.0f, 0.0f))	//ランキングボタンの位置
#define EXIT_BUTTON_POSITION (D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 160.0f, 0.0f))		//終了ボタンの位置
#define SIZE (D3DXVECTOR3(450.0f,50.0f,0.0f))														//サイズ

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
	// パッド取得
	LPDIRECTINPUTDEVICE8 P1_PAD = CInputJoypad::GetController(0);
	//上矢印キーが入力された場合
	if (pKeyboard->GetTrigger(DIK_UP))
	{
		//現在のボタンを減算する
		m_nButton--;
		//ボタンの選択時音再生処理関数呼び出し
		m_apButton[m_nButton]->PlayButtonSE(CButton::BUTTON_SE_SELECT);
	}
	//下矢印キーが入力された場合
	if (pKeyboard->GetTrigger(DIK_DOWN))
	{
		//現在のボタンを減算する
		m_nButton++;
		//ボタンの選択時音再生処理関数呼び出し
		m_apButton[m_nButton]->PlayButtonSE(CButton::BUTTON_SE_SELECT);
	}
	//もしENTERキー又はジョイスティックのAボタンを押されたら
	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		//ボタンのプレス処理関数呼び出し
		m_apButton[m_nButton]->Press();
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
	//ランキングボタン生成
	m_apButton[BUTTON_RANKING] = CRankingButton::Create(RANKING_BUTTON_POSITION, SIZE);
	//終了ボタン
	m_apButton[BUTTON_EXIT] = CExitButton::Create(EXIT_BUTTON_POSITION, SIZE);
}