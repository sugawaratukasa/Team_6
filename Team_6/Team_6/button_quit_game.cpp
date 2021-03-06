//=============================================================================
//
// ゲームに戻るボタン [button_quit_game.cpp]
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
#include "button_quit_game.h"
#include "texture.h"
#include "resource_manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CQuitGameButton::CQuitGameButton()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CQuitGameButton::~CQuitGameButton()
{
}

//=============================================================================
// 生成処理関数呼び出し
//=============================================================================
CQuitGameButton * CQuitGameButton::Create(D3DXVECTOR3 Position,D3DXVECTOR3 Size)
{
	//ゲームに戻るボタンのポインタ
	CQuitGameButton * pQuitGameButton = nullptr;
	//ゲームに戻るボタンポインタがnullptrの場合
	if (pQuitGameButton == nullptr)
	{
		//ゲームに戻るボタンのメモリ確保
		pQuitGameButton = new CQuitGameButton;
		//ゲームに戻るボタンのポインタがnullptrではない場合
		if (pQuitGameButton != nullptr)
		{
			//ゲームに戻るボタンの位置設定
			pQuitGameButton->SetPos(Position);
			//ゲームに戻るボタンのサイズ設定
			pQuitGameButton->SetSize(Size);
			//ゲームに戻るボタンの初期化処理関数呼び出し
			pQuitGameButton->Init(Position,Size);
		}
	}
	//ゲームに戻るボタンのポインタを返す
	return pQuitGameButton;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CQuitGameButton::Init(D3DXVECTOR3 Position, D3DXVECTOR3 Size)
{
	//ボタンの初期化処理関数呼び出し
	CButton::Init(Position,Size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_BUTTON_QUIT_GAME));
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CQuitGameButton::Uninit(void)
{
	//ボタンの終了処理関数呼び出し
	CButton::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CQuitGameButton::Update(void)
{
	//ボタンの更新処理関数呼び出し
	CButton::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CQuitGameButton::Draw(void)
{
	//ボタンの描画処理関数呼び出し
	CButton::Draw();
}

//=============================================================================
// プレス処理関数
//=============================================================================
void CQuitGameButton::Press(void)
{
	//押したときのサウンド再生
	PlayButtonSE(CButton::BUTTON_SE_PUSH);
	CScene::SetPause(false);
}