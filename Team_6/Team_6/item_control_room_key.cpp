#include "item_control_room_key.h"
#include "player_1.h"
#include "player_2.h"
#include "manager.h"
#include "mode_base.h"
#include "item_object_control_room_Key.h"

CControlRoomKey::CControlRoomKey()
{
}

CControlRoomKey::~CControlRoomKey()
{
}

CControlRoomKey * CControlRoomKey::Create(void)
{
	// CControlRoomKey�̃|�C���^
	CControlRoomKey *pControlRoomKey = nullptr;

	// nullcheck
	if (pControlRoomKey == nullptr)
	{
		// �������m��
		pControlRoomKey = new CControlRoomKey;

		// !nullcheck
		if (pControlRoomKey != nullptr)
		{
			// ����������
			pControlRoomKey->Init();
		}
	}
	// �|�C���^��Ԃ�
	return pControlRoomKey;
}

HRESULT CControlRoomKey::Init(void)
{
	SetPlayerItemGetList(CPlayer::ITEM_KEY_CONTROL_ROOM);
	return S_OK;
}

void CControlRoomKey::Uninit(void)
{
}

void CControlRoomKey::Update(void)
{
}

void CControlRoomKey::ItemCreate(int nPlayer)
{
	CPlayer * pPlayer;
	// �v���C���[�̃|�C���^���擾����
	pPlayer = CManager::GetModePtr()->GetPlayer(nPlayer);
	D3DXVECTOR3 PlayerPos;
	PlayerPos = pPlayer->GetPos();
	CControlRoomKeyObject::Create(PlayerPos, ZeroVector3);
}