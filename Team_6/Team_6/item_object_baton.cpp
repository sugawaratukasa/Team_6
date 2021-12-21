//=============================================================================
// 警棒オブジェクト [item_object_baton.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// インクルードファイル
// Author : Nikaido Taichi
//=============================================================================
#include "item_object_baton.h"
#include "manager.h"
#include "resource_manager.h"
#include "particle_manager.h"
#include "particle_emitter.h"

//=============================================================================
// マクロ定義
// Author : Nikaido Taichi
//=============================================================================
#define SIZE (D3DXVECTOR3(100.0f,100.0f,100.0f))

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CBatonObject::CBatonObject(PRIORITY Priority)
{
	m_pParticleEmitter = nullptr;
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CBatonObject::~CBatonObject()
{
}

//=============================================================================
// 生成処理関数
// Author : Nikaido Taichi
//=============================================================================
CBatonObject * CBatonObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CJailerKeyObjectのポインタ
	CBatonObject *pJailerKeyObject = nullptr;

	// nullcheck
	if (pJailerKeyObject == nullptr)
	{
		// メモリ確保
		pJailerKeyObject = new CBatonObject;

		// !nullcheck
		if (pJailerKeyObject != nullptr)
		{
			// 初期化処理
			pJailerKeyObject->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pJailerKeyObject;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CBatonObject::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// タイプ設定
	SetType(ITEM_OBJECT_BATON);
	// サイズ設定
	SetSize(SIZE);
	if (m_pParticleEmitter == nullptr)
	{
		m_pParticleEmitter = CParticle_Emitter::Create(pos, CParticle_Manager::TYPE_ITEM_SILVER);
	}
	// 初期化処理
	CItemObject::Init(pos, ZeroVector3);
	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CBatonObject::Uninit(void)
{
	if (m_pParticleEmitter != nullptr)
	{
		m_pParticleEmitter->Uninit();
	}
	// 終了処理
	CItemObject::Uninit();
}

//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CBatonObject::Update(void)
{
	// 更新処理
	CItemObject::Update();
}

//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CBatonObject::Draw(void)
{
	// 描画処理
	CItemObject::Draw();
}
