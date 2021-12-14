//=============================================================================
// ドアの壁クラス [object_door.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define ROT_90				(D3DXToRadian(89.0f))						// 90向き
#define COLLISION_POS_ADDX	(D3DXVECTOR3(pos.x + 85.0f,pos.y,pos.z))	// 位置
#define COLLISION_POS_SUBX	(D3DXVECTOR3(pos.x - 85.0f, pos.y, pos.z))	// 位置
#define COLLISION_POS_ADDZ	(D3DXVECTOR3(pos.x, pos.y, pos.z + 85.0f))	// 位置
#define COLLISION_POS_SUBZ	(D3DXVECTOR3(pos.x, pos.y, pos.z - 85.0f))	// 位置
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "object_door_wall.h"
#include "resource_manager.h"
#include "door_wall_collision.h"
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CDoor_Wall::CDoor_Wall(PRIORITY Priority) : CObject(Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CDoor_Wall::~CDoor_Wall()
{
}
//=============================================================================
// 生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
CDoor_Wall * CDoor_Wall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CDoor_Wallのポインタ
	CDoor_Wall *pDoor_Wall = nullptr;

	// nullcheck
	if (pDoor_Wall == nullptr)
	{
		// メモリ確保
		pDoor_Wall = new CDoor_Wall;

		// !nullcheck
		if (pDoor_Wall != nullptr)
		{
			// 初期化処理
			pDoor_Wall->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pDoor_Wall;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CDoor_Wall::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 初期化処理
	CObject::Init(pos, rot);

	// モデル情報取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデル情報取得
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_DOOR_WALL);

		// モデルの情報を渡す
		BindModel(model);
	}
	// 90以上の場合
	if (rot.y >= ROT_90)
	{
		// 生成
		CDoorWallCollision::Create(COLLISION_POS_ADDZ, rot);
		CDoorWallCollision::Create(COLLISION_POS_SUBZ, rot);
	}
	// 例外
	else
	{
		// 生成
		CDoorWallCollision::Create(COLLISION_POS_ADDX, rot);
		CDoorWallCollision::Create(COLLISION_POS_SUBX, rot);
	}

	// 種類設定
	SetType(TYPE_WALL);

	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CDoor_Wall::Uninit(void)
{
	// 終了処理
	CObject::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CDoor_Wall::Update(void)
{
	// 更新処理
	CObject::Update();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CDoor_Wall::Draw(void)
{
	// 描画処理
	CObject::Draw();
}