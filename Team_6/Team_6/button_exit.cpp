//=============================================================================
//
// スタートボタン [button_exit.cpp]
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
#include "button_exit.h"
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
CExitButton::CExitButton()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CExitButton::~CExitButton()
{
}

//=============================================================================
// 生成処理関数呼び出し
//=============================================================================
CExitButton * CExitButton::Create(D3DXVECTOR3 Position, D3DXVECTOR3 SIze)
{
	//終了ボタンのポインタ
	CExitButton * pExitButton = nullptr;
	//終了ボタンのポインタがnullptrの場合
	if (pExitButton == nullptr)
	{
		//終了ボタンのメモリ確保
		pExitButton = new CExitButton;
		//終了ボタンのポインタがnullptrではない場合
		if (pExitButton != nullptr)
		{
			//終了ボタンの初期化処理関数呼び出し
			pExitButton->Init(Position, SIze);
		}
	}
	//終了ボタンのポインタを返す
	return pExitButton;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CExitButton::Init(D3DXVECTOR3 Position, D3DXVECTOR3 Size)
{
	CButton::Init(Position, Size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_BUTTON_EXIT));
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CExitButton::Uninit(void)
{
	//ボタンの終了処理関数呼び出し
	CButton::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CExitButton::Update(void)
{
	//ボタンの更新処理関数呼び出し
	CButton::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CExitButton::Draw(void)
{
	//ボタンの描画処理関数呼び出し
	CButton::Draw();
}

//=============================================================================
// プレス処理関数
//=============================================================================
void CExitButton::Press(void)
{
	exit(0);
}