//=============================================================================
// 金属の机クラス [object_metal_desk.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(100.0f,120.0f,100.0f))	// サイズ
#define COLLISION_SIZE2	(D3DXVECTOR3(100.0f,120.0f, 100.0f))	// サイズ
#define ROT_90			(D3DXToRadian(89.0f))				// 向き
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "object_metal_desk.h"
#include "resource_manager.h"

//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CMetal_Desk::CMetal_Desk(PRIORITY Priority) : CObject(Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CMetal_Desk::~CMetal_Desk()
{
}
//=============================================================================
// 生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
CMetal_Desk * CMetal_Desk::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CMetal_Deskのポインタ
	CMetal_Desk *pMetal_Desk = nullptr;

	// nullcheck
	if (pMetal_Desk == nullptr)
	{
		// メモリ確保
		pMetal_Desk = new CMetal_Desk;

		// !nullcheck
		if (pMetal_Desk != nullptr)
		{
			// 初期化処理
			pMetal_Desk->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pMetal_Desk;
}

//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CMetal_Desk::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_METAL_DESK);

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
void CMetal_Desk::Uninit(void)
{
	// 終了処理
	CObject::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CMetal_Desk::Update(void)
{
	// 更新処理
	CObject::Update();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CMetal_Desk::Draw(void)
{
	// 描画処理
	CObject::Draw();
}