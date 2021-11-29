#include "item_get_ui_baton.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"

CItemGetUIBaton::CItemGetUIBaton()
{
}

CItemGetUIBaton::~CItemGetUIBaton()
{
}

CItemGetUIBaton * CItemGetUIBaton::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	// CItemGetUIBatonのポインタ
	CItemGetUIBaton *pItemGetUIBaton = nullptr;

	// nullcheck
	if (pItemGetUIBaton == nullptr)
	{
		// メモリ確保
		pItemGetUIBaton = new CItemGetUIBaton;

		// !nullcheck
		if (pItemGetUIBaton != nullptr)
		{
			// 初期化処理
			pItemGetUIBaton->Init(Pos, Size);
		}
	}
	// ポインタを返す
	return pItemGetUIBaton;
}

HRESULT CItemGetUIBaton::Init(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	CItemGetUI::Init(Pos, Size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_Y));
	return S_OK;
}

void CItemGetUIBaton::Uninit(void)
{
	CItemGetUI::Uninit();
}

void CItemGetUIBaton::Draw(void)
{
	CItemGetUI::Draw();
}

void CItemGetUIBaton::Update(void)
{
	CItemGetUI::Update();
}
