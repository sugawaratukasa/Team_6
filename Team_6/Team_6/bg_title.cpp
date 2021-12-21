//=============================================================================
//
// タイトル背景 [bg_pause.h]
// Author : 二階堂汰一
//
//=============================================================================
#include "main.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "scene_2d.h"
#include "bg_title.h"

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CTitleBG::CTitleBG(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CTitleBG::~CTitleBG()
{
}

//=============================================================================
// 生成処理関数
// Author : Nikaido Taichi
//=============================================================================
CTitleBG * CTitleBG::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CKeyTextureのポインタ
	CTitleBG *pTitleBG = nullptr;

	// nullcheck
	if (pTitleBG == nullptr)
	{
		// メモリ確保
		pTitleBG = new CTitleBG;

		// !nullcheck
		if (pTitleBG != nullptr)
		{
			// 初期化処理
			pTitleBG->Init(pos, size);
		}
	}
	// ポインタを返す
	return pTitleBG;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CTitleBG::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン2Dの初期化処理関数呼び出し
	CScene2D::Init(pos, size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_TITLE_BG));
	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CTitleBG::Uninit(void)
{
	// シーン2Dの終了処理関数呼び出し
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CTitleBG::Update(void)
{
	// シーン2Dの更新処理関数呼び出し
	CScene2D::Update();
}

//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CTitleBG::Draw(void)
{
	// シーン2Dの描画処理関数呼び出し
	CScene2D::Draw();
}
