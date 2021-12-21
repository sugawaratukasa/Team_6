//=============================================================================
//
// 看守室の鍵説明テクスチャ [jailer_key_guid_texture.cpp]
// Author : 二階堂　汰一
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "jailer_key_guid_texture.h"
#include "texture.h"
#include "manager.h"
#include "resource_manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CJailerKeyGuidTexture::CJailerKeyGuidTexture(PRIORITY Priority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CJailerKeyGuidTexture::~CJailerKeyGuidTexture()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CJailerKeyGuidTexture * CJailerKeyGuidTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CJailerKeyGuidTextureのポインタ
	CJailerKeyGuidTexture *pJailerKeyGuidTexture = nullptr;

	// nullcheck
	if (pJailerKeyGuidTexture == nullptr)
	{
		// メモリ確保
		pJailerKeyGuidTexture = new CJailerKeyGuidTexture;

		// !nullcheck
		if (pJailerKeyGuidTexture != nullptr)
		{
			// 初期化処理
			pJailerKeyGuidTexture->Init(pos, size);
		}
	}
	// ポインタを返す
	return pJailerKeyGuidTexture;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CJailerKeyGuidTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン2Dの初期化処理関数呼び出し
	CScene2D::Init(pos, size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_JAILER_KEY_GUID));
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CJailerKeyGuidTexture::Uninit(void)
{
	// シーン2Dの終了処理関数呼び出し
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CJailerKeyGuidTexture::Update(void)
{
	// シーン2Dの更新処理関数呼び出し
	CScene2D::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CJailerKeyGuidTexture::Draw(void)
{
	// シーン2Dの描画処理関数呼び出し
	CScene2D::Draw();
}
