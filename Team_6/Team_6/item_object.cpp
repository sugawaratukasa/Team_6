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

//=============================================================================
// マクロ定義
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CItemObject::CItemObject(PRIORITY Priority) : CModel(Priority)
{
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
	// 初期化処理
	CModel::Init(pos, rot);
	CModelCollisionBox::Create(pos, rot, this);
	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CItemObject::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CItemObject::Update(void)
{
	// 更新処理
	CModel::Update();
	// 衝突処理関数呼び出し
	Collision();
}
//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CItemObject::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=============================================================================
// 衝突処理関数
// Author : Nikaido Taichi
//=============================================================================
void CItemObject::Collision(void)
{
	// 位置を取得する
	D3DXVECTOR3 Position = GetPos();
	// サイズを取得する
	D3DXVECTOR3 Size = GetSize();
	// プレイヤーのポインタ
	CPlayer * apPlayer[MAX_PLAYER];
	// プレイヤーの最大数分回す
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		// プレイヤーのポインタを取得する
		apPlayer[nCount] = CManager::GetModePtr()->GetPlayer(nCount);
		// !nullcheck
		if (apPlayer[nCount] != nullptr)
		{
			//もしプレイヤーのアイテムの取得数が最大値以下の場合
			if (apPlayer[nCount]->GetItemCount() < MAX_ITEM)
			{
				// プレイヤーの位置を取得する
				D3DXVECTOR3 PlayerPosition = apPlayer[nCount]->GetPos();
				// プレイヤーのサイズを取得する
				D3DXVECTOR3 PlayerSize = apPlayer[nCount]->GetSize();
				// アイテムとプレイヤーの矩形型の当たり判定
				if (CCollision::CollisionRectangleAndRectangle(Position, PlayerPosition, Size, PlayerSize) == true)
				{
					// プレイヤーにアイテムを設定する
					apPlayer[nCount]->SetItem(this->GetType(), this);
					// 終了処理関数呼び出し
					Uninit();
					return;
				}
			}
		}
	}
}