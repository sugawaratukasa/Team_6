#include "item_baton.h"
#include "player_1.h"
#include "player_2.h"
#include "manager.h"
#include "mode_base.h"
#include "item_object_baton.h"

CItemBaton::CItemBaton()
{
}

CItemBaton::~CItemBaton()
{
}

CItemBaton * CItemBaton::Create(void)
{
	// CItemBaton�̃|�C���^
	CItemBaton *pItemBaton = nullptr;

	// nullcheck
	if (pItemBaton == nullptr)
	{
		// �������m��
		pItemBaton = new CItemBaton;

		// !nullcheck
		if (pItemBaton != nullptr)
		{
			// ����������
			pItemBaton->Init();
		}
	}
	// �|�C���^��Ԃ�
	return pItemBaton;
}

HRESULT CItemBaton::Init(void)
{
	SetPlayerItemGetList(CPlayer::ITEM_BATON);
	return S_OK;
}

void CItemBaton::Uninit(void)
{
}

void CItemBaton::Update(void)
{
}

void CItemBaton::ItemCreate(int nPlayer)
{
	CPlayer * pPlayer;
	// �v���C���[�̃|�C���^���擾����
	pPlayer = CManager::GetModePtr()->GetPlayer(nPlayer);
	D3DXVECTOR3 PlayerPos;
	PlayerPos = pPlayer->GetPos();
	CBatonObject::Create(PlayerPos, ZeroVector3);
}
