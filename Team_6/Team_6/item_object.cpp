//=============================================================================
// アイテムオブジェクト [item_object.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// インクルードファイル
// Author : Nikaido Taichi
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "character.h"
#include "collision.h"
#include "game.h"
#include "player.h"
#include "item_object.h"
#include "game.h"
#include "model_collision_box.h"
#include "keyboard.h"
#include "joypad.h"
#include "scene.h"
#include "manager.h"
#include "resource_manager.h"
#include "sound.h"

//=============================================================================
// マクロ定義
// Author : Nikaido Taichi
//=============================================================================
#define COLLISION_SIZE (D3DXVECTOR3(550.0f,550.0f,550.0f))
//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CItemObject::CItemObject(PRIORITY Priority) : CScene(Priority)
{
	m_Position = ZeroVector3;		// 位置
	m_Size = ZeroVector3;			// サイズ
	m_Rotation = ZeroVector3;		// 向き
	m_Type = ITEM_OBJECT_NONE;		// タイプ
}
//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CItemObject::~CItemObject()
{
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CItemObject::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_Position = pos;
	m_Rotation = rot;
	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CItemObject::Uninit(void)
{
	Release();
}

//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CItemObject::Update(void)
{
	// 衝突処理関数呼び出し
	Collision();
}
//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CItemObject::Draw(void)
{
}

//=============================================================================
// 衝突処理関数
// Author : Nikaido Taichi
//=============================================================================
void CItemObject::Collision(void)
{
	// キーボード取得
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	// パッド取得
	CInputJoypad * pJoypad = CManager::GetJoypad();
	// プレイヤーの位置
	D3DXVECTOR3 PlayerPosition[MAX_PLAYER];
	// プレイヤーのサイズ
	D3DXVECTOR3 PlayerSize[MAX_PLAYER];
	// プレイヤーのポインタ
	CPlayer * apPlayer[MAX_PLAYER];
	CSound * pSound = GET_SOUND_PTR;
	// プレイヤーの最大数分回す
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		// プレイヤーのポインタを取得する
		apPlayer[nCount] = CManager::GetModePtr()->GetPlayer(nCount);
		// !nullcheck
		if (apPlayer[nCount] != nullptr)
		{
			// プレイヤーの位置を取得する
			PlayerPosition[nCount] = apPlayer[nCount]->GetPos();
			// プレイヤーのサイズを取得する
			PlayerSize[nCount] = apPlayer[nCount]->GetSize();
			// アイテムとプレイヤーの矩形型の当たり判定
			if (CCollision::CollisionRectangleAndRectangle(m_Position, PlayerPosition[nCount], COLLISION_SIZE, PlayerSize[nCount]) == true)
			{
				if (nCount == CPlayer::PLAYER_1 && pKeyboard->GetTrigger(DIK_U) || nCount == CPlayer::PLAYER_2 && pKeyboard->GetTrigger(DIK_H))
				{
					if (apPlayer[nCount]->GetItemCount() < MAX_ITEM && apPlayer[nCount]->GetbGuidCreate() == false)
					{
						// プレイヤーにアイテムを設定する
						apPlayer[nCount]->SetAddbGetItem(this->GetType(), true);
						apPlayer[nCount]->SetbGuidCreate(this->GetType());
						pSound->CSound::Play(CSound::SOUND_SE_GET_ITEM);
						// 終了処理関数呼び出し
						Uninit();
						return;
					}
				}
			}
		}
	}
}