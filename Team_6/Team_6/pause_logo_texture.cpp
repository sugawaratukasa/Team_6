//=============================================================================
//
// ポーズロゴテクスチャ [pause_logo_texture.cpp]
// Author : 二階堂　汰一
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "pause_logo_texture.h"
#include "texture.h"
#include "manager.h"
#include "resource_manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CPauseLogoTexture::CPauseLogoTexture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CPauseLogoTexture::~CPauseLogoTexture()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CPauseLogoTexture * CPauseLogoTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CPauseLogoTextureのポインタ
	CPauseLogoTexture *pPauseLogoTexture = nullptr;

	// nullcheck
	if (pPauseLogoTexture == nullptr)
	{
		// メモリ確保
		pPauseLogoTexture = new CPauseLogoTexture;

		// !nullcheck
		if (pPauseLogoTexture != nullptr)
		{
			// 初期化処理
			pPauseLogoTexture->Init(pos, size);
		}
	}
	// ポインタを返す
	return pPauseLogoTexture;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CPauseLogoTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン2Dの初期化処理関数呼び出し
	CScene2D::Init(pos, size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PAUSE_LOGO));
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CPauseLogoTexture::Uninit(void)
{
	// シーン2Dの終了処理関数呼び出し
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CPauseLogoTexture::Update(void)
{
	// シーン2Dの更新処理関数呼び出し
	CScene2D::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CPauseLogoTexture::Draw(void)
{
	// シーン2Dの描画処理関数呼び出し
	CScene2D::Draw();
}
