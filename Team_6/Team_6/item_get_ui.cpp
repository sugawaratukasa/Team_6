#include "item_get_ui.h"
#include "player.h"
#include "manager.h"
#include "mode_base.h"

CItemGetUI::CItemGetUI()
{
}

CItemGetUI::~CItemGetUI()
{
}

HRESULT CItemGetUI::Init(D3DXVECTOR3 Pos,D3DXVECTOR3 Size)
{
	CBillboard::Init(Pos,Size);
	return S_OK;
}

void CItemGetUI::Uninit(void)
{
	CBillboard::Uninit();
}

void CItemGetUI::Draw(void)
{
	CBillboard::Draw();
}

void CItemGetUI::Update(void)
{
	CBillboard::Update();
}
