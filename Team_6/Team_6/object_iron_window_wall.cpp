//=============================================================================
// 開かないドアの壁 [object_keepout_wall.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(180.0f,500.0f,25.0f))	// サイズ
#define COLLISION_SIZE2	(D3DXVECTOR3(25.0f,500.0f,180.0f))	// サイズ
#define ROT_90			(D3DXToRadian(89.0f))				// 向き
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "object_iron_window_wall.h"
#include "resource_manager.h"

//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CIronWindow_Wall::CIronWindow_Wall(PRIORITY Priority) : CObject(Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CIronWindow_Wall::~CIronWindow_Wall()
{
}
//=============================================================================
// 生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
CIronWindow_Wall * CIronWindow_Wall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CIronWindow_Wallのポインタ
	CIronWindow_Wall *pIronWindow_Wall = nullptr;

	// nullcheck
	if (pIronWindow_Wall == nullptr)
	{
		// メモリ確保
		pIronWindow_Wall = new CIronWindow_Wall;

		// !nullcheck
		if (pIronWindow_Wall != nullptr)
		{
			// 初期化処理
			pIronWindow_Wall->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pIronWindow_Wall;
}

//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CIronWindow_Wall::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_IRON_WINDOW_WALL);

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

	//OBBの作成
	//SetObb(CObb::Create(pos, rot, GetMesh()));

	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CIronWindow_Wall::Uninit(void)
{
	// 終了処理
	CObject::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CIronWindow_Wall::Update(void)
{
	// 更新処理
	CObject::Update();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CIronWindow_Wall::Draw(void)
{
	// 描画処理
	CObject::Draw();
}