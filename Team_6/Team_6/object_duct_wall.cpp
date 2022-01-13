//=============================================================================
// ダクト [object_duct_wall.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "object_duct_wall.h"
#include "resource_manager.h"
#include "duct_collision.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(180.0f,500.0f,25.0f))		// サイズ
#define COLLISION_SIZE2	(D3DXVECTOR3(25.0f,500.0f,180.0f))		// サイズ
#define COLLISION_POS	(D3DXVECTOR3(pos.x + 50.0f,0.0f,pos.z))	// 位置
#define COLLISION_POS2	(D3DXVECTOR3(pos.x - 50.0f,0.0f,pos.z))	// 位置
#define ROT_90			(D3DXToRadian(89.0f))					// 向き

//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CDuct_Wall::CDuct_Wall(PRIORITY Priority) : CObject(Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CDuct_Wall::~CDuct_Wall()
{
}
//=============================================================================
// 生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
CDuct_Wall * CDuct_Wall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CKeepOut_Wallのポインタ
	CDuct_Wall *pDuct_Wall = nullptr;

	// nullcheck
	if (pDuct_Wall == nullptr)
	{
		// メモリ確保
		pDuct_Wall = new CDuct_Wall;

		// !nullcheck
		if (pDuct_Wall != nullptr)
		{
			// 初期化処理
			pDuct_Wall->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pDuct_Wall;
}

//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CDuct_Wall::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// サイズ
	SetSize(COLLISION_SIZE);

	// 初期化処理
	CObject::Init(pos, rot);

	// モデル情報取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデル情報取得
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_DUCT);

		// モデルの情報を渡す
		BindModel(model);
	}

	// 90以上の場合
	if (rot.y >= ROT_90)
	{
		// サイズ
		SetSize(COLLISION_SIZE2);
	}

	// 種類設定
	SetType(TYPE_WALL);

	// 判定生成
	CDuct_Collision::Create(COLLISION_POS, ZeroVector3, CDuct_Collision::TYPE_LEFT);
	CDuct_Collision::Create(COLLISION_POS2, ZeroVector3, CDuct_Collision::TYPE_RIGHT);
	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CDuct_Wall::Uninit(void)
{
	// 終了処理
	CObject::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CDuct_Wall::Update(void)
{
	// 更新処理
	CObject::Update();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CDuct_Wall::Draw(void)
{
	// 描画処理
	CObject::Draw();
}