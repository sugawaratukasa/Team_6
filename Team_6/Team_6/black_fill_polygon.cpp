//=============================================================================
// 床 [enemy_attack_point_polygon.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"
#include "collision.h"
#include "player.h"
#include "game.h"
#include "black_fill_polygon.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define COL (D3DCOLOR_RGBA(255, 255, 255, 255))	// 色
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CBlack_Fill_Polygon::CBlack_Fill_Polygon(PRIORITY Priority) : CScene3D(Priority)
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CBlack_Fill_Polygon::~CBlack_Fill_Polygon()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CBlack_Fill_Polygon * CBlack_Fill_Polygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CBlack_Fill_Polygonのポインタ
	CBlack_Fill_Polygon *pBlack_Fill_Polygon = nullptr;

	// nullcheck
	if (pBlack_Fill_Polygon == nullptr)
	{
		// メモリ確保
		pBlack_Fill_Polygon = new CBlack_Fill_Polygon;

		// !nullcheck
		if (pBlack_Fill_Polygon != nullptr)
		{
			// 初期化処理
			pBlack_Fill_Polygon->Init(pos, size);
		}
	}
	// ポインタを返す
	return pBlack_Fill_Polygon;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CBlack_Fill_Polygon::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CScene3D::Init(pos, size);

	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_BLACK_FILL));

	// 向き設定
	SetRot(ZeroVector3);

	// 色設定
	SetColor(COL);

	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBlack_Fill_Polygon::Uninit(void)
{
	// 終了処理
	CScene3D::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBlack_Fill_Polygon::Update(void)
{
	// 更新処理
	CScene3D::Update();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CBlack_Fill_Polygon::Draw(void)
{
	// 描画処理
	CScene3D::Draw();
}