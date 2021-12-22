//=============================================================================
//
// 制御室の鍵テクスチャ [control_room_key.cpp]
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
#include "control_room_key_texture.h"

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CControlKeyTexture::CControlKeyTexture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CControlKeyTexture::~CControlKeyTexture()
{
}

//=============================================================================
// 生成処理関数
// Author : Nikaido Taichi
//=============================================================================
CControlKeyTexture * CControlKeyTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CControlKeyTextureのポインタ
	CControlKeyTexture *pControlKeyTexture = nullptr;

	// nullcheck
	if (pControlKeyTexture == nullptr)
	{
		// メモリ確保
		pControlKeyTexture = new CControlKeyTexture;

		// !nullcheck
		if (pControlKeyTexture != nullptr)
		{
			// 初期化処理
			pControlKeyTexture->Init(pos, size);
		}
	}
	// ポインタを返す
	return pControlKeyTexture;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CControlKeyTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン2Dの初期化処理関数呼び出し
	CScene2D::Init(pos, size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_CONTROL_KEY));
	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CControlKeyTexture::Uninit(void)
{
	// シーン2Dの終了処理関数呼び出し
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CControlKeyTexture::Update(void)
{
	// シーン2Dの更新処理関数呼び出し
	CScene2D::Update();
}

//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CControlKeyTexture::Draw(void)
{
	// シーン2Dの描画処理関数呼び出し
	CScene2D::Draw();
}
