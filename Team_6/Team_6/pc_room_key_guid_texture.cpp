//=============================================================================
//
// PC室の鍵説明テクスチャ [number.cpp]
// Author : 二階堂　汰一
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "pc_room_key_guid_texture.h"
#include "texture.h"
#include "manager.h"
#include "resource_manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CPCRoomKeyGuidTexture::CPCRoomKeyGuidTexture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CPCRoomKeyGuidTexture::~CPCRoomKeyGuidTexture()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CPCRoomKeyGuidTexture * CPCRoomKeyGuidTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CPCRoomKeyGuidTextureのポインタ
	CPCRoomKeyGuidTexture *pPCRoomKeyGuidTexture = nullptr;

	// nullcheck
	if (pPCRoomKeyGuidTexture == nullptr)
	{
		// メモリ確保
		pPCRoomKeyGuidTexture = new CPCRoomKeyGuidTexture;

		// !nullcheck
		if (pPCRoomKeyGuidTexture != nullptr)
		{
			// 初期化処理
			pPCRoomKeyGuidTexture->Init(pos, size);
		}
	}
	// ポインタを返す
	return pPCRoomKeyGuidTexture;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CPCRoomKeyGuidTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン2Dの初期化処理関数呼び出し
	CScene2D::Init(pos, size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PC_ROOM_KEY_GUID));
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CPCRoomKeyGuidTexture::Uninit(void)
{
	// シーン2Dの終了処理関数呼び出し
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CPCRoomKeyGuidTexture::Update(void)
{
	// シーン2Dの更新処理関数呼び出し
	CScene2D::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CPCRoomKeyGuidTexture::Draw(void)
{
	// シーン2Dの描画処理関数呼び出し
	CScene2D::Draw();
}
