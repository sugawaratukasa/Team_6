#include "main.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "scene_2d.h"
#include "pad_texture.h"
#include "sound.h"

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CPadTexture::CPadTexture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CPadTexture::~CPadTexture()
{
}

CPadTexture * CPadTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CPadTextureのポインタ
	CPadTexture *pPadTexture = nullptr;

	// nullcheck
	if (pPadTexture == nullptr)
	{
		// メモリ確保
		pPadTexture = new CPadTexture;

		// !nullcheck
		if (pPadTexture != nullptr)
		{
			// 初期化処理
			pPadTexture->Init(pos, size);
		}
	}
	// ポインタを返す
	return pPadTexture;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CPadTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン2Dの初期化処理関数呼び出し
	CScene2D::Init(pos, size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_PAD_GUID));
	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPadTexture::Uninit(void)
{
	// シーン2Dの終了処理関数呼び出し
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPadTexture::Update(void)
{
	// シーン2Dの更新処理関数呼び出し
	CScene2D::Update();
}

//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPadTexture::Draw(void)
{
	// シーン2Dの描画処理関数呼び出し
	CScene2D::Draw();
}
