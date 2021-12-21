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
#include "map_ui_texture.h"

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CMapUITexture::CMapUITexture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CMapUITexture::~CMapUITexture()
{
}

CMapUITexture * CMapUITexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CMapのポインタ
	CMapUITexture *pMapUITexture = nullptr;

	// nullcheck
	if (pMapUITexture == nullptr)
	{
		// メモリ確保
		pMapUITexture = new CMapUITexture;

		// !nullcheck
		if (pMapUITexture != nullptr)
		{
			// 初期化処理
			pMapUITexture->Init(pos, size);
		}
	}
	// ポインタを返す
	return pMapUITexture;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CMapUITexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン2Dの初期化処理関数呼び出し
	CScene2D::Init(pos, size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_UI_MAP));
	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CMapUITexture::Uninit(void)
{
	// シーン2Dの終了処理関数呼び出し
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CMapUITexture::Update(void)
{
	// シーン2Dの更新処理関数呼び出し
	CScene2D::Update();
}

//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CMapUITexture::Draw(void)
{
	// シーン2Dの描画処理関数呼び出し
	CScene2D::Draw();
}
