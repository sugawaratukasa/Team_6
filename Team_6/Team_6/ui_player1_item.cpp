//=============================================================================
// �v���C���[1�A�C�e��UI [ui_player1_item.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Nikaido Taichi
//=============================================================================
#include "main.h"
#include "manager.h"
#include "mode_base.h"
#include "ui_player1_item.h"
#include "ui_flame_texture.h"
#include "item_object.h"
#include "baton_texture.h"
#include "map_ui_texture.h"
#include "game.h"
#include "player.h"
#include "select_item_flame.h"
#include "keyboard.h"
#include "joypad.h"
#include "jailer_key_texture.h"
#include "pc_room_key_texture.h"
#include "prison_key_texture.h"
#include "storage_key_texture.h"

//=============================================================================
// �}�N����`
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CPlayer1ItemUI::CPlayer1ItemUI()
{
	m_nItemTextureCount = ZERO_INT;		// �A�C�e���e�N�X�`��������
	m_nSelectCount = ZERO_INT;			// �A�C�e���I���̃J�E���g
	m_pSelectItemFlame = nullptr;		// �A�C�e���I��g�̃|�C���^
	for (int nCount = 0; nCount < CItemObject::ITEM_OBJECT_MAX; nCount++)
	{
		m_apItemTexture[nCount] = nullptr;		// �A�C�e���e�N�X�`���̃|�C���^
	}
}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CPlayer1ItemUI::~CPlayer1ItemUI()
{
}

//=============================================================================
// ���������֐�
// Author : Nikaido Taichi
//=============================================================================
CPlayer1ItemUI * CPlayer1ItemUI::Create(void)
{
	// CPlayer1ItemUI�̃|�C���^
	CPlayer1ItemUI *pPlayer1UI = nullptr;

	// nullcheck
	if (pPlayer1UI == nullptr)
	{
		// �������m��
		pPlayer1UI = new CPlayer1ItemUI;

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
HRESULT CPlayer1ItemUI::Init(void)
{
	// UI�̘g����
	CUIFlameTexture::Create(D3DXVECTOR3(110.0f, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(200.0f, 60.0f, 0.0f));
	// �I�𒆃A�C�e���̘g����
	m_pSelectItemFlame = CSelectItemFlame::Create(D3DXVECTOR3(42.5f, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(61.5f, 59.5f, 0.0f));
	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayer1ItemUI::Uninit(void)
{
	//------------------------
	//�@�S���̃J�M
	//------------------------
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PRISON] != nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PRISON]->Uninit();
			m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PRISON] = nullptr;
		}
	//------------------------
	//�@�q�ɂ̃J�M
	//------------------------
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_STORAGE] != nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_STORAGE]->Uninit();
			m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_STORAGE] = nullptr;
		}
	//------------------------
	//�@�Ŏ�̃J�M
	//------------------------
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM] != nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM]->Uninit();
			m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM] = nullptr;
		}
	//------------------------
	//�@PC���̃J�M
	//------------------------
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PC_ROOM] != nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PC_ROOM]->Uninit();
			m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PC_ROOM] = nullptr;
			m_nItemTextureCount--;
		}
	//------------------------
	//�@�x�_
	//------------------------
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_BATON] != nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_BATON]->Uninit();
			m_apItemTexture[CItemObject::ITEM_OBJECT_BATON] = nullptr;
		}
	//------------------------
	//�@�}�b�v
	//------------------------
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_MAP] != nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_MAP]->Uninit();
			m_apItemTexture[CItemObject::ITEM_OBJECT_MAP] = nullptr;
		}
		m_nItemTextureCount = 0;
}

//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayer1ItemUI::Update(void)
{
	// UI��������
	ItemGetGuideUICreate();
	// ���͏���
	PlayerItemGet();
}

//=============================================================================
// ���͏����֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayer1ItemUI::PlayerItemGet(void)
{
	// �L�[�{�[�h�擾
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	// �p�b�h�擾
	CInputJoypad * pJoypad = CManager::GetJoypad();
	if (pKeyboard->GetTrigger(DIK_I) || pJoypad != nullptr && pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_L_TRIGGER,0))
	{
		if (m_nSelectCount > 0)
		{
			m_nSelectCount--;
		}
	}
	if (pKeyboard->GetTrigger(DIK_O) || pJoypad != nullptr && pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R_TRIGGER, 0))
	{
		if (m_nSelectCount < 2)
		{
			m_nSelectCount++;
		}
	}
	switch (m_nSelectCount)
	{
	case 0:
		m_pSelectItemFlame->SetPosition(D3DXVECTOR3(42.5f, SCREEN_HEIGHT - 40.0f, 0.0f));
		break;
	case 1:
		m_pSelectItemFlame->SetPosition(D3DXVECTOR3(110.0, SCREEN_HEIGHT - 40.0f, 0.0f));
		break;
	case 2:
		m_pSelectItemFlame->SetPosition(D3DXVECTOR3(177.5, SCREEN_HEIGHT - 40.0f, 0.0f));
		break;
	default:
		break;
	}
}

//=============================================================================
// UI���������֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayer1ItemUI::ItemGetGuideUICreate(void)
{
	CGame * pGame = ((CGame*)CManager::GetModePtr());
	CPlayer * pPlayer1 = pGame->GetPlayer(0);
	//------------------------
	//�@�S���̃J�M
	//------------------------
	if (pPlayer1->GetbItem(CItemObject::ITEM_OBJECT_KEY_PRISON) == true)
	{
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PRISON] == nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PRISON] = CPrisonKeyTexture::Create(D3DXVECTOR3(50 + 65.0f * m_nItemTextureCount, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
			m_nItemTextureCount++;
		}
	}
	//------------------------
	//�@�q�ɂ̃J�M
	//------------------------
	if (pPlayer1->GetbItem(CItemObject::ITEM_OBJECT_KEY_STORAGE) == true)
	{
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_STORAGE] == nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_STORAGE] = CStorageKeyTexture::Create(D3DXVECTOR3(50 + 65.0f * m_nItemTextureCount, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
			m_nItemTextureCount++;
		}
	}
	//------------------------
	//�@�Ŏ�̃J�M
	//------------------------
	if (pPlayer1->GetbItem(CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM) == true)
	{
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM] == nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM] = CJailerKeyTexture::Create(D3DXVECTOR3(50 + 65.0f * m_nItemTextureCount, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
			m_nItemTextureCount++;
		}
	}
	//------------------------
	//�@PC���̃J�M
	//------------------------
	if (pPlayer1->GetbItem(CItemObject::ITEM_OBJECT_KEY_PC_ROOM) == true)
	{
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PC_ROOM] == nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PC_ROOM] = CPCRoomKeyTexture::Create(D3DXVECTOR3(50 + 65.0f * m_nItemTextureCount, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
			m_nItemTextureCount++;
		}
	}
	//------------------------
	//�@�x�_
	//------------------------
	if (pPlayer1->GetbItem(CItemObject::ITEM_OBJECT_BATON) == true)
	{
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_BATON] == nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_BATON] = CBatonTexture::Create(D3DXVECTOR3(50 + 65.0f * m_nItemTextureCount, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
			m_nItemTextureCount++;
		}
	}
	//------------------------
	//�@�}�b�v
	//------------------------
	if (pPlayer1->GetbItem(CItemObject::ITEM_OBJECT_MAP) == true)
	{
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_MAP] == nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_MAP] = CMapUITexture::Create(D3DXVECTOR3(50 + 65.0f * m_nItemTextureCount, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
			m_nItemTextureCount++;
		}
	}
}