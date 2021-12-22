//=============================================================================
//
// マネージャー処理 [manager.cpp]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "fade.h"
#include "game.h"
#include "input.h"
#include "joypad.h"
#include "keyboard.h"
#include "manager.h"
#include "resource_manager.h"
#include "model.h"
#include "player.h"
#include "renderer.h"
#include "scene3D.h"
#include "sound.h"
#include "texture.h"
#include "title.h"
#include "tutorial.h"
#include "result.h"
#include "xfile.h"
#include "polygon.h"

#include "Movie.h"
#include "mode_ranking.h"
#include "map_spot.h"
#include "particle_manager.h"
#include "mode_gameover.h"
#include "mode_ranking_board.h"
//=============================================================================
//静的メンバ変数宣言
//=============================================================================
CManager::MODE_TYPE CManager::m_mode = CManager::MODE_TYPE_TITLE;
unique_ptr<CRenderer> CManager::m_pRenderer = nullptr;
unique_ptr<CInputKeyboard> CManager::m_pInput = nullptr;
unique_ptr<CFade> CManager::m_pFade = nullptr;
unique_ptr<CInputJoypad> CManager::m_pJoypad = nullptr;
unique_ptr<CScene> CManager::m_pScene = nullptr;
unique_ptr<CResourceManager> CManager::m_pResourceManager = nullptr;
unique_ptr<CModeBase> CManager::m_pModeBase = nullptr;

