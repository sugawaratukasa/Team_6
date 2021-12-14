//=============================================================================
// 倉庫の鍵オブジェクト [item_object_storage_key.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// インクルードファイル
// Author : Nikaido Taichi
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "item_object_storage_key.h"

//=============================================================================
// マクロ定義
// Author : Nikaido Taichi
//=============================================================================
#define SIZE (D3DXVECTOR3(100.0f,100.0f,100.0f))

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CStorageKeyObject::CStorageKeyObject(PRIORITY Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CStorageKeyObject::~CStorageKeyObject()
{
}

//=============================================================================
// 生成処理関数
// Author : Nikaido Taichi
//=============================================================================
CStorageKeyObject * CStorageKeyObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CPrisonKeyObjectのポインタ
	CStorageKeyObject *pStorageKeyObject = nullptr;

	// nullcheck
	if (pStorageKeyObject == nullptr)
	{
		// メモリ確保
		pStorageKeyObject = new CStorageKeyObject;

		// !nullcheck
		if (pStorageKeyObject != nullptr)
		{
			// 初期化処理
			pStorageKeyObject->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pStorageKeyObject;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CStorageKeyObject::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// タイプ設定
	SetType(ITEM_OBJECT_KEY_STORAGE);
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
void CStorageKeyObject::Uninit(void)
{
	// 終了処理
	CItemObject::Uninit();
}

//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CStorageKeyObject::Update(void)
{
	// 更新処理
	CItemObject::Update();
}

//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CStorageKeyObject::Draw(void)
{
	// 描画処理
	CItemObject::Draw();
}
