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
	// CItemBatonのポインタ
	CItemBaton *pItemBaton = nullptr;

	// nullcheck
	if (pItemBaton == nullptr)
	{
		// メモリ確保
		pItemBaton = new CItemBaton;

		// !nullcheck
		if (pItemBaton != nullptr)
		{
			// 初期化処理
			pItemBaton->Init();
		}
	}
	// ポインタを返す
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
	// プレイヤーのポインタを取得する
	pPlayer = CManager::GetModePtr()->GetPlayer(nPlayer);
	D3DXVECTOR3 PlayerPos;
	PlayerPos = pPlayer->GetPos();
	CBatonObject::Create(PlayerPos, ZeroVector3);
}
