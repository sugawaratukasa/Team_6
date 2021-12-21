//=============================================================================
//
// 警棒説明テクスチャ [baton_guid_texture.cpp]
// Author : 二階堂　汰一
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "baton_guid_texture.h"
#include "texture.h"
#include "manager.h"
#include "resource_manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CBatonGuidTexture::CBatonGuidTexture(PRIORITY Priority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CBatonGuidTexture::~CBatonGuidTexture()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CBatonGuidTexture * CBatonGuidTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CBatonGuidTextureのポインタ
	CBatonGuidTexture *pBatonGuidTexture = nullptr;

	// nullcheck
	if (pBatonGuidTexture == nullptr)
	{
		// メモリ確保
		pBatonGuidTexture = new CBatonGuidTexture;

		// !nullcheck
		if (pBatonGuidTexture != nullptr)
		{
			// 初期化処理
			pBatonGuidTexture->Init(pos, size);
		}
	}
	// ポインタを返す
	return pBatonGuidTexture;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CBatonGuidTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン2Dの初期化処理関数呼び出し
	CScene2D::Init(pos, size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_BATON_GUID));
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CBatonGuidTexture::Uninit(void)
{
	// シーン2Dの終了処理関数呼び出し
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CBatonGuidTexture::Update(void)
{
	// シーン2Dの更新処理関数呼び出し
	CScene2D::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CBatonGuidTexture::Draw(void)
{
	// シーン2Dの描画処理関数呼び出し
	CScene2D::Draw();
}
