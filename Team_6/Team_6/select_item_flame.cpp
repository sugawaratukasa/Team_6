#include "select_item_flame.h"
#include "texture.h"
#include "manager.h"
#include "resource_manager.h"

CSelectItemFlame::CSelectItemFlame(PRIORITY Priority)
{
}

CSelectItemFlame::~CSelectItemFlame()
{
}

CSelectItemFlame * CSelectItemFlame::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CSelectItemFlameのポインタ
	CSelectItemFlame *pSelectItemFlame = nullptr;

	// nullcheck
	if (pSelectItemFlame == nullptr)
	{
		// メモリ確保
		pSelectItemFlame = new CSelectItemFlame;

		// !nullcheck
		if (pSelectItemFlame != nullptr)
		{
			// 初期化処理
			pSelectItemFlame->Init(pos, size);
		}
	}
	// ポインタを返す
	return pSelectItemFlame;
}

HRESULT CSelectItemFlame::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_SELECT_ITEM_FLAME));
	return S_OK;
}

void CSelectItemFlame::Uninit(void)
{
	CScene2D::Uninit();
}

void CSelectItemFlame::Update(void)
{
	CScene2D::Update();
}

void CSelectItemFlame::Draw(void)
{
	CScene2D::Draw();
}
