//=============================================================================
// プレイヤーUIマネージャー [player_ui_manager.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// インクルードファイル
// Author : Nikaido Taichi
//=============================================================================
#include "main.h"
#include "manager.h"
#include "mode_base.h"
#include "player_ui_manager.h"
#include "ui_flame_texture.h"
#include "player.h"
#include "player_1.h"
#include "player_2.h"
#include "item_object.h"
#include "baton_texture.h"
#include "map_texture.h"
#include "key_texture.h"

//=============================================================================
// マクロ定義
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CPlayerUIManager::CPlayerUIManager()
{
	for (int nCount = 0; nCount < 2; nCount++)
	{
		m_anItemTextureCount[nCount] = 0;
	}
	for (int nCountPlayer = 0; nCountPlayer < 2; nCountPlayer++)
	{
		for (int nCountTexture = 0; nCountTexture < CItemObject::ITEM_OBJECT_MAX; nCountTexture++)
		{
			m_apItemTexture[nCountPlayer][nCountTexture] = nullptr;
		}
	}
}
//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CPlayerUIManager::~CPlayerUIManager()
{
}

CPlayerUIManager * CPlayerUIManager::Create(void)
{
	// CPlayerUIManagerのポインタ
	CPlayerUIManager *pPlayerUIManager = nullptr;

	// nullcheck
	if (pPlayerUIManager == nullptr)
	{
		// メモリ確保
		pPlayerUIManager = new CPlayerUIManager;

		// !nullcheck
		if (pPlayerUIManager != nullptr)
		{
			// 初期化処理
			pPlayerUIManager->Init();
		}
	}
	// ポインタを返す
	return pPlayerUIManager;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CPlayerUIManager::Init(void)
{
	CUIFlameTexture::Create(D3DXVECTOR3(110.0f, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(200.0f, 60.0f, 0.0f));
	CUIFlameTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 110.0f, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(200.0f, 60.0f, 0.0f));
	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPlayerUIManager::Uninit(void)
{
}

//=============================================================================
// 更新関数処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPlayerUIManager::Update(void)
{
	UICreate();
}

void CPlayerUIManager::UICreate(void)
{
	// プレイヤーのポインタ
	CPlayer * apPlayer[MAX_PLAYER];
	// プレイヤーのアイテム情報
	CItemObject *  apPlayerItem[MAX_PLAYER][CItemObject::ITEM_OBJECT_MAX];
	// プレイヤーカウント
	int nCountPlayer = 0;
	// アイテムカウント
	int nCountItem = 0;
	// プレイヤーの最大数分回す
	for (nCountPlayer = 0; nCountPlayer < MAX_PLAYER; nCountPlayer++)
	{
		// プレイヤーのポインタを取得する
		apPlayer[nCountPlayer] = CManager::GetModePtr()->GetPlayer(nCountPlayer);
		// アイテムの最大数分回す
		for (nCountItem = 0; nCountItem < CItemObject::ITEM_OBJECT_MAX; nCountItem++)
		{
			// プレイヤーのアイテム情報を取得する
			apPlayerItem[nCountPlayer][nCountItem] = apPlayer[nCountPlayer]->GetItem(nCountItem);
			if (apPlayerItem[nCountPlayer][nCountItem] != nullptr)
			{
				switch (nCountItem)
				{
				case CItemObject::ITEM_OBJECT_KEY_PRISON:
					if (nCountPlayer == 0)
					{
						if (m_apItemTexture[0][CItemObject::ITEM_OBJECT_KEY_PRISON] == nullptr)
						{
							m_apItemTexture[0][CItemObject::ITEM_OBJECT_KEY_PRISON] = CKeyTexture::Create(D3DXVECTOR3(50 + 65.0f * m_anItemTextureCount[0], SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
							m_anItemTextureCount[0]++;
						}
					}
					if (nCountPlayer == 1)
					{
						{
							if (m_apItemTexture[1][CItemObject::ITEM_OBJECT_KEY_PRISON] == nullptr)
							{
								m_apItemTexture[1][CItemObject::ITEM_OBJECT_KEY_PRISON] = CKeyTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_anItemTextureCount[1], SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
								m_anItemTextureCount[1]++;
							}
						}
					}
					break;
				case CItemObject::ITEM_OBJECT_KEY_STORAGE:
					if (nCountPlayer == 0)
					{
						if (m_apItemTexture[0][CItemObject::ITEM_OBJECT_KEY_STORAGE] == nullptr)
						{
							m_apItemTexture[0][CItemObject::ITEM_OBJECT_KEY_STORAGE] = CKeyTexture::Create(D3DXVECTOR3(50 + 65.0f * m_anItemTextureCount[0], SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
							m_anItemTextureCount[0]++;
						}
					}
					if (nCountPlayer == 1)
					{
						if (m_apItemTexture[1][CItemObject::ITEM_OBJECT_KEY_STORAGE] == nullptr)
						{
							m_apItemTexture[1][CItemObject::ITEM_OBJECT_KEY_STORAGE] = CKeyTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_anItemTextureCount[1], SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
							m_anItemTextureCount[1]++;
						}
					}
					break;
				case CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM:
					if (nCountPlayer == 0)
					{
						if (m_apItemTexture[0][CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM] == nullptr)
						{
							m_apItemTexture[0][CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM] = CKeyTexture::Create(D3DXVECTOR3(50 + 65.0f * m_anItemTextureCount[0], SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
							m_anItemTextureCount[0]++;
						}
					}
					if (nCountPlayer == 1)
					{
						if (m_apItemTexture[1][CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM] == nullptr)
						{
							m_apItemTexture[1][CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM] = CKeyTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_anItemTextureCount[1], SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
							m_anItemTextureCount[1]++;
						}
					}
					break;
				case CItemObject::ITEM_OBJECT_KEY_PC_ROOM:
					if (nCountPlayer == 0)
					{
						if (m_apItemTexture[0][CItemObject::ITEM_OBJECT_KEY_PC_ROOM] == nullptr)
						{
							m_apItemTexture[0][CItemObject::ITEM_OBJECT_KEY_PC_ROOM] = CKeyTexture::Create(D3DXVECTOR3(50 + 65.0f * m_anItemTextureCount[0], SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
							m_anItemTextureCount[0]++;
						}
					}
					if (nCountPlayer == 1)
					{
						if (m_apItemTexture[1][CItemObject::ITEM_OBJECT_KEY_PC_ROOM] == nullptr)
						{
							m_apItemTexture[1][CItemObject::ITEM_OBJECT_KEY_PC_ROOM] = CKeyTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_anItemTextureCount[1], SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
							m_anItemTextureCount[1]++;
						}
					}
					break;
				case CItemObject::ITEM_OBJECT_BATON:
					if (nCountPlayer == 0)
					{
						if (m_apItemTexture[0][CItemObject::ITEM_OBJECT_BATON] == nullptr)
						{
							m_apItemTexture[0][CItemObject::ITEM_OBJECT_BATON] = CBatonTexture::Create(D3DXVECTOR3(50 + 65.0f * m_anItemTextureCount[0], SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
							m_anItemTextureCount[0]++;
						}
					}
					if (nCountPlayer == 1)
					{
						if (m_apItemTexture[1][CItemObject::ITEM_OBJECT_BATON] == nullptr)
						{
							m_apItemTexture[1][CItemObject::ITEM_OBJECT_BATON] = CBatonTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_anItemTextureCount[1], SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
							m_anItemTextureCount[1]++;
						}
					}
					break;
				case CItemObject::ITEM_OBJECT_MAP:
					if (nCountPlayer == 0)
					{
						if (m_apItemTexture[0][CItemObject::ITEM_OBJECT_MAP] == nullptr)
						{
							m_apItemTexture[0][CItemObject::ITEM_OBJECT_MAP] = CMapTexture::Create(D3DXVECTOR3(50 + 65.0f * m_anItemTextureCount[0], SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
							m_anItemTextureCount[0]++;
						}
					}
					if (nCountPlayer == 1)
					{
						if (m_apItemTexture[1][CItemObject::ITEM_OBJECT_MAP] == nullptr)
						{
							m_apItemTexture[1][CItemObject::ITEM_OBJECT_MAP] = CMapTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_anItemTextureCount[1], SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
							m_anItemTextureCount[1]++;
						}
					}
					break;
				default:
					break;
				}
			}
		}
	}
}