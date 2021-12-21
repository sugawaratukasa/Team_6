//=============================================================================
// 看守室ドアの判定 [guards_door_collision.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "guards_door_collision.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(150.0f,550.0f,150.0f))	// サイズ
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CGuards_Door_Collision::CGuards_Door_Collision(PRIORITY Priority) : CDoor_Collision(Priority)
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CGuards_Door_Collision::~CGuards_Door_Collision()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CGuards_Door_Collision * CGuards_Door_Collision::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CDoor *pDoor)
{
	// CGuards_Door_Collisionのポインタ
	CGuards_Door_Collision *pPrison_Door_Collision = nullptr;

	// nullcheck
	if (pPrison_Door_Collision == nullptr)
	{
		// メモリ確保
		pPrison_Door_Collision = new CGuards_Door_Collision;

		// !nullcheck
		if (pPrison_Door_Collision != nullptr)
		{
			// 初期化処理
			pPrison_Door_Collision->Init(pos, rot);

			// ポインタを代入
			pPrison_Door_Collision->SetpDoor(pDoor);
		}
	}
	// ポインタを返す
	return pPrison_Door_Collision;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CGuards_Door_Collision::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 初期化処理
	CDoor_Collision::Init(pos, rot);

	// タイプ設定
	SetType(TYPE_JAILER_ROOM);

	// サイズ設定
	SetSize(COLLISION_SIZE);
	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CGuards_Door_Collision::Uninit(void)
{
	// 終了処理
	CDoor_Collision::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CGuards_Door_Collision::Update(void)
{
	// 更新処理
	CDoor_Collision::Update();

	// CDoorのポインタ取得
	CDoor *pDoor = GetpDoor();

	// ロック状態設定
	SetLock(pDoor->GetLock());
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CGuards_Door_Collision::Draw(void)
{
}