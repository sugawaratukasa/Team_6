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
	// CElectricalRoomKey�̃|�C���^
	CElectricalRoomKey *pElectricalRoomKey = nullptr;

	// nullcheck
	if (pElectricalRoomKey == nullptr)
	{
		// �������m��
		pElectricalRoomKey = new CElectricalRoomKey;

		// !nullcheck
		if (pElectricalRoomKey != nullptr)
		{
			// ����������
			pElectricalRoomKey->Init();
		}
	}
	// �|�C���^��Ԃ�
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
	// �v���C���[�̃|�C���^���擾����
	pPlayer = CManager::GetModePtr()->GetPlayer(nPlayer);
	D3DXVECTOR3 PlayerPos;
	PlayerPos = pPlayer->GetPos();
	CElectricalRoomKeyObject::Create(PlayerPos, ZeroVector3);
}

void CElectricalRoomKey::DuctPass(D3DXVECTOR3 pos)
{
	CElectricalRoomKeyObject::Create(pos,ZeroVector3);
}
