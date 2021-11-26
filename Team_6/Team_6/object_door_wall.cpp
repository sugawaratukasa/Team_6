//=============================================================================
// ドアの壁クラス [object_door.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(500.0f,500.0f,500.0f))
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "object_door_wall.h"
#include "resource_manager.h"
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