//=============================================================================
//
// ボタンテクスチャ [bg_pause.h]
// Author : 二階堂汰一
//
//=============================================================================
#include "main.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "scene_2d.h"
#include "baton_texture.h"

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CBatonTexture::CBatonTexture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CBatonTexture::~CBatonTexture()
{
}

//=============================================================================
// 生成処理関数
// Author : Nikaido Taichi
//=============================================================================
CBatonTexture * CBatonTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CBatonTextureのポインタ
	CBatonTexture *pBatonTexture = nullptr;

	// nullcheck
	if (pBatonTexture == nullptr)
	{
		// メモリ確保
		pBatonTexture = new CBatonTexture;

		// !nullcheck
		if (pBatonTexture != nullptr)
		{
			// 初期化処理
			pBatonTexture->Init(pos, size);
		}
	}
	// ポインタを返す
	return pBatonTexture;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CBatonTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン2Dの初期化処理関数呼び出し
	CScene2D::Init(pos, size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_BATON));
	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CBatonTexture::Uninit(void)
{
	// シーン2Dの終了処理関数呼び出し
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CBatonTexture::Update(void)
{
	// シーン2Dの更新処理関数呼び出し
	CScene2D::Update();
}

//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CBatonTexture::Draw(void)
{
	// シーン2Dの描画処理関数呼び出し
	CScene2D::Draw();
}
