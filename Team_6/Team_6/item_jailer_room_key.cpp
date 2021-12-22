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
	// CJailerRoomKey�̃|�C���^
	CJailerRoomKey *pJailerRoomKey = nullptr;

	// nullcheck
	if (pJailerRoomKey == nullptr)
	{
		// �������m��
		pJailerRoomKey = new CJailerRoomKey;

		// !nullcheck
		if (pJailerRoomKey != nullptr)
		{
			// ����������
			pJailerRoomKey->Init();
		}
	}
	// �|�C���^��Ԃ�
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
	// �v���C���[�̃|�C���^���擾����
	pPlayer = CManager::GetModePtr()->GetPlayer(nPlayer);
	D3DXVECTOR3 PlayerPos;
	PlayerPos = pPlayer->GetPos();
	CJailerKeyObject::Create(PlayerPos, ZeroVector3);
}
//=======================================================
// �A�C�e���_�N�g�󂯓n��
// Author : SugawaraTsukasa
//=======================================================
void CJailerRoomKey::DuctPass(D3DXVECTOR3 pos)
{
	CJailerKeyObject::Create(pos, ZeroVector3);
}
