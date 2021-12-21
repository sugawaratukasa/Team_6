//=============================================================================
//
// 独房の鍵の説明テクスチャ [item_guid_prison_key.cpp]
// Author : 二階堂　汰一
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "item_guid_prison_key.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "prison_key_texture.h"
#include "keyboard.h"
#include "joypad.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CPrisonKeyGuid::CPrisonKeyGuid(PRIORITY Priority)
{
	m_pPrisonKeyTexture = nullptr;	// 看守室の鍵テクスチャのポインタ
}

//=============================================================================
// デストラクタ
//=============================================================================
CPrisonKeyGuid::~CPrisonKeyGuid()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CPrisonKeyGuid * CPrisonKeyGuid::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CJailerKeyTextureのポインタ
	CPrisonKeyGuid *pPrisonKeyGuid = nullptr;

	// nullcheck
	if (pPrisonKeyGuid == nullptr)
	{
		// メモリ確保
		pPrisonKeyGuid = new CPrisonKeyGuid;

		// !nullcheck
		if (pPrisonKeyGuid != nullptr)
		{
			// 初期化処理
			pPrisonKeyGuid->Init(pos, size);
		}
	}
	// ポインタを返す
	return pPrisonKeyGuid;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CPrisonKeyGuid::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン2Dの初期化処理関数呼び出し
	CScene2D::Init(pos, size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_JAILER_KEY));
	//　看守室の鍵テクスチャのポインタのnullptrチェック
	if (m_pPrisonKeyTexture == nullptr)
	{
		// 看守室の鍵テクスチャを生成する
		m_pPrisonKeyTexture = CPrisonKeyTexture::Create(ZeroVector3, ZeroVector3);
	}
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CPrisonKeyGuid::Uninit(void)
{
	// シーン2Dの終了処理関数
	CScene2D::Uninit();
	//　看守室の鍵テクスチャのポインタのnullptrチェック
	if (m_pPrisonKeyTexture != nullptr)
	{
		//　看守室の鍵テクスチャの終了処理関数
		m_pPrisonKeyTexture->Uninit();
		// 看守室の鍵テクスチャのポインタを初期化する
		m_pPrisonKeyTexture = nullptr;
	}
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CPrisonKeyGuid::Update(void)
{
	// シーン2Dの更新処理関数
	CScene2D::Update();
	//　看守室の鍵テクスチャのポインタのnullptrチェック
	if (m_pPrisonKeyTexture != nullptr)
	{
		//　看守室の鍵テクスチャの更新処理関数
		m_pPrisonKeyTexture->Update();
	}
	// 入力処理
	Input();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CPrisonKeyGuid::Draw(void)
{
	// シーン2Dの描画処理関数
	CScene2D::Draw();
	//　看守室の鍵テクスチャのポインタのnullptrチェック
	if (m_pPrisonKeyTexture != nullptr)
	{
		// 看守室の鍵テクスチャの描画処理関数
		m_pPrisonKeyTexture->Draw();
	}
}

//=============================================================================
// 入力処理関数
//=============================================================================
void CPrisonKeyGuid::Input(void)
{
	// キーボード取得
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	// パッド取得
	CInputJoypad * pJoypad = CManager::GetJoypad();
	// もしENTERキーが入力されたら
	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		//　終了処理関数
		Uninit();
	}
}
