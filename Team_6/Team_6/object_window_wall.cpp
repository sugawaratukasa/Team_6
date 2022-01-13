//=============================================================================
// 窓付き壁 [object_window_wall.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(180.0f,500.0f,30.0f))	// サイズ
#define COLLISION_SIZE2	(D3DXVECTOR3(30.0f,500.0f,180.0f))	// サイズ
#define ROT_90			(D3DXToRadian(89.0f))				// 向き
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "object_window_wall.h"
#include "resource_manager.h"

//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CWindow_Wall::CWindow_Wall(PRIORITY Priority) : CObject(Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CWindow_Wall::~CWindow_Wall()
{
}
//=============================================================================
// 生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
CWindow_Wall * CWindow_Wall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CWindow_Wallのポインタ
	CWindow_Wall *pWindow_Wall = nullptr;

	// nullcheck
	if (pWindow_Wall == nullptr)
	{
		// メモリ確保
		pWindow_Wall = new CWindow_Wall;

		// !nullcheck
		if (pWindow_Wall != nullptr)
		{
			// 初期化処理
			pWindow_Wall->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pWindow_Wall;
}

//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CWindow_Wall::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_WINDOW_WALL);

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

	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CWindow_Wall::Uninit(void)
{
	// 終了処理
	CObject::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CWindow_Wall::Update(void)
{
	// 更新処理
	CObject::Update();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CWindow_Wall::Draw(void)
{
	// 描画処理
	CObject::Draw();
}