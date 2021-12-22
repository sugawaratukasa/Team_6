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
#include "storage_door_collision.h"
#include "textlog.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(120.0f,450.0f,120.0f))	// サイズ
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CStorage_Door_Collision::CStorage_Door_Collision(PRIORITY Priority) : CDoor_Collision(Priority)
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CStorage_Door_Collision::~CStorage_Door_Collision()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CStorage_Door_Collision * CStorage_Door_Collision::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CDoor *pDoor)
{
	// CStorage_Door_Collisionのポインタ
	CStorage_Door_Collision *pControl_Room_Door_Collision = nullptr;

	// nullcheck
	if (pControl_Room_Door_Collision == nullptr)
	{
		// メモリ確保
		pControl_Room_Door_Collision = new CStorage_Door_Collision;

		// !nullcheck
		if (pControl_Room_Door_Collision != nullptr)
		{
			// 初期化処理
			pControl_Room_Door_Collision->Init(pos, rot);

			// ポインタを代入
			pControl_Room_Door_Collision->SetpDoor(pDoor);
		}
	}
	// ポインタを返す
	return pControl_Room_Door_Collision;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CStorage_Door_Collision::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 初期化処理
	CDoor_Collision::Init(pos, rot);

	// タイプ設定
	SetType(TYPE_STORAGE);

	// サイズ設定
	SetSize(COLLISION_SIZE);
	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CStorage_Door_Collision::Uninit(void)
{
	// 終了処理
	CDoor_Collision::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CStorage_Door_Collision::Update(void)
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
void CStorage_Door_Collision::Draw(void)
{
}
//=============================================================================
// 開く処理
// Author : Sugawara Tsukasa
//=============================================================================
void CStorage_Door_Collision::Open(void)
{
	// 開く処理
	CDoor_Collision::Open();

	// テキストログ生成
	//CTextLog::Create();
}