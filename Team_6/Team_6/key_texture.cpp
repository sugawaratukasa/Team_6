#include "main.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "scene_2d.h"
#include "key_texture.h"

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CKeyTexture::CKeyTexture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CKeyTexture::~CKeyTexture()
{
}

CKeyTexture * CKeyTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CKeyTextureのポインタ
	CKeyTexture *pKeyTexture = nullptr;

	// nullcheck
	if (pKeyTexture == nullptr)
	{
		// メモリ確保
		pKeyTexture = new CKeyTexture;

		// !nullcheck
		if (pKeyTexture != nullptr)
		{
			// 初期化処理
			pKeyTexture->Init(pos, size);
		}
	}
	// ポインタを返す
	return pKeyTexture;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CKeyTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン2Dの初期化処理関数呼び出し
	CScene2D::Init(pos, size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_KEY));
	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CKeyTexture::Uninit(void)
{
	// シーン2Dの終了処理関数呼び出し
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CKeyTexture::Update(void)
{
	// シーン2Dの更新処理関数呼び出し
	CScene2D::Update();
}

//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CKeyTexture::Draw(void)
{
	// シーン2Dの描画処理関数呼び出し
	CScene2D::Draw();
}
