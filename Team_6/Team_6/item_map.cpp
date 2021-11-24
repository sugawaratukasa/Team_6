#include "main.h"
#include "item_map.h"
#include "map_texture.h"
#include "player_1.h"
#include "player_2.h"
#include "manager.h"
#include "mode_base.h"
#include "item_object_map.h"

CItemMap::CItemMap()
{
	m_pMapTexture = nullptr;
}

CItemMap::~CItemMap()
{
}

CItemMap * CItemMap::Create(void)
{
	// CBatonTexture�̃|�C���^
	CItemMap *pItemMap = nullptr;

	// nullcheck
	if (pItemMap == nullptr)
	{
		// �������m��
		pItemMap = new CItemMap;

		// !nullcheck
		if (pItemMap != nullptr)
		{
			// ����������
			pItemMap->Init();
		}
	}
	// �|�C���^��Ԃ�
	return pItemMap;
}

HRESULT CItemMap::Init(void)
{
	SetPlayerItemGetList(CPlayer::ITEM_MAP);
	if (m_pMapTexture == nullptr)
	{
		m_pMapTexture = CMapTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH - 100.0f, SCREEN_HEIGHT / 2 - 100.0f, 0.0f));
	}
	return S_OK;
}

void CItemMap::Uninit(void)
{
	if (m_pMapTexture != nullptr)
	{
		m_pMapTexture->Uninit();
	}
}

void CItemMap::Update(void)
{
}

void CItemMap::ItemCreate(int nPlayer)
{
	CPlayer * pPlayer;
	// �v���C���[�̃|�C���^���擾����
	pPlayer = CManager::GetModePtr()->GetPlayer(nPlayer);
	D3DXVECTOR3 PlayerPos;
	PlayerPos = pPlayer->GetPos();
	CMapObject::Create(PlayerPos, ZeroVector3);
}