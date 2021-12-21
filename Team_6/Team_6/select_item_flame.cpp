//=============================================================================
//
// 選択してるアイテムの枠 [select_item_flame.cpp]
// Author : 二階堂　汰一
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "select_item_flame.h"
#include "texture.h"
#include "manager.h"
#include "resource_manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CSelectItemFlame::CSelectItemFlame(PRIORITY Priority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CSelectItemFlame::~CSelectItemFlame()
{
}

//=============================================================================
// 生成処理関数
//=============================================================================
CSelectItemFlame * CSelectItemFlame::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CSelectItemFlameのポインタ
	CSelectItemFlame *pSelectItemFlame = nullptr;

	// nullcheck
	if (pSelectItemFlame == nullptr)
	{
		// メモリ確保
		pSelectItemFlame = new CSelectItemFlame;

		// !nullcheck
		if (pSelectItemFlame != nullptr)
		{
			// 初期化処理
			pSelectItemFlame->Init(pos, size);
		}
	}
	// ポインタを返す
	return pSelectItemFlame;
}

//=============================================================================
// 初期化処理関数
//=============================================================================
HRESULT CSelectItemFlame::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン2Dの初期化処理関数
	CScene2D::Init(pos, size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_SELECT_ITEM_FLAME));
	return S_OK;
}

//=============================================================================
// 終了処理関数
//=============================================================================
void CSelectItemFlame::Uninit(void)
{
	// シーン2Dの終了処理関数
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理関数
//=============================================================================
void CSelectItemFlame::Update(void)
{
	// シーン2Dの更新処理関数
	CScene2D::Update();
}

//=============================================================================
// 描画処理関数
//=============================================================================
void CSelectItemFlame::Draw(void)
{
	// シーン2Dの描画処理関数
	CScene2D::Draw();
}
