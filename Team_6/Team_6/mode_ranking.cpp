//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "mode_ranking.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"
#include "keyboard.h"
#include "texture.h"
#include "sound.h"
#include "joypad.h"
#include "resource_manager.h"
#include "ranking_bg.h"
#include "ranking.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define KEYBORAD_MAX	(256)													// キー
#define BG_POS			(D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f))	// 位置
//=============================================================================
// コンストラクタ
//=============================================================================
CMode_Ranking::CMode_Ranking()
{
	m_pRankig = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CMode_Ranking::~CMode_Ranking()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMode_Ranking::Init(void)
{
	// ランキング生成処理
	RankingCreate();
	CSound * pSound = GET_SOUND_PTR;
	pSound->CSound::Play(CSound::SOUND_BGM_RANKING);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMode_Ranking::Uninit(void)
{
	// 破棄
	if (m_pRankig != nullptr)
	{
		// 終了
		m_pRankig->Uninit();

		m_pRankig = nullptr;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CMode_Ranking::Update(void)
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
void CMode_Ranking::Draw(void)
{

}

//=============================================================================
// 2Dオブジェクト生成
//=============================================================================
void CMode_Ranking::RankingCreate(void)
{
	// ランキングbg生成
	CRanking_bg::Create(BG_POS);

	// 生成
	m_pRankig = CRanking::Create();
}
//=============================================================================
// モード遷移
//=============================================================================
void CMode_Ranking::ModeTransition(void)
{
	// 遷移
	CFade *pFade = CManager::GetFade();
	pFade->SetFade(CManager::MODE_TYPE_TITLE);

	// 終了
	Uninit();
}