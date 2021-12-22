//=============================================================================
//
// 倉庫の鍵説明テクスチャ [storage_key_guid_texture.cpp]
// Author : 二階堂　汰一
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "storage_key_guid_texture.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CStorageKeyGuidTexture::CStorageKeyGuidTexture(PRIORITY Priority) : CScene2D(Priority)
{
}


//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CStorageKeyGuidTexture::~CStorageKeyGuidTexture()
{
}


//=============================================================================
// 生成処理関数
// Author : Nikaido Taichi
//=============================================================================
CStorageKeyGuidTexture * CStorageKeyGuidTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CPrisonKeyGuidTextureのポインタ
	CStorageKeyGuidTexture *pStorageKeyGuidTexture = nullptr;

	// nullcheck
	if (pStorageKeyGuidTexture == nullptr)
	{
		// メモリ確保
		pStorageKeyGuidTexture = new CStorageKeyGuidTexture;

		// !nullcheck
		if (pStorageKeyGuidTexture != nullptr)
		{
			// 初期化処理
			pStorageKeyGuidTexture->Init(pos, size);
		}
	}
	// ポインタを返す
	return pStorageKeyGuidTexture;
}


//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CStorageKeyGuidTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン2Dの初期化処理関数呼び出し
	CScene2D::Init(pos, size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_STORAGE_KEY_GUID));
	return S_OK;
}


//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CStorageKeyGuidTexture::Uninit(void)
{
	// シーン2Dの描画処理関数呼び出し
	CScene2D::Uninit();
}


//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CStorageKeyGuidTexture::Update(void)
{
	// シーン2Dの更新処理関数呼び出し
	CScene2D::Update();
}


//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CStorageKeyGuidTexture::Draw(void)
{
	// シーン2Dの描画処理関数呼び出し
	CScene2D::Draw();
}
