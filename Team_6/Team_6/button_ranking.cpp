//=============================================================================
//
// スタートボタン [button_start.cpp]
// Author : 二階堂汰一
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "button_ranking.h"
#include "texture.h"
#include "resource_manager.h"
#include "fade.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CRankingButton::CRankingButton()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CRankingButton::~CRankingButton()
{
}

//=============================================================================
// 生成処理関数呼び出し
//=============================================================================
CRankingButton * CRankingButton::Create(D3DXVECTOR3 Position, D3DXVECTOR3 SIze)
{
	//ランキングボタンのポインタ
	CRankingButton * pRankingButton = nullptr;
	//ランキングボタンのポインタがnullptrの場合
	if (pRankingButton == nullptr)
	{
		//ランキングボタンのメモリ確保
		pRankingButton = new CRankingButton;
		//ランキングボタンのポインタがnullptrではない場合
		if (pRankingButton != nullptr)
		{
			//ランキングボタンの初期化処理関数呼び出し
			pRankingButton->Init(Position, SIze);
		}
	}
	//ランキングボタンのポインタを返す
	return pRankingButton;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CRankingButton::Init(D3DXVECTOR3 Position, D3DXVECTOR3 Size)
{
	CButton::Init(Position, Size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_BUTTON_RANKING));
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CRankingButton::Uninit(void)
{
	//ボタンの終了処理関数呼び出し
	CButton::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CRankingButton::Update(void)
{
	//ボタンの更新処理関数呼び出し
	CButton::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CRankingButton::Draw(void)
{
	//ボタンの描画処理関数呼び出し
	CButton::Draw();
}

//=============================================================================
// プレス処理関数
//=============================================================================
void CRankingButton::Press(void)
{
	//押したときのサウンド再生
	PlayButtonSE(CButton::BUTTON_SE_PUSH);
	// 遷移
	CFade *pFade = CManager::GetFade();
	pFade->SetFade(CManager::MODE_TYPE_RANKING_BOARD);
}