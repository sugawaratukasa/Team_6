#include "item_jailer_room_key.h"
#include "player_1.h"
#include "player_2.h"
#include "manager.h"
#include "mode_base.h"
#include "item_object_jailer_room_key.h"

CJailerRoomKey::CJailerRoomKey()
{
}

CJailerRoomKey::~CJailerRoomKey()
{
}

CJailerRoomKey * CJailerRoomKey::Create(void)
{
	// CJailerRoomKeyのポインタ
	CJailerRoomKey *pJailerRoomKey = nullptr;

	// nullcheck
	if (pJailerRoomKey == nullptr)
	{
		// メモリ確保
		pJailerRoomKey = new CJailerRoomKey;

		// !nullcheck
		if (pJailerRoomKey != nullptr)
		{
			// 初期化処理
			pJailerRoomKey->Init();
		}
	}
	// ポインタを返す
	return pJailerRoomKey;
}

HRESULT CJailerRoomKey::Init(void)
{
	SetPlayerItemGetList(CPlayer::ITEM_KEY_JAILER_ROOM);
	return S_OK;
}

void CJailerRoomKey::Uninit(void)
{
}

void CJailerRoomKey::Update(void)
{
}

void CJailerRoomKey::ItemCreate(int nPlayer)
{
	CPlayer * pPlayer;
	// プレイヤーのポインタを取得する
	pPlayer = CManager::GetModePtr()->GetPlayer(nPlayer);
	D3DXVECTOR3 PlayerPos;
	PlayerPos = pPlayer->GetPos();
	CJailerKeyObject::Create(PlayerPos, ZeroVector3);
}
//=======================================================
// アイテムダクト受け渡し
// Author : SugawaraTsukasa
//=======================================================
void CJailerRoomKey::DuctPass(D3DXVECTOR3 pos)
{
	CJailerKeyObject::Create(pos, ZeroVector3);
}
