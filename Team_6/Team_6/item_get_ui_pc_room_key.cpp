#include "item_get_ui_pc_room_key.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"

CItemGetUIPCRoomKey::CItemGetUIPCRoomKey()
{
}

CItemGetUIPCRoomKey::~CItemGetUIPCRoomKey()
{
}

CItemGetUIPCRoomKey * CItemGetUIPCRoomKey::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	// CItemGetUIPCRoomKeyのポインタ
	CItemGetUIPCRoomKey *pItemGetUIPCRoomKey = nullptr;

	// nullcheck
	if (pItemGetUIPCRoomKey == nullptr)
	{
		// メモリ確保
		pItemGetUIPCRoomKey = new CItemGetUIPCRoomKey;

		// !nullcheck
		if (pItemGetUIPCRoomKey != nullptr)
		{
			// 初期化処理
			pItemGetUIPCRoomKey->Init(Pos, Size);
		}
	}
	// ポインタを返す
	return pItemGetUIPCRoomKey;
}

HRESULT CItemGetUIPCRoomKey::Init(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	CItemGetUI::Init(Pos, Size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_Y));
	return S_OK;
}

void CItemGetUIPCRoomKey::Uninit(void)
{
	CItemGetUI::Uninit();
}

void CItemGetUIPCRoomKey::Draw(void)
{
	CItemGetUI::Draw();
}

void CItemGetUIPCRoomKey::Update(void)
{
	CItemGetUI::Update();
}
