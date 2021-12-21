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
#include "object_switch_collision.h"
#include "object_switch.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(120.0f,450.0f,120.0f))	// サイズ
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CSwitch_Collision::CSwitch_Collision(PRIORITY Priority) : CDoor_Collision(Priority)
{
	m_pSwitch = nullptr;
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CSwitch_Collision::~CSwitch_Collision()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CSwitch_Collision * CSwitch_Collision::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CSwitch *pSwitch)
{
	// CSwitch_Collisionのポインタ
	CSwitch_Collision *pSwitch_Collision = nullptr;

	// nullcheck
	if (pSwitch_Collision == nullptr)
	{
		// メモリ確保
		pSwitch_Collision = new CSwitch_Collision;

		// !nullcheck
		if (pSwitch_Collision != nullptr)
		{
			// 初期化処理
			pSwitch_Collision->Init(pos, rot);

			// ポインタを代入
			pSwitch_Collision->m_pSwitch = pSwitch;
		}
	}
	// ポインタを返す
	return pSwitch_Collision;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CSwitch_Collision::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 初期化処理
	CDoor_Collision::Init(pos, rot);

	// タイプ設定
	SetType(TYPE_SWITCH);

	SetSize(COLLISION_SIZE);
	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CSwitch_Collision::Uninit(void)
{
	// 終了処理
	CDoor_Collision::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CSwitch_Collision::Update(void)
{
	// 更新処理
	CDoor_Collision::Update();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CSwitch_Collision::Draw(void)
{
}
//=============================================================================
// 独房のドアを開く
// Author : Sugawara Tsukasa
//=============================================================================
void CSwitch_Collision::Open(void)
{
	// !nullcheck
	if (m_pSwitch != nullptr)
	{
		// ボタンを押す処理
		m_pSwitch->Push();
	}
}
