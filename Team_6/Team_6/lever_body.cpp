//=============================================================================
// レバーボディ [lever_body.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "lever_body.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CLever_Body::CLever_Body(PRIORITY Priority) : CModel(Priority)
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CLever_Body::~CLever_Body()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CLever_Body * CLever_Body::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CLever_Bodyのポインタ
	CLever_Body *pLever_Body = nullptr;

	// nullcheck
	if (pLever_Body == nullptr)
	{
		// メモリ確保
		pLever_Body = new CLever_Body;

		// !nullcheck
		if (pLever_Body != nullptr)
		{
			// 初期化処理
			pLever_Body->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pLever_Body;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CLever_Body::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 初期化処理
	CModel::Init(pos, rot);

	// モデル情報取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデル情報取得
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_LEVER_BODY);

		// モデルの情報を渡す
		BindModel(model);
	}
	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CLever_Body::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CLever_Body::Update(void)
{
	// 更新処理
	CModel::Update();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CLever_Body::Draw(void)
{
	// 描画処理
	CModel::Draw();
}