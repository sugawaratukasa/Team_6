//=============================================================================
// マップオブジェクト [item_object_map.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// インクルードファイル
// Author : Nikaido Taichi
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "character.h"
#include "collision.h"
#include "game.h"
#include "player.h"
#include "item_object_map.h"
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
CMapObject::CMapObject(PRIORITY Priority) : CItemObject(Priority)
{
	m_pParticleEmitter = nullptr;
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CMapObject::~CMapObject()
{
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CMapObject * CMapObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CMapObjectのポインタ
	CMapObject *pMapObject = nullptr;

	// nullcheck
	if (pMapObject == nullptr)
	{
		// メモリ確保
		pMapObject = new CMapObject;

		// !nullcheck
		if (pMapObject != nullptr)
		{
			// 初期化処理
			pMapObject->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pMapObject;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CMapObject::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// タイプ設定
	SetType(ITEM_OBJECT_MAP);
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
void CMapObject::Uninit(void)
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
void CMapObject::Update(void)
{
	// 更新処理
	CItemObject::Update();
}
//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CMapObject::Draw(void)
{
	// 描画処理
	CItemObject::Draw();
}