#include "main.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "scene_2d.h"
#include "keyboard_texture.h"
#include "sound.h"

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CKeyboardTexture::CKeyboardTexture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CKeyboardTexture::~CKeyboardTexture()
{
}

CKeyboardTexture * CKeyboardTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CKeyboardTextureのポインタ
	CKeyboardTexture *pKeyboardTexture = nullptr;

	// nullcheck
	if (pKeyboardTexture == nullptr)
	{
		// メモリ確保
		pKeyboardTexture = new CKeyboardTexture;

		// !nullcheck
		if (pKeyboardTexture != nullptr)
		{
			// 初期化処理
			pKeyboardTexture->Init(pos, size);
		}
	}
	// ポインタを返す
	return pKeyboardTexture;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CKeyboardTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン2Dの初期化処理関数呼び出し
	CScene2D::Init(pos, size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_KEYBOARD_GUID));
	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CKeyboardTexture::Uninit(void)
{
	// シーン2Dの終了処理関数呼び出し
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CKeyboardTexture::Update(void)
{
	// シーン2Dの更新処理関数呼び出し
	CScene2D::Update();
}

//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CKeyboardTexture::Draw(void)
{
	// シーン2Dの描画処理関数呼び出し
	CScene2D::Draw();
}
