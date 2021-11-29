#include "item_get_ui_storage_key.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"

CItemGetUIStorageKey::CItemGetUIStorageKey()
{
}

CItemGetUIStorageKey::~CItemGetUIStorageKey()
{
}

CItemGetUIStorageKey * CItemGetUIStorageKey::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	// CItemGetUIStorageKeyのポインタ
	CItemGetUIStorageKey *pItemGetUIStorageKey = nullptr;

	// nullcheck
	if (pItemGetUIStorageKey == nullptr)
	{
		// メモリ確保
		pItemGetUIStorageKey = new CItemGetUIStorageKey;

		// !nullcheck
		if (pItemGetUIStorageKey != nullptr)
		{
			// 初期化処理
			pItemGetUIStorageKey->Init(Pos, Size);
		}
	}
	// ポインタを返す
	return pItemGetUIStorageKey;
}

HRESULT CItemGetUIStorageKey::Init(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	CItemGetUI::Init(Pos, Size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_Y));
	return S_OK;
}

void CItemGetUIStorageKey::Uninit(void)
{
	CItemGetUI::Uninit();
}

void CItemGetUIStorageKey::Draw(void)
{
	CItemGetUI::Draw();
}

void CItemGetUIStorageKey::Update(void)
{
	CItemGetUI::Update();
}
