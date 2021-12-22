#include "main.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "scene_2d.h"
#include "map2_texture.h"
#include "sound.h"

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CMap2Texture::CMap2Texture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CMap2Texture::~CMap2Texture()
{
}

CMap2Texture * CMap2Texture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CMap2Textureのポインタ
	CMap2Texture *pMap2Texture = nullptr;

	// nullcheck
	if (pMap2Texture == nullptr)
	{
		// メモリ確保
		pMap2Texture = new CMap2Texture;

		// !nullcheck
		if (pMap2Texture != nullptr)
		{
			// 初期化処理
			pMap2Texture->Init(pos, size);
		}
	}
	// ポインタを返す
	return pMap2Texture;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CMap2Texture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン2Dの初期化処理関数呼び出し
	CScene2D::Init(pos, size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_MAP2));
	CSound * pSound = GET_SOUND_PTR;
	pSound->CSound::Play(CSound::SOUND_SE_OPEN_MAP);
	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CMap2Texture::Uninit(void)
{
	// シーン2Dの終了処理関数呼び出し
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CMap2Texture::Update(void)
{
	// シーン2Dの更新処理関数呼び出し
	CScene2D::Update();
}

//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CMap2Texture::Draw(void)
{
	// シーン2Dの描画処理関数呼び出し
	CScene2D::Draw();
}
