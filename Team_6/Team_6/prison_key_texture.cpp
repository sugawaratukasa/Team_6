#include "main.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "scene_2d.h"
#include "prison_key_texture.h"

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CPrisonKeyTexture::CPrisonKeyTexture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CPrisonKeyTexture::~CPrisonKeyTexture()
{
}

//=============================================================================
// 生成処理関数
// Author : Nikaido Taichi
//=============================================================================
CPrisonKeyTexture * CPrisonKeyTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CPrisonKeyTextureのポインタ
	CPrisonKeyTexture *pPrisonKey = nullptr;

	// nullcheck
	if (pPrisonKey == nullptr)
	{
		// メモリ確保
		pPrisonKey = new CPrisonKeyTexture;

		// !nullcheck
		if (pPrisonKey != nullptr)
		{
			// 初期化処理
			pPrisonKey->Init(pos, size);
		}
	}
	// ポインタを返す
	return pPrisonKey;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CPrisonKeyTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン2Dの初期化処理関数呼び出し
	CScene2D::Init(pos, size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PRISON_KEY));
	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPrisonKeyTexture::Uninit(void)
{
	// シーン2Dの終了処理関数呼び出し
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPrisonKeyTexture::Update(void)
{
	// シーン2Dの更新処理関数呼び出し
	CScene2D::Update();
}

//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPrisonKeyTexture::Draw(void)
{
	// シーン2Dの描画処理関数呼び出し
	CScene2D::Draw();
}
