//=============================================================================
// 制御室の扉 [control_room_door.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "electrical_room_door.h"
#include "object.h"
#include "manager.h"
#include "resource_manager.h"
#include "electrical_room_door_collision.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(130.0f,330.0f,25.0f))	// サイズ
#define COLLISION_SIZE2	(D3DXVECTOR3(25.0f,330.0f,130.0f))	// サイズ
#define ROT_90			(D3DXToRadian(89.0f))				// 向き
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CEletrical_Room_Door::CEletrical_Room_Door(PRIORITY Priority)
{
}
//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CEletrical_Room_Door::~CEletrical_Room_Door()
{
}
//=============================================================================
// 生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
CEletrical_Room_Door * CEletrical_Room_Door::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CEletrical_Room_Doorのポインタ
	CEletrical_Room_Door *pEletrical_Room_Door = nullptr;

	// nullcheck
	if (pEletrical_Room_Door == nullptr)
	{
		// メモリ確保
		pEletrical_Room_Door = new CEletrical_Room_Door;

		// !nullcheck
		if (pEletrical_Room_Door != nullptr)
		{
			// 初期化処理
			pEletrical_Room_Door->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pEletrical_Room_Door;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CEletrical_Room_Door::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ドアの初期化処理関数呼び出し
	CDoor::Init(pos, rot);

	// サイズ
	SetSize(COLLISION_SIZE);

	// モデル情報取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデル情報取得
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_DOOR);

		// モデルの情報を渡す
		BindModel(model);
	}

	// 90以上の場合
	if (rot.y >= ROT_90)
	{
		// サイズ
		SetSize(COLLISION_SIZE2);
	}

	// 判定用のオブジェクト生成
	CElectrical_Room_Door_Collision::Create(pos, rot, this);
	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEletrical_Room_Door::Uninit(void)
{
	// ドアの終了処理関数呼び出し
	CDoor::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEletrical_Room_Door::Update(void)
{
	// ドアの更新処理関数呼び出し
	CDoor::Update();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CEletrical_Room_Door::Draw(void)
{
	// ドアの描画処理関数呼び出し
	CDoor::Draw();
}