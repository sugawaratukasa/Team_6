//=============================================================================
// ドアの壁の当たり判定用クラス [door_wall_collision.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(20.0f,550.0f,20.0f))	// サイズ
#define COLLISION_SIZE2	(D3DXVECTOR3(20.0f,550.0f,20.0f))	// サイズ
#define ROT_90			(D3DXToRadian(89.0f))				// 向き
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "door_wall_collision.h"
#include "resource_manager.h"

//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CDoorWallCollision::CDoorWallCollision(PRIORITY Priority) : CObject(Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CDoorWallCollision::~CDoorWallCollision()
{
}
//=============================================================================
// 生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
CDoorWallCollision * CDoorWallCollision::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CWallのポインタ
	CDoorWallCollision *pWall = nullptr;

	// nullcheck
	if (pWall == nullptr)
	{
		// メモリ確保
		pWall = new CDoorWallCollision;

		// !nullcheck
		if (pWall != nullptr)
		{
			// 初期化処理
			pWall->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pWall;
}

//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CDoorWallCollision::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// サイズ
	SetSize(COLLISION_SIZE);

	// 初期化処理
	CObject::Init(pos, rot);

	// 90以上の場合
	if (rot.y >= ROT_90)
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
void CDoorWallCollision::Uninit(void)
{
	// 終了処理
	CObject::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CDoorWallCollision::Update(void)
{
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CDoorWallCollision::Draw(void)
{
}