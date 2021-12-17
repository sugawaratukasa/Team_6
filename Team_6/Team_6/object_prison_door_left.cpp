//=============================================================================
// 牢屋の扉 [object_prison_door_right.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "object_prison_door_left.h"
#include "object.h"
#include "manager.h"
#include "resource_manager.h"
#include "prison_door_collision.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(180.0f,450.0f,50.0f))	// サイズ
#define COLLISION_SIZE2	(D3DXVECTOR3(50.0f,450.0f,180.0f))	// サイズ
#define ROT_90			(D3DXToRadian(89.0f))				// 向き
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CPrison_Door_Left::CPrison_Door_Left(PRIORITY Priority)
{
}
//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CPrison_Door_Left::~CPrison_Door_Left()
{
}
//=============================================================================
// 生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
CPrison_Door_Left * CPrison_Door_Left::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CPrison_Door_Leftのポインタ
	CPrison_Door_Left *pPrison_Door = nullptr;

	// nullcheck
	if (pPrison_Door == nullptr)
	{
		// メモリ確保
		pPrison_Door = new CPrison_Door_Left;

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
HRESULT CPrison_Door_Left::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_PRISON_DOOR_LEFT);

		// モデルの情報を渡す
		BindModel(model);
	}

	// 90以上の場合
	if (rot.y >= ROT_90)
	{
		// サイズ
		SetSize(COLLISION_SIZE2);
	}

	// 判定用オブジェクト生成
	CPrison_Door_Collision::Create(pos, rot, this);
	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPrison_Door_Left::Uninit(void)
{
	// ドアの終了処理関数呼び出し
	CDoor::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPrison_Door_Left::Update(void)
{
	// ドアの更新処理関数呼び出し
	CDoor::Update();

	// 開錠状態
	Open();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPrison_Door_Left::Draw(void)
{
	// ドアの描画処理関数呼び出し
	CDoor::Draw();
}
