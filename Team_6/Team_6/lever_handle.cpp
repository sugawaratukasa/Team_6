//=============================================================================
// レバーハンドル [lever_handle.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "lever_handle.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CLever_Handle::CLever_Handle(PRIORITY Priority) : CModel(Priority)
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CLever_Handle::~CLever_Handle()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CLever_Handle * CLever_Handle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CLever_Handleのポインタ
	CLever_Handle *pLever_Handle = nullptr;

	// nullcheck
	if (pLever_Handle == nullptr)
	{
		// メモリ確保
		pLever_Handle = new CLever_Handle;

		// !nullcheck
		if (pLever_Handle != nullptr)
		{
			// 初期化処理
			pLever_Handle->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pLever_Handle;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CLever_Handle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 初期化処理
	CModel::Init(pos, rot);

	// モデル情報取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデル情報取得
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_LEVER_HANDLE);

		// モデルの情報を渡す
		BindModel(model);
	}
	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CLever_Handle::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CLever_Handle::Update(void)
{
	// 更新処理
	CModel::Update();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CLever_Handle::Draw(void)
{
	// 描画処理
	CModel::Draw();
}