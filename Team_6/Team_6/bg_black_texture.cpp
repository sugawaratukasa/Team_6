#include "bg_black_texture.h"
#include "texture.h"
#include "manager.h"
#include "resource_manager.h"

CBlackTexture::CBlackTexture(PRIORITY Priority) : CScene2D(Priority)
{
}

CBlackTexture::~CBlackTexture()
{
}

CBlackTexture * CBlackTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CBlackTextureのポインタ
	CBlackTexture *pBlackTexture = nullptr;

	// nullcheck
	if (pBlackTexture == nullptr)
	{
		// メモリ確保
		pBlackTexture = new CBlackTexture;

		// !nullcheck
		if (pBlackTexture != nullptr)
		{
			// 初期化処理
			pBlackTexture->Init(pos, size);
		}
	}
	// ポインタを返す
	return pBlackTexture;
}

HRESULT CBlackTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン2Dの初期化処理関数呼び出し
	CScene2D::Init(pos, size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_IMPRISONMENT));
	return S_OK;
}

void CBlackTexture::Uninit(void)
{
	// シーン2Dの終了処理関数呼び出し
	CScene2D::Uninit();
}

void CBlackTexture::Update(void)
{
	// シーン2Dの更新処理関数呼び出し
	CScene2D::Update();
}

void CBlackTexture::Draw(void)
{
	// シーン2Dの描画処理関数呼び出し
	CScene2D::Draw();
}
