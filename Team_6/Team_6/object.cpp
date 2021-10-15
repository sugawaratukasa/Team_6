//=============================================================================
// オブジェクト [object.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "character.h"
#include "collision.h"
#include "game.h"
#include "player.h"
#include "object.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define SIZE	(D3DXVECTOR3 (1500.0f,2000.0f,1500.0f))	// サイズ
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CObject::CObject(PRIORITY Priority) : CModel(Priority)
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CObject::~CObject()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CObject * CObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CObjectのポインタ
	CObject *pObject = nullptr;

	// nullcheck
	if (pObject == nullptr)
	{
		// メモリ確保
		pObject = new CObject;

		// !nullcheck
		if (pObject != nullptr)
		{
			// 初期化処理
			pObject->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pObject;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CObject::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// モデル情報取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデル情報取得
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_ROCK);

		// モデルの情報を渡す
		BindModel(model);
	}

	// サイズ設定
	SetSize(SIZE);

	// 箱生成
	//CModel_Box::Create(pos, rot, this);

	// 初期化処理
	CModel::Init(pos, ZeroVector3);

	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CObject::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CObject::Update(void)
{
	// 更新処理
	CModel::Update();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CObject::Draw(void)
{
	// 描画処理
	CModel::Draw();
}