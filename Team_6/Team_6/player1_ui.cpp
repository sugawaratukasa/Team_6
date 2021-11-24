//=============================================================================
// プレイヤー1UI [player1_ui.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// インクルードファイル
// Author : Nikaido Taichi
//=============================================================================
#include "main.h"
#include "manager.h"
#include "mode_base.h"
#include "player1_ui.h"
#include "ui_flame_texture.h"
#include "item_object.h"
#include "baton_texture.h"
#include "map_texture.h"
#include "key_texture.h"
#include "game.h"
#include "player.h"
#include "select_item_flame.h"
#include "keyboard.h"

//=============================================================================
// マクロ定義
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CPlayer1UI::CPlayer1UI()
{
	m_nItemTextureCount = 0;
	m_nSelectFlame = 0;
	for (int nCount = 0; nCount < CItemObject::ITEM_OBJECT_MAX; nCount++)
	{
		m_apItemTexture[nCount] = nullptr;
	}
	m_pSelectItemFlame = nullptr;
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CPlayer1UI::~CPlayer1UI()
{
}

//=============================================================================
// 生成処理関数
// Author : Nikaido Taichi
//=============================================================================
CPlayer1UI * CPlayer1UI::Create(void)
{
	// CPlayer1UIのポインタ
	CPlayer1UI *pPlayer1UI = nullptr;

	// nullcheck
	if (pPlayer1UI == nullptr)
	{
		// メモリ確保
		pPlayer1UI = new CPlayer1UI;

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
HRESULT CPlayer1UI::Init(void)
{
	CUIFlameTexture::Create(D3DXVECTOR3(110.0f, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(200.0f, 60.0f, 0.0f));
	m_pSelectItemFlame = CSelectItemFlame::Create(D3DXVECTOR3(42.5f, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(61.5f, 59.5f, 0.0f));
	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPlayer1UI::Uninit(void)
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
// 更新関数処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPlayer1UI::Update(void)
{
	// UI生成処理
	UICreate();
	Input();
}

void CPlayer1UI::Input(void)
{
	// キーボード取得
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	if (pKeyboard->GetTrigger(DIK_I))
	{
		if (m_nSelectFlame > 0)
		{
			m_nSelectFlame--;
		}
	}
	if (pKeyboard->GetTrigger(DIK_O))
	{
		if (m_nSelectFlame < 2)
		{
			m_nSelectFlame++;
		}
	}
	switch (m_nSelectFlame)
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
// UI生成処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPlayer1UI::UICreate(void)
{
	CGame * pGame = ((CGame*)CManager::GetModePtr());
	CPlayer * pPlayer1 = pGame->GetPlayer(0);
	//------------------------
	//　牢屋のカギ
	//------------------------
	if (pPlayer1->GetbItem(CItemObject::ITEM_OBJECT_KEY_PRISON) == true)
	{
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PRISON] == nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PRISON] = CKeyTexture::Create(D3DXVECTOR3(50 + 65.0f * m_nItemTextureCount, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
			m_nItemTextureCount++;
		}
	}
	//------------------------
	//　倉庫のカギ
	//------------------------
	if (pPlayer1->GetbItem(CItemObject::ITEM_OBJECT_KEY_STORAGE) == true)
	{
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_STORAGE] == nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_STORAGE] = CKeyTexture::Create(D3DXVECTOR3(50 + 65.0f * m_nItemTextureCount, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
			m_nItemTextureCount++;
		}
	}
	//------------------------
	//　看守のカギ
	//------------------------
	if (pPlayer1->GetbItem(CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM) == true)
	{
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM] == nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM] = CKeyTexture::Create(D3DXVECTOR3(50 + 65.0f * m_nItemTextureCount, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
			m_nItemTextureCount++;
		}
	}
	//------------------------
	//　PC室のカギ
	//------------------------
	if (pPlayer1->GetbItem(CItemObject::ITEM_OBJECT_KEY_PC_ROOM) == true)
	{
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PC_ROOM] == nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_KEY_PC_ROOM] = CKeyTexture::Create(D3DXVECTOR3(50 + 65.0f * m_nItemTextureCount, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
			m_nItemTextureCount++;
		}
	}
	//------------------------
	//　警棒
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
	//　マップ
	//------------------------
	if (pPlayer1->GetbItem(CItemObject::ITEM_OBJECT_MAP) == true)
	{
		if (m_apItemTexture[CItemObject::ITEM_OBJECT_MAP] == nullptr)
		{
			m_apItemTexture[CItemObject::ITEM_OBJECT_MAP] = CMapTexture::Create(D3DXVECTOR3(50 + 65.0f * m_nItemTextureCount, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
			m_nItemTextureCount++;
		}
	}
}