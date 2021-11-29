//=============================================================================
// 看守の扉 [guards_door.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "guards_door.h"
#include "object.h"
#include "manager.h"
#include "resource_manager.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(330.0f,550.0f,50.0f))	// サイズ
#define COLLISION_SIZE2	(D3DXVECTOR3(50.0f,550.0f,330.0f))	// サイズ
#define ROT_90			(D3DXToRadian(89.0f))				// 向き
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CGuards_Door::CGuards_Door(PRIORITY Priority)
{
}
//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CGuards_Door::~CGuards_Door()
{
}
//=============================================================================
// 生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
CGuards_Door * CGuards_Door::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CGuards_Doorのポインタ
	CGuards_Door *pPrison_Door = nullptr;

	// nullcheck
	if (pPrison_Door == nullptr)
	{
		// メモリ確保
		pPrison_Door = new CGuards_Door;

		// !nullcheck
		if (pPrison_Door != nullptr)
		{
			// 初期化処理
			pPrison_Door->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pPrison_Door;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CGuards_Door::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ドアの初期化処理関数呼び出し
	CDoor::Init(pos, rot);

	// サイズ
	SetSize(COLLISION_SIZE);

	// モデル情報取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデル情報取得
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_DOOR);

		// モデルの情報を渡す
		BindModel(model);
	}

	// 90以上の場合
	if (rot.y >= ROT_90)
	{
		// サイズ
		SetSize(COLLISION_SIZE2);
	}
	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CGuards_Door::Uninit(void)
{
	// ドアの終了処理関数呼び出し
	CDoor::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CGuards_Door::Update(void)
{
	// ドアの更新処理関数呼び出し
	CDoor::Update();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CGuards_Door::Draw(void)
{
	// ドアの描画処理関数呼び出し
	CDoor::Draw();
}
