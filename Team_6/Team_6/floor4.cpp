//=============================================================================
// 床 [floor.cpp]
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
#include "floor4.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define COL (D3DCOLOR_RGBA(255, 255, 255, 255))	// 色
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CFloor4::CFloor4(PRIORITY Priority) : CScene3D(Priority)
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CFloor4::~CFloor4()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CFloor4 * CFloor4::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CFloorのポインタ
	CFloor4 *pFloor = nullptr;

	// nullcheck
	if (pFloor == nullptr)
	{
		// メモリ確保
		pFloor = new CFloor4;

		// !nullcheck
		if (pFloor != nullptr)
		{
			// 初期化処理
			pFloor->Init(pos, size);
		}
	}
	// ポインタを返す
	return pFloor;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CFloor4::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CScene3D::Init(pos, size);

	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_FLOOR_4));

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
void CFloor4::Uninit(void)
{
	// 終了処理
	CScene3D::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CFloor4::Update(void)
{
	// 更新処理
	CScene3D::Update();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CFloor4::Draw(void)
{
	// 描画処理
	CScene3D::Draw();
}