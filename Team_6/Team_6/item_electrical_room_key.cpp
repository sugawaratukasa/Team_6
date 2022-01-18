#include "item_electrical_room_key.h"
#include "player_1.h"
#include "player_2.h"
#include "manager.h"
#include "mode_base.h"
#include "item_object_electrical_room_key.h"

CElectricalRoomKey::CElectricalRoomKey()
{
}

CElectricalRoomKey::~CElectricalRoomKey()
{
}

CElectricalRoomKey * CElectricalRoomKey::Create(void)
{
	// CElectricalRoomKeyのポインタ
	CElectricalRoomKey *pElectricalRoomKey = nullptr;

	// nullcheck
	if (pElectricalRoomKey == nullptr)
	{
		// メモリ確保
		pElectricalRoomKey = new CElectricalRoomKey;

		// !nullcheck
		if (pElectricalRoomKey != nullptr)
		{
			// 初期化処理
			pElectricalRoomKey->Init();
		}
	}
	// ポインタを返す
	return pElectricalRoomKey;
}

HRESULT CElectricalRoomKey::Init(void)
{
	SetPlayerItemGetList(CPlayer::ITEM_KEY_ELECTRICAL_ROOM);
	return S_OK;
}

void CElectricalRoomKey::Uninit(void)
{
}

void CElectricalRoomKey::Update(void)
{
}

void CElectricalRoomKey::ItemCreate(int nPlayer)
{
	CPlayer * pPlayer;
	// プレイヤーのポインタを取得する
	pPlayer = CManager::GetModePtr()->GetPlayer(nPlayer);
	D3DXVECTOR3 PlayerPos;
	PlayerPos = pPlayer->GetPos();
	CElectricalRoomKeyObject::Create(PlayerPos, ZeroVector3);
}

void CElectricalRoomKey::DuctPass(D3DXVECTOR3 pos)
{
	CElectricalRoomKeyObject::Create(pos,ZeroVector3);
}
