//=======================================================================================
//
// UIの枠テクスチャ [ui_flame_texture.cpp]
// Author : Sugawara Tsukasa
//
//=======================================================================================

//=======================================================================================
// インクルードファイル
//=======================================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "resource_manager.h"
#include "texture.h"
#include "scene_2d.h"
#include "ui_flame_texture.h"

#define COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,0.8f))

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CUIFlameTexture::CUIFlameTexture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CUIFlameTexture::~CUIFlameTexture()
{
}

CUIFlameTexture * CUIFlameTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CUIFlameTextureのポインタ
	CUIFlameTexture *pUIFlameTexture = nullptr;

	// nullcheck
	if (pUIFlameTexture == nullptr)
	{
		// メモリ確保
		pUIFlameTexture = new CUIFlameTexture;

		// !nullcheck
		if (pUIFlameTexture != nullptr)
		{
			// 初期化処理
			pUIFlameTexture->Init(pos, size);
		}
	}
	// ポインタを返す
	return pUIFlameTexture;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CUIFlameTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン2Dの初期化処理関数呼び出し
	CScene2D::Init(pos, size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_UI_FLAME));
	SetCol(COLOR);
	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CUIFlameTexture::Uninit(void)
{
	// シーン2Dの終了処理関数呼び出し
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CUIFlameTexture::Update(void)
{
	// シーン2Dの更新処理関数呼び出し
	CScene2D::Update();
}

//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CUIFlameTexture::Draw(void)
{
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();	//デバイスの取得
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 50);
	pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	// シーン2Dの描画処理関数呼び出し
	CScene2D::Draw();
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
