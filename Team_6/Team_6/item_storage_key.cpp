#include "item_storage_key.h"
#include "player_1.h"
#include "player_2.h"
#include "manager.h"
#include "mode_base.h"
#include "item_object_storage_key.h"

CStorageKey::CStorageKey()
{
}

CStorageKey::~CStorageKey()
{
}

CStorageKey * CStorageKey::Create(void)
{
	// CStorageKeyのポインタ
	CStorageKey *pStorageKey = nullptr;

	// nullcheck
	if (pStorageKey == nullptr)
	{
		// メモリ確保
		pStorageKey = new CStorageKey;

		// !nullcheck
		if (pStorageKey != nullptr)
		{
			// 初期化処理
			pStorageKey->Init();
		}
	}
	// ポインタを返す
	return pStorageKey;
}

HRESULT CStorageKey::Init(void)
{
	SetPlayerItemGetList(CPlayer::ITEM_KEY_STORAGE);
	return S_OK;
}

void CStorageKey::Uninit(void)
{
}

void CStorageKey::Update(void)
{
}

void CStorageKey::ItemCreate(int nPlayer)
{
	CPlayer * pPlayer;
	// プレイヤーのポインタを取得する
	pPlayer = CManager::GetModePtr()->GetPlayer(nPlayer);
	D3DXVECTOR3 PlayerPos;
	PlayerPos = pPlayer->GetPos();
	CStorageKeyObject::Create(PlayerPos, ZeroVector3);
}