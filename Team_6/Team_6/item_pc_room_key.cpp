#include "item_pc_room_key.h"
#include "item_object_pc_room_key.h"
#include "manager.h"
#include "mode_base.h"
#include "player.h"
#include "player_1.h"
#include "player_2.h"

CPCRoomKey::CPCRoomKey()
{
}

CPCRoomKey::~CPCRoomKey()
{
}

CPCRoomKey * CPCRoomKey::Create(void)
{
	// CPCRoomKeyのポインタ
	CPCRoomKey *pPCRoomKey = nullptr;

	// nullcheck
	if (pPCRoomKey == nullptr)
	{
		// メモリ確保
		pPCRoomKey = new CPCRoomKey;

		// !nullcheck
		if (pPCRoomKey != nullptr)
		{
			// 初期化処理
			pPCRoomKey->Init();
		}
	}
	// ポインタを返す
	return pPCRoomKey;
}

HRESULT CPCRoomKey::Init(void)
{
	SetPlayerItemGetList(CPlayer::ITEM_KEY_CAMERA_ROOM);
	return S_OK;
}

void CPCRoomKey::Uninit(void)
{
}

void CPCRoomKey::Update(void)
{
}

void CPCRoomKey::ItemCreate(int nPlayer)
{
	CPlayer * pPlayer;
	// プレイヤーのポインタを取得する
	pPlayer = CManager::GetModePtr()->GetPlayer(nPlayer);
	D3DXVECTOR3 PlayerPos;
	PlayerPos = pPlayer->GetPos();
	CPCRoomKeyObject::Create(PlayerPos, ZeroVector3);
}
//=======================================================
// アイテムダクト受け渡し
// Author : SugawaraTsukasa
//=======================================================
void CPCRoomKey::DuctPass(D3DXVECTOR3 pos)
{
	CPCRoomKeyObject::Create(pos, ZeroVector3);
}