unique_ptr<CMovie> CManager::m_pMovie = nullptr;
unique_ptr<CParticle_Manager> CManager::m_pParticle_Manager = nullptr;
//=============================================================================
// コンストラクタ
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// メモリ確保
	m_pRenderer.reset(new CRenderer);
	m_pInput.reset(new CInputKeyboard);
	m_pJoypad.reset(new CInputJoypad);
	m_pFade.reset(new CFade);
	m_pResourceManager.reset(CResourceManager::GetInstance());

	m_pMovie.reset(new CMovie);
	m_pParticle_Manager.reset(new CParticle_Manager);

	//メモリが確保できたら
	if (m_pRenderer != nullptr)
	{
		// 初期化処理
		if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
		{
			return -1;
		}
	}

	//メモリが確保できたら
	if (m_pInput != nullptr)
	{
		if (FAILED(m_pInput->Init(hInstance, hWnd)))
		{
			return -1;
		}
	}

	//メモリが確保できたら
	if (m_pJoypad != nullptr)
	{
		if (FAILED(m_pJoypad->Init(hInstance, hWnd)))
		{
			return -1;
		}
	}

	// !nullcheck
	if (m_pFade != nullptr)
	{
		// 初期化処理
		m_pFade->Init();
	}
	// !nullcheck

	if (m_pParticle_Manager != nullptr)
	{
		// 初期化処理
		m_pParticle_Manager->Init();
	}

	// !nullcheck
	if (m_pMovie != nullptr)
	{
		// 初期化処理
		m_pMovie->Init();
	}

	//全テクスチャの読み込み
	LoadAll();

	CMapSpot::LoadSpot();
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CManager::Uninit(void)
{
	// !nullcheck
	if (m_pParticle_Manager != nullptr)
	{
		// パーティクルマネージャー終了
		m_pParticle_Manager.reset();
		m_pParticle_Manager = nullptr;
	}

	// !nullchack
	if (m_pFade != nullptr)
	{
		//フェードクラスの終了処理呼び出し
		m_pFade->Uninit();
		m_pFade.reset();
		m_pFade = nullptr;
	}

	// !nullcheck
	if (m_pResourceManager != nullptr)
	{
		// リソースのロード
		m_pResourceManager.reset();
		m_pResourceManager = nullptr;

	}

	// !nullchack
	if (m_pInput != nullptr)
	{
		//入力処理クラスの終了処理呼び出し
		m_pInput->Uninit();

		//メモリの削除
		m_pInput.reset();
		m_pInput = nullptr;
	}

	// !nullchack
	if (m_pJoypad != nullptr)
	{
		//入力処理クラスの終了処理呼び出し
		m_pJoypad->Uninit();

		//メモリの削除
		m_pJoypad.reset();
		m_pJoypad = nullptr;
	}

	//メモリ開放
	if (m_pRenderer != nullptr)
	{
		// 描画クラス
		m_pRenderer.reset();
		m_pRenderer = nullptr;
	}

	if (m_pModeBase != nullptr)
	{
		// 描画クラス
		m_pModeBase.reset();
		m_pModeBase = nullptr;
	}

	// シーン情報のリリース
	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{
	if (m_pInput != nullptr)
	{
		//入力処理クラスの更新処理呼び出し
		m_pInput->Update();
	}

	if (m_pJoypad != nullptr)
	{
		//入力処理クラスの更新処理呼び出し
		m_pJoypad->Update();
	}

	if (m_pRenderer != nullptr)
	{
		//レンダラークラスの更新処理呼び出し
		m_pRenderer->Update();
	}

	if (m_pFade != nullptr)
	{
		//フェードクラスの更新処理呼び出し
		m_pFade->Update();
	}

	// モードの更新処理
	if (m_pModeBase != nullptr)
	{
		m_pModeBase->Update();
	}

	// モードの更新処理
	if (m_pMovie != nullptr)
	{
		m_pMovie->Update();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != nullptr)
	{
		//レンダラークラスの描画処理呼び出し
		m_pRenderer->Draw();
	}

	// モードの更新処理
	if (m_pModeBase != nullptr)
	{
		m_pModeBase->Draw();
	}
}

//=============================================================================
// テクスチャの全ロード処理
//=============================================================================
void CManager::LoadAll(void)
{
	// !nullcheck
	if (m_pResourceManager != nullptr)
	{
		// リソースのロード
		m_pResourceManager->LoadAll();
	}
	
}

//=============================================================================
// ゲームモードの設定処理
//=============================================================================
void CManager::SetMode(MODE_TYPE mode)
{
	// !nullcheck
	if (m_pModeBase != nullptr)
	{
		//メモリ開放
		m_pModeBase.reset();
		m_pModeBase = nullptr;
	}

	// サウンドの情報
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();

	//サウンドストップ
	pSound->StopAll();

	// シーン情報のリリース
	CScene::ReleaseAll();

	// モードを変える
	m_mode = mode;

	//設定されたモードをクリエイト
	switch (m_mode)
	{
		// タイトル
	case MODE_TYPE_TITLE:
		// タイトル生成
		m_pModeBase.reset(new CTitle);
		break;


		// チュートリアル
	case MODE_TYPE_TUTORIAL:
		// チュートリアル生成
		m_pModeBase.reset(new CTutorial);
		break;

		// ゲーム
	case MODE_TYPE_GAME:
		// ゲーム生成
		m_pModeBase.reset(new CGame);
		break;
		// ゲーム
	case MODE_TYPE_RESULT:
		// ゲーム生成
		m_pModeBase.reset(new CResult);
		break;
		// リザルト
	case MODE_TYPE_RANKING_RESULT:
		// ゲーム生成
		m_pModeBase.reset(new CMode_Ranking);
		break;
		// ランキングボード
	case MODE_TYPE_RANKING_BOARD:
		// ゲーム生成
		m_pModeBase.reset(new CMode_Ranking_Board);
		break;
	case MODE_TYPE_GAMEOVER:
		// ゲーム生成
		m_pModeBase.reset(new CGameOver);
		break;
	default:
		break;
	}

	// !nullcheck
	if (m_pModeBase != nullptr)
	{
		// 初期化処理
		m_pModeBase->Init();
	}
}

//=============================================================================
//ゲームモード情報の取得
//=============================================================================
CManager::MODE_TYPE CManager::GetMode(void)
{
	return m_mode;
}

//=============================================================================
// ゲームモード情報
//=============================================================================
CModeBase * CManager::GetModeBase(void)
{
	// !nullcheck
	if (m_pModeBase != nullptr)
	{
		// ポインタを返す
		return m_pModeBase.get();
	}

	return nullptr;
}

//=============================================================================
// ゲーム情報
//=============================================================================
CModeBase * CManager::GetModePtr(void)
{
	//キャスト
	CModeBase *pMode = ((CModeBase*)m_pModeBase.get());

	// !nullcheck
	if (pMode != nullptr)
	{
		return pMode;
	}
	return nullptr;
}