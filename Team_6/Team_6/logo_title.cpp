//=============================================================================
//
// タイトルロゴ [lpgo_title.cpp]
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
#include "logo_title.h"

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CTitleLogo::CTitleLogo(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CTitleLogo::~CTitleLogo()
{
}

//=============================================================================
// 生成処理関数
// Author : Nikaido Taichi
//=============================================================================
CTitleLogo * CTitleLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CKeyTextureのポインタ
	CTitleLogo *pTitleLogo = nullptr;

	// nullcheck
	if (pTitleLogo == nullptr)
	{
		// メモリ確保
		pTitleLogo = new CTitleLogo;

		// !nullcheck
		if (pTitleLogo != nullptr)
		{
			// 初期化処理
			pTitleLogo->Init(pos, size);
		}
	}
	// ポインタを返す
	return pTitleLogo;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CTitleLogo::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン2Dの初期化処理関数呼び出し
	CScene2D::Init(pos, size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_TITLE_LOGO));
	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CTitleLogo::Uninit(void)
{
	// シーン2Dの終了処理関数呼び出し
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CTitleLogo::Update(void)
{
	// シーン2Dの更新処理関数呼び出し
	CScene2D::Update();
}

//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CTitleLogo::Draw(void)
{
	// シーン2Dの描画処理関数呼び出し
	CScene2D::Draw();
}
