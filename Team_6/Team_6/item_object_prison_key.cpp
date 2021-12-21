//=============================================================================
// PC室の鍵オブジェクト [item_object.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// インクルードファイル
// Author : Nikaido Taichi
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "item_object_prison_key.h"
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
CPrisonKeyObject::CPrisonKeyObject(PRIORITY Priority)
{
	m_pParticleEmitter = nullptr;
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CPrisonKeyObject::~CPrisonKeyObject()
{
}

//=============================================================================
// 生成処理関数
// Author : Nikaido Taichi
//=============================================================================
CPrisonKeyObject * CPrisonKeyObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CPrisonKeyObjectのポインタ
	CPrisonKeyObject *pPrisonKeyObject = nullptr;

	// nullcheck
	if (pPrisonKeyObject == nullptr)
	{
		// メモリ確保
		pPrisonKeyObject = new CPrisonKeyObject;

		// !nullcheck
		if (pPrisonKeyObject != nullptr)
		{
			// 初期化処理
			pPrisonKeyObject->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pPrisonKeyObject;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CPrisonKeyObject::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// タイプ設定
	SetType(ITEM_OBJECT_KEY_PRISON);
	// サイズ設定
	SetSize(SIZE);
	if (m_pParticleEmitter == nullptr)
	{
		m_pParticleEmitter = CParticle_Emitter::Create(pos, CParticle_Manager::TYPE_ITEM_GOLD);
	}
	// 初期化処理
	CItemObject::Init(pos, ZeroVector3);
	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPrisonKeyObject::Uninit(void)
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
void CPrisonKeyObject::Update(void)
{
	// 更新処理
	CItemObject::Update();
}

//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPrisonKeyObject::Draw(void)
{
	// 描画処理
	CItemObject::Draw();
}
