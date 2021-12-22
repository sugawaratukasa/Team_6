//=============================================================================
// ダクトの判定 [duct_collision.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "duct_collision.h"
#include "model_collision_box.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE (D3DXVECTOR3(100.0f, 550.0f, 100.0f))	// サイズ
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CDuct_Collision::CDuct_Collision(PRIORITY Priority) : CModel(Priority)
{
}
//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CDuct_Collision::~CDuct_Collision()
{
}
//=============================================================================
// 生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
CDuct_Collision * CDuct_Collision::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type)
{
	// CDuct_Collisionのポインタ
	CDuct_Collision *pDuctCollision = nullptr;

	// nullcheck
	if (pDuctCollision == nullptr)
	{
		// メモリ確保
		pDuctCollision = new CDuct_Collision;

		// !nullcheck
		if (pDuctCollision != nullptr)
		{
			// 種類代入
			pDuctCollision->m_Type = type;

			// 初期化処理
			pDuctCollision->Init(pos, rot);
		}
	}
	return nullptr;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CDuct_Collision::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 初期化
	CModel::Init(pos, rot);

	// サイズ
	SetSize(COLLISION_SIZE);
	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CDuct_Collision::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CDuct_Collision::Update(void)
{
	// 更新
	CModel::Update();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CDuct_Collision::Draw(void)
{
}
