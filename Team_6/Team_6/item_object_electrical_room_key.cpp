//=============================================================================
// 電気室の鍵オブジェクト [item_object_electrical_room_key.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// インクルードファイル
// Author : Nikaido Taichi
//=============================================================================
#include "item_object_electrical_room_key.h"
#include "manager.h"
#include "resource_manager.h"
#include "particle_manager.h"
#include "particle_emitter.h"

//=============================================================================
// マクロ定義
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CElectricalRoomKeyObject::CElectricalRoomKeyObject(PRIORITY Priority)
{
	m_pParticleEmitter = nullptr;
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CElectricalRoomKeyObject::~CElectricalRoomKeyObject()
{
}

//=============================================================================
// 生成処理関数
// Author : Nikaido Taichi
//=============================================================================
CElectricalRoomKeyObject * CElectricalRoomKeyObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CElectricalRoomKeyObjectのポインタ
	CElectricalRoomKeyObject *pElectricalRoomKeyObject = nullptr;

	// nullcheck
	if (pElectricalRoomKeyObject == nullptr)
	{
		// メモリ確保
		pElectricalRoomKeyObject = new CElectricalRoomKeyObject;

		// !nullcheck
		if (pElectricalRoomKeyObject != nullptr)
		{
			// 初期化処理
			pElectricalRoomKeyObject->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pElectricalRoomKeyObject;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CElectricalRoomKeyObject::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// タイプ設定
	SetType(ITEM_OBJECT_KEY_ELECTRICAL_ROOM);
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
void CElectricalRoomKeyObject::Uninit(void)
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
void CElectricalRoomKeyObject::Update(void)
{
	// 更新処理
	CItemObject::Update();
}

//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CElectricalRoomKeyObject::Draw(void)
{
	// 描画処理
	CItemObject::Draw();
}
