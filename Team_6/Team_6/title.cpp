//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "title.h"
#include "renderer.h"
#include "input.h"
#include "scene_2d.h"
#include "logo_title.h"
#include "bg_title.h"
#include "title_button_manager.h"
#include "fade.h"
#include "Movie.h"
//=============================================================================
// マクロ定義
//=============================================================================

#define TRANSITION_WAIT_LENGTH	(300)

//=============================================================================
// コンストラクタ
//=============================================================================
CTitle::CTitle()
{
	m_pTitleButtonManager = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CTitle::~CTitle()
{
	// 終了処理
	Uninit();
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitle::Init(void)
{
	// 生成処理関数呼び出し
	CreateAll();
	// カウンタ初期化
	m_nCountToMovie = 0;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	if (m_pTitleButtonManager != nullptr)
	{
		// タイトルボタンマネージャーの終了処理関数呼び出し
		m_pTitleButtonManager->Uninit();
		m_pTitleButtonManager = nullptr;
	}


}

//=============================================================================
// 更新処理
//=============================================================================
void CTitle::Update(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	// 動画開始までのカウンターを加算
	if (!pRenderer->GetIsUseMovie())
	{
		if (m_pTitleButtonManager != nullptr)
		{
			// タイトルボタンマネージャーの更新処理関数呼び出し
			m_pTitleButtonManager->Update();
		}

		m_nCountToMovie++;
	}
	if (m_nCountToMovie >= TRANSITION_WAIT_LENGTH && 
		!pRenderer->GetIsUseMovie())
	{
		m_nCountToMovie = 0;
		// 画面遷移
		pRenderer->SetIsUseMovie(true);
		CManager::GetMovie()->ChangeMovie(L"./data/Movie/Test.avi",true);
		CManager::GetMovie()->Init();
		CManager::GetMovie()->Play();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CTitle::Draw(void)
{
}
//=============================================================================
// 生成処理関数
//=============================================================================
void CTitle::CreateAll(void)
{
	CTitleBG::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	CTitleLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 200.0f, 0.0f), D3DXVECTOR3(700.0f, 130.0f, 0.0f));
	if (m_pTitleButtonManager == nullptr)
	{
		// タイトルボタンマネージャーの生成
		m_pTitleButtonManager = CTitleButtonManager::Create();
	}
}


//=============================================================================
// モード遷移
//=============================================================================
void CTitle::ModeTransition(CManager::MODE_TYPE mode)
{
	// 遷移
	CFade *pFade = CManager::GetFade();
	pFade->SetFade(mode);
	m_nCountToMovie = 0;
}