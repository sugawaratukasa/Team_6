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
#include "character.h"
#include "collision.h"
#include "game.h"
#include "player.h"
#include "item_object_pc_room_key.h"
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
CPCRoomKeyObject::CPCRoomKeyObject(PRIORITY Priority) : CItemObject(Priority)
{
	m_pParticleEmitter = nullptr;
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CPCRoomKeyObject::~CPCRoomKeyObject()
{
}

//=============================================================================
// 生成処理関数
// Author : Nikaido Taichi
//=============================================================================
CPCRoomKeyObject * CPCRoomKeyObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CPlayer1のポインタ
	CPCRoomKeyObject *pPCRoomKeyObject = nullptr;

	// nullcheck
	if (pPCRoomKeyObject == nullptr)
	{
		// メモリ確保
		pPCRoomKeyObject = new CPCRoomKeyObject;

		// !nullcheck
		if (pPCRoomKeyObject != nullptr)
		{
			// 初期化処理
			pPCRoomKeyObject->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pPCRoomKeyObject;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CPCRoomKeyObject::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// サイズ設定
	SetSize(SIZE);
	// タイプ設定
	SetType(ITEM_OBJECT_KEY_PC_ROOM);
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
void CPCRoomKeyObject::Uninit(void)
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
void CPCRoomKeyObject::Update(void)
{
	// 更新処理
	CItemObject::Update();
}
//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPCRoomKeyObject::Draw(void)
{
	// 描画処理
	CItemObject::Draw();
}