//=============================================================================
// 木の机クラス [object_wood_desk.cpp]
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
#include "object_wood_desk.h"
#include "resource_manager.h"

//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CWood_Desk::CWood_Desk(PRIORITY Priority) : CObject(Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CWood_Desk::~CWood_Desk()
{
}
//=============================================================================
// 生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
CWood_Desk * CWood_Desk::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CWood_Deskのポインタ
	CWood_Desk *pWood_Desk = nullptr;

	// nullcheck
	if (pWood_Desk == nullptr)
	{
		// メモリ確保
		pWood_Desk = new CWood_Desk;

		// !nullcheck
		if (pWood_Desk != nullptr)
		{
			// 初期化処理
			pWood_Desk->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pWood_Desk;
}

//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CWood_Desk::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_WOOD_DESK);

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
void CWood_Desk::Uninit(void)
{
	// 終了処理
	CObject::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CWood_Desk::Update(void)
{
	// 更新処理
	CObject::Update();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CWood_Desk::Draw(void)
{
	// 描画処理
	CObject::Draw();
}