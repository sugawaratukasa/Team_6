//=============================================================================
// 制御室の鍵オブジェクト [item_object_control_room_key.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// インクルードファイル
// Author : Nikaido Taichi
//=============================================================================
#include "item_object_control_room_key.h"
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
CControlRoomKeyObject::CControlRoomKeyObject(PRIORITY Priority)
{
	m_pParticleEmitter = nullptr;
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CControlRoomKeyObject::~CControlRoomKeyObject()
{
}

//=============================================================================
// 生成処理関数
// Author : Nikaido Taichi
//=============================================================================
CControlRoomKeyObject * CControlRoomKeyObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CControlRoomKeyObjectのポインタ
	CControlRoomKeyObject *pControlRoomKeyObject = nullptr;

	// nullcheck
	if (pControlRoomKeyObject == nullptr)
	{
		// メモリ確保
		pControlRoomKeyObject = new CControlRoomKeyObject;

		// !nullcheck
		if (pControlRoomKeyObject != nullptr)
		{
			// 初期化処理
			pControlRoomKeyObject->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pControlRoomKeyObject;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CControlRoomKeyObject::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// タイプ設定
	SetType(ITEM_OBJECT_KEY_CONTOROL_ROOM);
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
void CControlRoomKeyObject::Uninit(void)
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
void CControlRoomKeyObject::Update(void)
{
	// 更新処理
	CItemObject::Update();
}

//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CControlRoomKeyObject::Draw(void)
{
	// 描画処理
	CItemObject::Draw();
}
