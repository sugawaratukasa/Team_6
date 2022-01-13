//=============================================================================
// 木の椅子クラス [object_wood_chair.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================

#define COLLISION_SIZE	(D3DXVECTOR3(70.0f,70.0f,70.0f))	// サイズ
#define COLLISION_SIZE2	(D3DXVECTOR3(70.0f,70.0f,70.0f))	// サイズ
#define ROT_90			(D3DXToRadian(89.0f))				// 向き
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "object_wood_chair.h"
#include "resource_manager.h"

//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CWood_Chair::CWood_Chair(PRIORITY Priority) : CObject(Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CWood_Chair::~CWood_Chair()
{
}
//=============================================================================
// 生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
CWood_Chair * CWood_Chair::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CWood_Chairのポインタ
	CWood_Chair *pWood_Chair = nullptr;

	// nullcheck
	if (pWood_Chair == nullptr)
	{
		// メモリ確保
		pWood_Chair = new CWood_Chair;

		// !nullcheck
		if (pWood_Chair != nullptr)
		{
			// 初期化処理
			pWood_Chair->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pWood_Chair;
}

//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CWood_Chair::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_WOOD_CHAIR);

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
void CWood_Chair::Uninit(void)
{
	// 終了処理
	CObject::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CWood_Chair::Update(void)
{
	// 更新処理
	CObject::Update();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CWood_Chair::Draw(void)
{
	// 描画処理
	CObject::Draw();
}