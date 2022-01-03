//=============================================================================
// オブジェクト [object.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "character.h"
#include "collision.h"
#include "game.h"
#include "player.h"
#include "object.h"
#include "model_collision_box.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CObject::CObject(PRIORITY Priority) : CModel(Priority)
{
	m_Type = TYPE_NONE;
	m_pObb = nullptr;
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CObject::~CObject()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CObject * CObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CObjectのポインタ
	CObject *pObject = nullptr;

	// nullcheck
	if (pObject == nullptr)
	{
		// メモリ確保
		pObject = new CObject;

		// !nullcheck
		if (pObject != nullptr)
		{
			// 初期化処理
			pObject->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pObject;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CObject::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 初期化処理
	CModel::Init(pos, rot);

	CModelCollisionBox::Create(pos, rot, this);
	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CObject::Uninit(void)
{
	if (m_pObb != nullptr)
	{
		//OBBの終了
		m_pObb->Uninit();
	}
	
	// 終了処理
	CModel::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CObject::Update(void)
{
	// 更新処理
	CModel::Update();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CObject::Draw(void)
{
	// 描画処理
	CModel::Draw();
}