//=============================================================================
// �v���C���[2�A�C�e��UI [ui_player2_item.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Nikaido Taichi
//=============================================================================
#include "main.h"
#include "manager.h"
#include "mode_base.h"
#include "ui_player2_item.h"
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
CPlayer2ItemUI::CPlayer2ItemUI()
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
CPlayer2ItemUI::~CPlayer2ItemUI()
{
}

//=============================================================================
// ���������֐�
// Author : Nikaido Taichi
//=============================================================================
CPlayer2ItemUI * CPlayer2ItemUI::Create(void)
{
	// CPlayer2ItemUI�̃|�C���^
	CPlayer2ItemUI *pPlayer1UI = nullptr;

	// nullcheck
	if (pPlayer1UI == nullptr)
	{
		// �������m��
		pPlayer1UI = new CPlayer2ItemUI;

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
HRESULT CPlayer2ItemUI::Init(void)
{
	CUIFlameTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 110.0f, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(200.0f, 60.0f, 0.0f));
	m_pSelectItemFlame = CSelectItemFlame::Create(D3DXVECTOR3(1236.5f, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(61.5f, 59.5f, 0.0f));
	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayer2ItemUI::Uninit(void)
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
void CPlayer2ItemUI::Update(void)
{
	// UI��������
	ItemGetGuideUICreate();
	PlayerItemGet();
}

//=============================================================================
// ���͏����֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayer2ItemUI::PlayerItemGet(void)
{
	// �L�[�{�[�h�擾
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	// �p�b�h�擾
	CInputJoypad * pJoypad = CManager::GetJoypad();

	if (pKeyboard->GetTrigger(DIK_J) || pJoypad != nullptr && pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R_TRIGGER, 1))
	{
		if (m_nSelectCount < 2)
		{
			m_nSelectCount++;
		}
	}
	if (pKeyboard->GetTrigger(DIK_K) || pJoypad != nullptr && pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_L_TRIGGER, 1))
	{
		if (m_nSelectCount > 0)
		{
			m_nSelectCount--;
		}
	}
	switch (m_nSelectCount)
	{
	case 0:
		m_pSelectItemFlame->SetPosition(D3DXVECTOR3(1236.5f, SCREEN_HEIGHT - 40.0f, 0.0f));
		break;
	case 1:
		m_pSelectItemFlame->SetPosition(D3DXVECTOR3(1170.5f, SCREEN_HEIGHT - 40.0f, 0.0f));
		break;
	case 2:
		m_pSelectItemFlame->SetPosition(D3DXVECTOR3(1103.5f, SCREEN_HEIGHT - 40.0f, 0.0f));
		break;
	default:
		break;
	}
}

//=============================================================================
// UI���������֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayer2ItemUI::ItemGetGuideUICreate(void)
{
	// �Q�[�����[�h�̎擾
	CGame * pGame = ((CGame*)CManager::GetModePtr());
	// �v���C���[�̎擾
	CPlayer * pPlayer2 = pGame->GetPlayer(1);
	// �S���̌�
	if (pPlayer2->GetbItem(CItemObject::ITEM_OBJECT_KEY_PRISON) == true)
	{
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PRISON] == nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PRISON] = CPrisonKeyTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_nItemTextureCount, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
			// �A�C�e���e�N�X�`���̃J�E���g�����Z����
			m_nItemTextureCount++;
		}
	}
	// �q�ɂ̌�
	if (pPlayer2->GetbItem(CItemObject::ITEM_OBJECT_KEY_STORAGE) == true)
	{
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_STORAGE] == nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_STORAGE] = CStorageKeyTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_nItemTextureCount, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
			// �A�C�e���e�N�X�`���̃J�E���g�����Z����
			m_nItemTextureCount++;
		}
	}
	// �Ŏ�̌�
	if (pPlayer2->GetbItem(CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM) == true)
	{
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM] == nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM] = CJailerKeyTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_nItemTextureCount, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
			// �A�C�e���e�N�X�`���̃J�E���g�����Z����
			m_nItemTextureCount++;
		}
	}
	// PC���̌�
	if (pPlayer2->GetbItem(CItemObject::ITEM_OBJECT_KEY_PC_ROOM) == true)
	{
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PC_ROOM] == nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PC_ROOM] = CPCRoomKeyTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_nItemTextureCount, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
			// �A�C�e���e�N�X�`���̃J�E���g�����Z����
			m_nItemTextureCount++;
		}
	}
	// �x�_
	if (pPlayer2->GetbItem(CItemObject::ITEM_OBJECT_BATON) == true)
	{
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_BATON] == nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_BATON] = CBatonTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_nItemTextureCount, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
			// �A�C�e���e�N�X�`���̃J�E���g�����Z����
			m_nItemTextureCount++;
		}
	}
	// �}�b�v
	if (pPlayer2->GetbItem(CItemObject::ITEM_OBJECT_MAP) == true)
	{
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_MAP] == nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_MAP] = CMapUITexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_nItemTextureCount, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
			// �A�C�e���e�N�X�`���̃J�E���g�����Z����
			m_nItemTextureCount++;
		}
	}
}