#include "main.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "scene_2d.h"
#include "map1_texture.h"
#include "sound.h"

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CMap1Texture::CMap1Texture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CMap1Texture::~CMap1Texture()
{
}

CMap1Texture * CMap1Texture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CMap1Textureのポインタ
	CMap1Texture *pMap1Texture = nullptr;

	// nullcheck
	if (pMap1Texture == nullptr)
	{
		// メモリ確保
		pMap1Texture = new CMap1Texture;

		// !nullcheck
		if (pMap1Texture != nullptr)
		{
			// 初期化処理
			pMap1Texture->Init(pos, size);
		}
	}
	// ポインタを返す
	return pMap1Texture;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CMap1Texture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン2Dの初期化処理関数呼び出し
	CScene2D::Init(pos, size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_MAP1));
	CSound * pSound = GET_SOUND_PTR;
	pSound->CSound::Play(CSound::SOUND_SE_OPEN_MAP);
	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CMap1Texture::Uninit(void)
{
	// シーン2Dの終了処理関数呼び出し
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CMap1Texture::Update(void)
{
	// シーン2Dの更新処理関数呼び出し
	CScene2D::Update();
}

//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CMap1Texture::Draw(void)
{
	// シーン2Dの描画処理関数呼び出し
	CScene2D::Draw();
}
