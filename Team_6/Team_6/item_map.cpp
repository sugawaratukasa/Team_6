//=============================================================================
// マップ効果 [item_map.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// インクルードファイル
// Author : Nikaido Taichi
//=============================================================================
#include "main.h"
#include "item_map.h"
#include "map1_texture.h"
#include "map2_texture.h"
#include "player_1.h"
#include "player_2.h"
#include "manager.h"
#include "mode_base.h"
#include "item_object_map.h"
#include "player.h"
#include "game.h"
#include "keyboard.h"
#include "joypad.h"

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CItemMap::CItemMap()
{
	memset(m_abCreateMap,false,sizeof(m_abCreateMap));	// マップテクスチャ生成状態
	m_pMap1Texture = nullptr;				// マップ1テクスチャのポインタ
	m_pMap2Texture = nullptr;				// マップ2テクスチャのポインタ
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CItemMap::~CItemMap()
{
}

//=============================================================================
// 生成処理関数
// Author : Nikaido Taichi
//=============================================================================
CItemMap * CItemMap::Create(void)
{
	// CBatonTextureのポインタ
	CItemMap *pItemMap = nullptr;

	// nullcheck
	if (pItemMap == nullptr)
	{
		// メモリ確保
		pItemMap = new CItemMap;

		// !nullcheck
		if (pItemMap != nullptr)
		{
			// 初期化処理
			pItemMap->Init();
		}
	}
	// ポインタを返す
	return pItemMap;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CItemMap::Init(void)
{
	// プレイヤーにマップ取得状態を与える
	SetPlayerItemGetList(CPlayer::ITEM_MAP);
	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CItemMap::Uninit(void)
{
	if (m_pMap1Texture != nullptr)
	{
		m_pMap1Texture->Uninit();
		m_pMap1Texture = nullptr;
	}
	if (m_pMap2Texture != nullptr)
	{
		m_pMap2Texture->Uninit();
		m_pMap2Texture = nullptr;
	}
}

//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CItemMap::Update(void)
{
	// プレイヤーアイテム取得情報を取得する
	PlayerItemGet();
}

//=============================================================================
// プレイヤーアイテム取得情報取得処理関数
// Author : Nikaido Taichi
//=============================================================================
void CItemMap::PlayerItemGet(void)
{
	// プレイヤーのポインタ
	CPlayer * apPlayer[MAX_PLAYER];
	// プレイヤーのアイテム所得状態
	bool abPlayerGetItem[MAX_PLAYER];
	// プレイヤーの最大数分回す
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		// プレイヤーのポインタを取得する
		apPlayer[nCount] = CManager::GetModePtr()->GetPlayer(nCount);
		// プレイヤーポインタのnullptrチェック
		if (apPlayer[nCount] != nullptr)
		{
			// プレイヤーのアイテム所得状態を取得する
			abPlayerGetItem[nCount] = apPlayer[nCount]->GetbItem(CPlayer::ITEM_MAP);
			// マップ生成処理関数
			MapCreate(nCount, abPlayerGetItem[nCount]);
		}
	}
}

//=============================================================================
// マップテクスチャ生成処理関数
// Author : Nikaido Taichi
//=============================================================================
void CItemMap::MapCreate(int nPlayer, bool bItem)
{
	// キーボード取得
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	// パッド取得
	CInputJoypad * pJoypad = CManager::GetJoypad();
	if (bItem == true)
	{
		if (nPlayer == 0 && pKeyboard->GetTrigger(DIK_B))
		{
			// マップテクスチャを生成してない場合
			if (m_abCreateMap[nPlayer] == false)
			{
				// マップテクスチャポインタのnullptrチェック
				if (m_pMap1Texture == nullptr)
				{
					// マップテクスチャを生成する
					m_pMap1Texture = CMap1Texture::Create(D3DXVECTOR3(SCREEN_WIDTH / 4 + SCREEN_WIDTH / 2 * nPlayer, SCREEN_HEIGHT / 2 + 50.0f , 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2 - 75.0f, SCREEN_HEIGHT - 150.0f, 0.0f));
					// マップテクスチャ生成状態をtrueにする
					m_abCreateMap[nPlayer] = true;
				}
			}
			// マップテクスチャを生成している場合
			else
			{
				if (m_pMap1Texture != nullptr)
				{
					// マップテクスチャの終了処理関数呼び出し
					m_pMap1Texture->Uninit();
					// マップテクスチャのポインタを初期化にする
					m_pMap1Texture = nullptr;
					// マップテクスチャ生成状態をfalseにする
					m_abCreateMap[nPlayer] = false;
				}
			}
		}
		if (nPlayer == 1 && pKeyboard->GetTrigger(DIK_N))
		{
			// マップテクスチャを生成してない場合
			if (m_abCreateMap[nPlayer] == false)
			{
				// マップテクスチャポインタのnullptrチェック
				if (m_pMap2Texture == nullptr)
				{
					// マップテクスチャを生成する
					m_pMap2Texture = CMap2Texture::Create(D3DXVECTOR3(SCREEN_WIDTH / 4 + SCREEN_WIDTH / 2 * nPlayer, SCREEN_HEIGHT / 2 + 50.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2 - 75.0f, SCREEN_HEIGHT - 150.0f, 0.0f));
					// マップテクスチャ生成状態をtrueにする
					m_abCreateMap[nPlayer] = true;
				}
			}
			// マップテクスチャを生成している場合
			else
			{
				// マップテクスチャポインタのnullptrチェック
				if (m_pMap2Texture != nullptr)
				{
					// マップテクスチャの終了処理関数呼び出し
					m_pMap2Texture->Uninit();
					// マップテクスチャのポインタを初期化にする
					m_pMap2Texture = nullptr;
					// マップテクスチャ生成状態をfalseにする
					m_abCreateMap[nPlayer] = false;
				}
			}
		}
	}
}

//=============================================================================
// マップアイテム生成処理関数
// Author : Nikaido Taichi
//=============================================================================
void CItemMap::ItemCreate(int nPlayer)
{
	CPlayer * pPlayer;
	// プレイヤーのポインタを取得する
	pPlayer = CManager::GetModePtr()->GetPlayer(nPlayer);
	// プレイヤーの位置を取得する
	D3DXVECTOR3 PlayerPos;
	PlayerPos = pPlayer->GetPos();
	// マップアイテムを生成する
	CMapObject::Create(PlayerPos, ZeroVector3);
}
