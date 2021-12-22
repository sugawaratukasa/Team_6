#include "item_prison_key.h"
#include "player_1.h"
#include "player_2.h"
#include "manager.h"
#include "mode_base.h"
#include "item_object_prison_key.h"

CPrisonKey::CPrisonKey()
{
}

CPrisonKey::~CPrisonKey()
{
}

CPrisonKey * CPrisonKey::Create(void)
{
	// CPrisonKey�̃|�C���^
	CPrisonKey *pPrisonKey = nullptr;

	// nullcheck
	if (pPrisonKey == nullptr)
	{
		// �������m��
		pPrisonKey = new CPrisonKey;

		// !nullcheck
		if (pPrisonKey != nullptr)
		{
			// ����������
			pPrisonKey->Init();
		}
	}
	// �|�C���^��Ԃ�
	return pPrisonKey;
}

HRESULT CPrisonKey::Init(void)
{
	SetPlayerItemGetList(CPlayer::ITEM_KEY_PRISON);
	return S_OK;
}

void CPrisonKey::Uninit(void)
{
}

void CPrisonKey::Update(void)
{
}

void CPrisonKey::ItemCreate(int nPlayer)
{
	CPlayer * pPlayer;
	// �v���C���[�̃|�C���^���擾����
	pPlayer = CManager::GetModePtr()->GetPlayer(nPlayer);
	D3DXVECTOR3 PlayerPos;
	PlayerPos = pPlayer->GetPos();
	CPrisonKeyObject::Create(PlayerPos, ZeroVector3);
}
//=======================================================
// �A�C�e���_�N�g�󂯓n��
// Author : SugawaraTsukasa
//=======================================================
void CPrisonKey::DuctPass(D3DXVECTOR3 pos)
{
	CPrisonKeyObject::Create(pos, ZeroVector3);
}