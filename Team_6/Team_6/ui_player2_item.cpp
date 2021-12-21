//=============================================================================
// プレイヤー2アイテムUI [ui_player2_item.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// インクルードファイル
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
// マクロ定義
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CPlayer2ItemUI::CPlayer2ItemUI()
{
	m_nItemTextureCount = ZERO_INT;		// アイテムテクスチャ生成数
	m_nSelectCount = ZERO_INT;			// アイテム選択のカウント
	m_pSelectItemFlame = nullptr;		// アイテム選択枠のポインタ
	for (int nCount = 0; nCount < CItemObject::ITEM_OBJECT_MAX; nCount++)
	{
		m_apItemTexture[nCount] = nullptr;		// アイテムテクスチャのポインタ
	}
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CPlayer2ItemUI::~CPlayer2ItemUI()
{
}

//=============================================================================
// 生成処理関数
// Author : Nikaido Taichi
//=============================================================================
CPlayer2ItemUI * CPlayer2ItemUI::Create(void)
{
	// CPlayer2ItemUIのポインタ
	CPlayer2ItemUI *pPlayer1UI = nullptr;

	// nullcheck
	if (pPlayer1UI == nullptr)
	{
		// メモリ確保
		pPlayer1UI = new CPlayer2ItemUI;

		// !nullcheck
		if (pPlayer1UI != nullptr)
		{
			// 初期化処理
			pPlayer1UI->Init();
		}
	}
	// ポインタを返す
	return pPlayer1UI;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CPlayer2ItemUI::Init(void)
{
	CUIFlameTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 110.0f, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(200.0f, 60.0f, 0.0f));
	m_pSelectItemFlame = CSelectItemFlame::Create(D3DXVECTOR3(1236.5f, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(61.5f, 59.5f, 0.0f));
	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPlayer2ItemUI::Uninit(void)
{
	//------------------------
	//　牢屋のカギ
	//------------------------
	if (m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PRISON] != nullptr)
	{
		m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PRISON]->Uninit();
		m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PRISON] = nullptr;
	}
	//------------------------
	//　倉庫のカギ
	//------------------------
	if (m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_STORAGE] != nullptr)
	{
		m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_STORAGE]->Uninit();
		m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_STORAGE] = nullptr;
	}
	//------------------------
	//　看守のカギ
	//------------------------
	if (m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM] != nullptr)
	{
		m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM]->Uninit();
		m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM] = nullptr;
	}
	//------------------------
	//　PC室のカギ
	//------------------------
	if (m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PC_ROOM] != nullptr)
	{
		m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PC_ROOM]->Uninit();
		m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PC_ROOM] = nullptr;
		m_nItemTextureCount--;
	}
	//------------------------
	//　警棒
	//------------------------
	if (m_apItemTexture[CItemObject::ITEM_OBJECT_BATON] != nullptr)
	{
		m_apItemTexture[CItemObject::ITEM_OBJECT_BATON]->Uninit();
		m_apItemTexture[CItemObject::ITEM_OBJECT_BATON] = nullptr;
	}
	//------------------------
	//　マップ
	//------------------------
	if (m_apItemTexture[CItemObject::ITEM_OBJECT_MAP] != nullptr)
	{
		m_apItemTexture[CItemObject::ITEM_OBJECT_MAP]->Uninit();
		m_apItemTexture[CItemObject::ITEM_OBJECT_MAP] = nullptr;
	}
	m_nItemTextureCount = 0;
}

//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPlayer2ItemUI::Update(void)
{
	// UI生成処理
	ItemGetGuideUICreate();
	PlayerItemGet();
}

//=============================================================================
// 入力処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPlayer2ItemUI::PlayerItemGet(void)
{
	// キーボード取得
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	// パッド取得
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
// UI生成処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPlayer2ItemUI::ItemGetGuideUICreate(void)
{
	// ゲームモードの取得
	CGame * pGame = ((CGame*)CManager::GetModePtr());
	// プレイヤーの取得
	CPlayer * pPlayer2 = pGame->GetPlayer(1);
	// 牢屋の鍵
	if (pPlayer2->GetbItem(CItemObject::ITEM_OBJECT_KEY_PRISON) == true)
	{
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PRISON] == nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PRISON] = CPrisonKeyTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_nItemTextureCount, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
			// アイテムテクスチャのカウントを加算する
			m_nItemTextureCount++;
		}
	}
	// 倉庫の鍵
	if (pPlayer2->GetbItem(CItemObject::ITEM_OBJECT_KEY_STORAGE) == true)
	{
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_STORAGE] == nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_STORAGE] = CStorageKeyTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_nItemTextureCount, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
			// アイテムテクスチャのカウントを加算する
			m_nItemTextureCount++;
		}
	}
	// 看守の鍵
	if (pPlayer2->GetbItem(CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM) == true)
	{
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM] == nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM] = CJailerKeyTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_nItemTextureCount, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
			// アイテムテクスチャのカウントを加算する
			m_nItemTextureCount++;
		}
	}
	// PC室の鍵
	if (pPlayer2->GetbItem(CItemObject::ITEM_OBJECT_KEY_PC_ROOM) == true)
	{
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PC_ROOM] == nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PC_ROOM] = CPCRoomKeyTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_nItemTextureCount, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
			// アイテムテクスチャのカウントを加算する
			m_nItemTextureCount++;
		}
	}
	// 警棒
	if (pPlayer2->GetbItem(CItemObject::ITEM_OBJECT_BATON) == true)
	{
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_BATON] == nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_BATON] = CBatonTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_nItemTextureCount, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
			// アイテムテクスチャのカウントを加算する
			m_nItemTextureCount++;
		}
	}
	// マップ
	if (pPlayer2->GetbItem(CItemObject::ITEM_OBJECT_MAP) == true)
	{
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_MAP] == nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_MAP] = CMapUITexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_nItemTextureCount, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
			// アイテムテクスチャのカウントを加算する
			m_nItemTextureCount++;
		}
	}
}