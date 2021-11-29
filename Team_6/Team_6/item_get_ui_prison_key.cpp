#include "item_get_ui_prison_key.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"

CItemGetUIPrisonKey::CItemGetUIPrisonKey()
{
}

CItemGetUIPrisonKey::~CItemGetUIPrisonKey()
{
}

CItemGetUIPrisonKey * CItemGetUIPrisonKey::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	// CItemGetUIPrisonKeyのポインタ
	CItemGetUIPrisonKey *pItemGetUIPrisonKey = nullptr;

	// nullcheck
	if (pItemGetUIPrisonKey == nullptr)
	{
		// メモリ確保
		pItemGetUIPrisonKey = new CItemGetUIPrisonKey;

		// !nullcheck
		if (pItemGetUIPrisonKey != nullptr)
		{
			// 初期化処理
			pItemGetUIPrisonKey->Init(Pos,Size);
		}
	}
	// ポインタを返す
	return pItemGetUIPrisonKey;
}

HRESULT CItemGetUIPrisonKey::Init(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	CItemGetUI::Init(Pos, Size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_Y));
	return S_OK;
}

void CItemGetUIPrisonKey::Uninit(void)
{
	CItemGetUI::Uninit();
}

void CItemGetUIPrisonKey::Draw(void)
{
	CItemGetUI::Draw();
}

void CItemGetUIPrisonKey::Update(void)
{
	CItemGetUI::Update();
}
