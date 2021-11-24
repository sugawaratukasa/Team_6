//=============================================================================
// �v���C���[2UI [player2_ui.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Nikaido Taichi
//=============================================================================
#include "main.h"
#include "manager.h"
#include "mode_base.h"
#include "player2_ui.h"
#include "ui_flame_texture.h"
#include "item_object.h"
#include "baton_texture.h"
#include "map_texture.h"
#include "key_texture.h"
#include "game.h"
#include "player.h"

//=============================================================================
// �}�N����`
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CPlayer2UI::CPlayer2UI()
{
	m_nItemTextureCount = 0;
	for (int nCount = 0; nCount < CItemObject::ITEM_OBJECT_MAX; nCount++)
	{
		m_apItemTexture[nCount] = nullptr;
	}
}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CPlayer2UI::~CPlayer2UI()
{
}

//=============================================================================
// ���������֐�
// Author : Nikaido Taichi
//=============================================================================
CPlayer2UI * CPlayer2UI::Create(void)
{
	// CPlayer2UI�̃|�C���^
	CPlayer2UI *pPlayer1UI = nullptr;

	// nullcheck
	if (pPlayer1UI == nullptr)
	{
		// �������m��
		pPlayer1UI = new CPlayer2UI;

		// !nullcheck
		if (pPlayer1UI != nullptr)
		{
			// ����������
			pPlayer1UI->Init();
		}
	}
	// �|�C���^��Ԃ�
	return pPlayer1UI;
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CPlayer2UI::Init(void)
{
	CUIFlameTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 110.0f, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(200.0f, 60.0f, 0.0f));
	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayer2UI::Uninit(void)
{
}

//=============================================================================
// �X�V�֐������֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayer2UI::Update(void)
{
	// UI��������
	UICreate();
}

//=============================================================================
// UI���������֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayer2UI::UICreate(void)
{
	CGame * pGame = ((CGame*)CManager::GetModePtr());
	CPlayer * pPlayer2 = pGame->GetPlayer(1);
	if (pPlayer2->GetbItem(CItemObject::ITEM_OBJECT_KEY_PRISON) == true)
	{
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PRISON] == nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PRISON] = CKeyTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_nItemTextureCount, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
			m_nItemTextureCount++;
		}
	}
	if (pPlayer2->GetbItem(CItemObject::ITEM_OBJECT_KEY_STORAGE) == true)
	{
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_STORAGE] == nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_STORAGE] = CKeyTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_nItemTextureCount, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
			m_nItemTextureCount++;
		}
	}
	if (pPlayer2->GetbItem(CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM) == true)
	{
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM] == nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM] = CKeyTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_nItemTextureCount, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
			m_nItemTextureCount++;
		}
	}
	if (pPlayer2->GetbItem(CItemObject::ITEM_OBJECT_KEY_PC_ROOM) == true)
	{
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PC_ROOM] == nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PC_ROOM] = CKeyTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_nItemTextureCount, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
			m_nItemTextureCount++;
		}
	}
	if (pPlayer2->GetbItem(CItemObject::ITEM_OBJECT_BATON) == true)
	{
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_BATON] == nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_BATON] = CBatonTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_nItemTextureCount, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
			m_nItemTextureCount++;
		}
	}
	if (pPlayer2->GetbItem(CItemObject::ITEM_OBJECT_MAP) == true)
	{
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_MAP] == nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_MAP] = CMapTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_nItemTextureCount, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
			m_nItemTextureCount++;
		}
	}
}