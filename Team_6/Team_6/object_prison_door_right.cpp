//=============================================================================
// 牢屋壁クラス [object_prison_wall.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(0.0f,400.0f,50.0f))	// サイズ
#define COLLISION_SIZE2	(D3DXVECTOR3(50.0f,400.0f,0.0f))	// サイズ
#define ROT_90			(D3DXToRadian(89.0f))				// 向き
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "object_prison_door_right.h"
#include "resource_manager.h"

//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CPrison_Door_Right::CPrison_Door_Right(PRIORITY Priority) : CObject(Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CPrison_Door_Right::~CPrison_Door_Right()
{
}
//=============================================================================
// 生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
CPrison_Door_Right * CPrison_Door_Right::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CPrison_Door_Rightのポインタ
	CPrison_Door_Right *pPrison_Door_Right = nullptr;

	// nullcheck
	if (pPrison_Door_Right == nullptr)
	{
		// メモリ確保
		pPrison_Door_Right = new CPrison_Door_Right;

		// !nullcheck
		if (pPrison_Door_Right != nullptr)
		{
			// 初期化処理
			pPrison_Door_Right->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pPrison_Door_Right;
}

//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CPrison_Door_Right::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_PRISON_DOOR_RIGHT);

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


	//OBBの作成
	SetObb(CObb::Create(pos, rot, GetMesh()));

	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPrison_Door_Right::Uninit(void)
{
	// 終了処理
	CObject::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPrison_Door_Right::Update(void)
{
	// 更新処理
	CObject::Update();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPrison_Door_Right::Draw(void)
{
	// 描画処理
	CObject::Draw();
}