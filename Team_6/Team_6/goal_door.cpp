//=============================================================================
// ゴールの扉 [goal_door.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "goal_door.h"
#include "object.h"
#include "manager.h"
#include "resource_manager.h"
#include "jailer_door_collision.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(180.0f,330.0f,25.0f))	// サイズ
#define COLLISION_SIZE2	(D3DXVECTOR3(25.0f,330.0f,180.0f))	// サイズ
#define ROT_90			(D3DXToRadian(89.0f))				// 向き
#define MOVE_Y			(10.0f)								// 移動
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CGoal_Door::CGoal_Door(PRIORITY Priority)
{
	m_pLever1 = nullptr;
	m_pLever2 = nullptr;
	m_InitPos = ZeroVector3;
}
//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================

CGoal_Door::~CGoal_Door()
{
}
//=============================================================================
// 生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
CGoal_Door * CGoal_Door::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CLever *pLever1, CLever *pLever2)
{
	// CGoal_Doorのポインタ
	CGoal_Door *pGoal_Door = nullptr;

	// nullcheck
	if (pGoal_Door == nullptr)
	{
		// メモリ確保
		pGoal_Door = new CGoal_Door;

		// !nullcheck
		if (pGoal_Door != nullptr)
		{
			// CLeverのポインタ代入
			pGoal_Door->m_pLever1 = pLever1;

			// CLeverのポインタ代入
			pGoal_Door->m_pLever2 = pLever2;

			// 初期化処理
			pGoal_Door->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pGoal_Door;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CGoal_Door::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_GOAL_DOOR);

		// モデルの情報を渡す
		BindModel(model);
	}

	// 90以上の場合
	if (rot.y >= ROT_90)
	{
		// サイズ
		SetSize(COLLISION_SIZE2);
	}

	//OBBの作成
	SetObb(CObb::Create(pos, rot, GetMesh()));

	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CGoal_Door::Uninit(void)
{
	// ドアの終了処理関数呼び出し
	CDoor::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CGoal_Door::Update(void)
{
	// ドアの更新処理関数呼び出し
	CDoor::Update();

	// 下がっているか取得
	bool bDown1 = m_pLever1->GetbDownLever();
	bool bDown2 = m_pLever2->GetbDownLever();

	// レバーが両方下がっているか
	if (bDown1 == true && bDown2 == true)
	{
		// 開く
		Open();
	}
	// レバーとも下がっていない場合
	else
	{
		// 開く
		Close();
	}
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CGoal_Door::Draw(void)
{
	// ドアの描画処理関数呼び出し
	CDoor::Draw();
}
//=============================================================================
// 開く処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CGoal_Door::Open(void)
{
	// 位置
	D3DXVECTOR3 pos = GetPos();

	// 位置
	if (pos.y >= m_InitPos.y - COLLISION_SIZE.y)
	{
		// 移動
		pos.y -= MOVE_Y;

		// 位置設定
		SetPos(pos);
	}
}
//=============================================================================
// 閉じる処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CGoal_Door::Close(void)
{
	// 位置
	D3DXVECTOR3 pos = GetPos();
	// 位置
	if (pos.y <= m_InitPos.y)
	{
		// 移動
		pos.y += MOVE_Y;

		// 位置設定
		SetPos(pos);
	}
}
