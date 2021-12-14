//=============================================================================
//
// 看守室の鍵テクスチャテクスチャ [item_guid_prison_key.cpp]
// Author : 二階堂　汰一
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "scene_2d.h"
#include "jailer_key_texture.h"

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CJailerKeyTexture::CJailerKeyTexture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CJailerKeyTexture::~CJailerKeyTexture()
{
}

//=============================================================================
// 生成処理関数
// Author : Nikaido Taichi
//=============================================================================
CJailerKeyTexture * CJailerKeyTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CJailerKeyTextureのポインタ
	CJailerKeyTexture *pJailerKey = nullptr;

	// nullcheck
	if (pJailerKey == nullptr)
	{
		// メモリ確保
		pJailerKey = new CJailerKeyTexture;

		// !nullcheck
		if (pJailerKey != nullptr)
		{
			// 初期化処理
			pJailerKey->Init(pos, size);
		}
	}
	// ポインタを返す
	return pJailerKey;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CJailerKeyTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン2Dの初期化処理関数呼び出し
	CScene2D::Init(pos, size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_JAILER_KEY));
	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CJailerKeyTexture::Uninit(void)
{
	// シーン2Dの終了処理関数呼び出し
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CJailerKeyTexture::Update(void)
{
	// シーン2Dの更新処理関数呼び出し
	CScene2D::Update();
}

//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CJailerKeyTexture::Draw(void)
{
	// シーン2Dの描画処理関数呼び出し
	CScene2D::Draw();
}
