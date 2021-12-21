//=============================================================================
//
// 牢獄の鍵説明テクスチャ [number.cpp]
// Author : 二階堂　汰一
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "prison_key_guid_texture.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CPrisonKeyGuidTexture::CPrisonKeyGuidTexture(PRIORITY Priority)
{
}


//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CPrisonKeyGuidTexture::~CPrisonKeyGuidTexture()
{
}


//=============================================================================
// 生成処理関数
// Author : Nikaido Taichi
//=============================================================================
CPrisonKeyGuidTexture * CPrisonKeyGuidTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CPrisonKeyGuidTextureのポインタ
	CPrisonKeyGuidTexture *pPrisonKeyGuidTexture = nullptr;

	// nullcheck
	if (pPrisonKeyGuidTexture == nullptr)
	{
		// メモリ確保
		pPrisonKeyGuidTexture = new CPrisonKeyGuidTexture;

		// !nullcheck
		if (pPrisonKeyGuidTexture != nullptr)
		{
			// 初期化処理
			pPrisonKeyGuidTexture->Init(pos, size);
		}
	}
	// ポインタを返す
	return pPrisonKeyGuidTexture;
}


//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CPrisonKeyGuidTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン2Dの初期化処理関数呼び出し
	CScene2D::Init(pos, size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PRISON_KEY_GUID));
	return S_OK;
}


//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPrisonKeyGuidTexture::Uninit(void)
{
	// シーン2Dの描画処理関数呼び出し
	CScene2D::Uninit();
}


//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPrisonKeyGuidTexture::Update(void)
{
	// シーン2Dの更新処理関数呼び出し
	CScene2D::Update();
}


//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPrisonKeyGuidTexture::Draw(void)
{
	// シーン2Dの描画処理関数呼び出し
	CScene2D::Draw();
}
