//=============================================================================
// 看守室の鍵オブジェクト [item_object_jailer_room_key.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// インクルードファイル
// Author : Nikaido Taichi
//=============================================================================
#include "item_object_jailer_room_key.h"
#include "manager.h"
#include "resource_manager.h"

//=============================================================================
// マクロ定義
// Author : Nikaido Taichi
//=============================================================================
#define SIZE (D3DXVECTOR3(100.0f,100.0f,100.0f))

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CJailerKeyObject::CJailerKeyObject(PRIORITY Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CJailerKeyObject::~CJailerKeyObject()
{
}

//=============================================================================
// 生成処理関数
// Author : Nikaido Taichi
//=============================================================================
CJailerKeyObject * CJailerKeyObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CJailerKeyObjectのポインタ
	CJailerKeyObject *pJailerKeyObject = nullptr;

	// nullcheck
	if (pJailerKeyObject == nullptr)
	{
		// メモリ確保
		pJailerKeyObject = new CJailerKeyObject;

		// !nullcheck
		if (pJailerKeyObject != nullptr)
		{
			// 初期化処理
			pJailerKeyObject->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pJailerKeyObject;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CJailerKeyObject::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// モデル情報取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデル情報取得
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_KEY_OBJECT);

		// モデルの情報を渡す
		BindModel(model);
	}
	// タイプ設定
	SetType(ITEM_OBJECT_KEY_JAILER_ROOM);
	// サイズ設定
	SetSize(SIZE);

	// 初期化処理
	CItemObject::Init(pos, ZeroVector3);
	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CJailerKeyObject::Uninit(void)
{
	// 終了処理
	CItemObject::Uninit();
}

//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CJailerKeyObject::Update(void)
{
	// 更新処理
	CItemObject::Update();
}

//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CJailerKeyObject::Draw(void)
{
	// 描画処理
	CItemObject::Draw();
}
