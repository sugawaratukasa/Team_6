//=============================================================================
//
// 制御室の鍵説明テクスチャ [control_room_key_guid_texture.cpp]
// Author : 二階堂　汰一
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "scene_2d.h"
#include "control_room_key_guid_texture.h"

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CControlRoomKeyGuidTexture::CControlRoomKeyGuidTexture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CControlRoomKeyGuidTexture::~CControlRoomKeyGuidTexture()
{
}

//=============================================================================
// 生成処理関数
// Author : Nikaido Taichi
//=============================================================================
CControlRoomKeyGuidTexture * CControlRoomKeyGuidTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CControlRoomKeyGuidTextureのポインタ
	CControlRoomKeyGuidTexture *pControlRoomKeyGuidTexture = nullptr;

	// nullcheck
	if (pControlRoomKeyGuidTexture == nullptr)
	{
		// メモリ確保
		pControlRoomKeyGuidTexture = new CControlRoomKeyGuidTexture;

		// !nullcheck
		if (pControlRoomKeyGuidTexture != nullptr)
		{
			// 初期化処理
			pControlRoomKeyGuidTexture->Init(pos, size);
		}
	}
	// ポインタを返す
	return pControlRoomKeyGuidTexture;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CControlRoomKeyGuidTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン2Dの初期化処理関数呼び出し
	CScene2D::Init(pos, size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_CONTROL_KEY_GUID));
	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CControlRoomKeyGuidTexture::Uninit(void)
{
	// シーン2Dの終了処理関数呼び出し
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CControlRoomKeyGuidTexture::Update(void)
{
	// シーン2Dの更新処理関数呼び出し
	CScene2D::Update();
}

//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CControlRoomKeyGuidTexture::Draw(void)
{
	// シーン2Dの描画処理関数呼び出し
	CScene2D::Draw();
}
