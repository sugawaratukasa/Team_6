//=============================================================================
// スイッチ判定クラス [object_switch_collision.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define POS				(D3DXVECTOR3(pos.x,pos.y,pos.z + 200.0f))	// 位置
#define POS2			(D3DXVECTOR3(pos.x + 200.0f,pos.y,pos.z))	// 位置
#define COLLISION_SIZE	(D3DXVECTOR3(150.0f,450.0f,50.0f))			// サイズ
#define COLLISION_SIZE2	(D3DXVECTOR3(50.0f,450.0f,150.0f))			// サイズ
#define ROT_180			(D3DXToRadian(179.0f))						// 向き
#define ROT_270			(D3DXToRadian(269.0f))						// 向き
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "object_switch_collision.h"
#include "resource_manager.h"

//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CSwitch_Collision::CSwitch_Collision(PRIORITY Priority) : CObject(Priority)
{
	m_pSwitch = nullptr;
}

//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CSwitch_Collision::~CSwitch_Collision()
{
}
//=============================================================================
// 生成処理関数
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

			// CSwitchのポインタ代入
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
	CObject::Init(pos, rot);

	// 180以上の場合
	if (rot.y >= ROT_180 && rot.y <= ROT_270)
	{
		// 位置設定
		SetPos(POS);

		// サイズ
		SetSize(COLLISION_SIZE);
	}

	// 270以上の場合
	if (rot.y >= ROT_270)
	{
		// 位置設定
		SetPos(POS2);

		// サイズ
		SetSize(COLLISION_SIZE2);
	}

	// 種類設定
	SetType(TYPE_SWITCH);

	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CSwitch_Collision::Uninit(void)
{
	// 終了処理
	CObject::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CSwitch_Collision::Update(void)
{
	// 更新処理
	CObject::Update();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CSwitch_Collision::Draw(void)
{
}
//=============================================================================
// ボタンを押す処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CSwitch_Collision::Push(void)
{
	// ボタンを押す処理
	m_pSwitch->Push();
}