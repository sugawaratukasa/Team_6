//=============================================================================
//
// 電気室の鍵説明テクスチャ [electrical_key_guid_texture.cpp]
// Author : 二階堂　汰一
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "electrical_room_key_guid_texture.h"
#include "texture.h"
#include "manager.h"
#include "resource_manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CElectricalRoomKeyGuidTexture::CElectricalRoomKeyGuidTexture(PRIORITY Priority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CElectricalRoomKeyGuidTexture::~CElectricalRoomKeyGuidTexture()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CElectricalRoomKeyGuidTexture * CElectricalRoomKeyGuidTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CElectricalRoomKeyGuidTextureのポインタ
	CElectricalRoomKeyGuidTexture *pElectricalRoomKeyGuidTexture = nullptr;

	// nullcheck
	if (pElectricalRoomKeyGuidTexture == nullptr)
	{
		// メモリ確保
		pElectricalRoomKeyGuidTexture = new CElectricalRoomKeyGuidTexture;

		// !nullcheck
		if (pElectricalRoomKeyGuidTexture != nullptr)
		{
			// 初期化処理
			pElectricalRoomKeyGuidTexture->Init(pos, size);
		}
	}
	// ポインタを返す
	return pElectricalRoomKeyGuidTexture;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CElectricalRoomKeyGuidTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン2Dの初期化処理関数呼び出し
	CScene2D::Init(pos, size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_ELECTRICAL_KEY_GUID));
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CElectricalRoomKeyGuidTexture::Uninit(void)
{
	// シーン2Dの終了処理関数呼び出し
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CElectricalRoomKeyGuidTexture::Update(void)
{
	// シーン2Dの更新処理関数呼び出し
	CScene2D::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CElectricalRoomKeyGuidTexture::Draw(void)
{
	// シーン2Dの描画処理関数呼び出し
	CScene2D::Draw();
}
