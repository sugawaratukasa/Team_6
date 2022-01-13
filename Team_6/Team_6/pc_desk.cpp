//=============================================================================
// PCの机 [pc_desk.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================

#define COLLISION_SIZE	(D3DXVECTOR3(180.0f,400.0f,90.0f))	// サイズ
#define COLLISION_SIZE2	(D3DXVECTOR3(90.0f,400.0f,180.0f))	// サイズ
#define ROT_90			(D3DXToRadian(89.0f))				// 向き
#define ROT_180			(D3DXToRadian(179.0f))				// 向き
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "pc_desk.h"
#include "resource_manager.h"

//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CPC_Desk::CPC_Desk(PRIORITY Priority) : CObject(Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CPC_Desk::~CPC_Desk()
{
}
//=============================================================================
// 生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
CPC_Desk * CPC_Desk::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CPC_Deskのポインタ
	CPC_Desk *pPC_Desk = nullptr;

	// nullcheck
	if (pPC_Desk == nullptr)
	{
		// メモリ確保
		pPC_Desk = new CPC_Desk;

		// !nullcheck
		if (pPC_Desk != nullptr)
		{
			// 初期化処理
			pPC_Desk->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pPC_Desk;
}

//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CPC_Desk::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_PC_DESK);

		// モデルの情報を渡す
		BindModel(model);
	}

	// 90以上の場合
	if (rot.y >= ROT_90 && rot.y < ROT_180)
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
void CPC_Desk::Uninit(void)
{
	// 終了処理
	CObject::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPC_Desk::Update(void)
{
	// 更新処理
	CObject::Update();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPC_Desk::Draw(void)
{
	// 描画処理
	CObject::Draw();
}