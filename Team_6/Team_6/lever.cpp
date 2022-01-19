//=============================================================================
// 牢屋の判定 [prison_door_collision.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "lever.h"
#include "lever_body.h"
#include "lever_handle.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(80.0f,450.0f,80.0f))			// サイズ
#define ROT_180			(D3DXToRadian(179.0f))						// 向き
#define POS				(D3DXVECTOR3(pos.x,pos.y,pos.z + 100))		// 位置
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CLever::CLever(PRIORITY Priority) : CDoor_Collision(Priority)
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CLever::~CLever()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CLever * CLever::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CLeverのポインタ
	CLever *pLever = nullptr;

	// nullcheck
	if (pLever == nullptr)
	{
		// メモリ確保
		pLever = new CLever;

		// !nullcheck
		if (pLever != nullptr)
		{
			// 初期化処理
			pLever->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pLever;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CLever::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 初期化処理
	CDoor_Collision::Init(pos, rot);

	// レバー生成処理
	LeverCrate(pos, rot);

	// サイズ設定
	SetSize(COLLISION_SIZE);

	// タイプ設定
	SetType(TYPE_LEVER);

	// 向きが180°以上の場合
	if (rot.y > ROT_180)
	{
		// 位置設定
		SetPos(POS);
	}
	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CLever::Uninit(void)
{
	// 終了処理
	CDoor_Collision::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CLever::Update(void)
{
	// 更新処理
	CDoor_Collision::Update();

	// 下がっている取得
	bool bDown = m_pLever_Handle->GetbDown();

	// falseの場合
	if (bDown == false)
	{
		// falseに
		m_bDownLever = false;
	}
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CLever::Draw(void)
{
}
//=============================================================================
// レバー生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CLever::LeverCrate(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// レバーハンドル生成
	m_pLever_Handle = CLever_Handle::Create(pos, rot);

	// レバーハンドルボディ生成
	CLever_Body::Create(pos, rot);
}
//=============================================================================
// 開く処理処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CLever::Open(int nPlayer)
{
	// レバーが下がっている状態に
	m_bDownLever = true;

	// trueに
	m_pLever_Handle->SetDown(true);
}
//=============================================================================
// ドアが開いた事を設定する処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CLever::SetOpen(bool bOpen)
{
	m_pLever_Handle->SetOpen(bOpen);
}
