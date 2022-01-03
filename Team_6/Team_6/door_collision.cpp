//=============================================================================
// ドアの判定 [door_collision.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "collision.h"
#include "game.h"
#include "door_collision.h"
#include "model_collision_box.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CDoor_Collision::CDoor_Collision(PRIORITY Priority) : CModel(Priority)
{
	m_Type = TYPE_NONE;
	m_bLock = true;
	m_pDoor = nullptr;
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CDoor_Collision::~CDoor_Collision()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CDoor_Collision * CDoor_Collision::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CDoor *pDoor)
{
	// CDoor_Collisionのポインタ
	CDoor_Collision *pDoor_Collision = nullptr;

	// nullcheck
	if (pDoor_Collision == nullptr)
	{
		// メモリ確保
		pDoor_Collision = new CDoor_Collision;

		// !nullcheck
		if (pDoor_Collision != nullptr)
		{
			// 初期化処理
			pDoor_Collision->Init(pos, rot);

			// ポインタを代入
			pDoor_Collision->m_pDoor = pDoor;
		}
	}
	// ポインタを返す
	return pDoor_Collision;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CDoor_Collision::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 初期化処理
	CModel::Init(pos, rot);

	CModelCollisionBox::Create(pos, rot, this);
	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CDoor_Collision::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CDoor_Collision::Update(void)
{
	// 更新処理
	CModel::Update();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CDoor_Collision::Draw(void)
{
}
//=============================================================================
// 扉を開く処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CDoor_Collision::Open(int nPlayer)
{
	// !nullcheck
	if (m_pDoor != nullptr)
	{
		// ドアを開く
		m_pDoor->SetLock(false);
	}
}
//=============================================================================
// 扉が開けない処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CDoor_Collision::NotOpen(int nPlayer)
{
}
