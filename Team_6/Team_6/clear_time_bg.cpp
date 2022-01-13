//=============================================================================
// クリアタイム背景 [clear_time_bg.cpp]
// Author : SugawaraTsuksa
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "clear_time_bg.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"
//=============================================================================
// マクロ定義
// Author : SugawaraTsuksa
//=============================================================================
#define SIZE_VALUE	(D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f))
//=============================================================================
// コンストラクタ
// Author : SugawaraTsuksa
//=============================================================================
CClear_Time_bg::CClear_Time_bg()
{
}

//=============================================================================
// デストラクタ
// Author : SugawaraTsuksa
//=============================================================================
CClear_Time_bg::~CClear_Time_bg()
{
}
//=============================================================================
// インスタンス生成処理
// Author : SugawaraTsuksa
//=============================================================================
CClear_Time_bg * CClear_Time_bg::Create(D3DXVECTOR3 pos)
{
	// CClear_Time_bgのポインタ
	CClear_Time_bg *pClear_Time_bg = nullptr;

	// nullptrの場合
	if (pClear_Time_bg == nullptr)
	{
		// メモリ確保
		pClear_Time_bg = new CClear_Time_bg;

		// !nullcheck
		if (pClear_Time_bg != nullptr)
		{
			pClear_Time_bg->Init(pos);
		}
	}
	// ポインタを返す
	return pClear_Time_bg;
}
//=============================================================================
// 初期化処理
// Author : SugawaraTsuksa
//=============================================================================
HRESULT CClear_Time_bg::Init(D3DXVECTOR3 pos)
{
	CScene2D::Init(pos, SIZE_VALUE);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_CLEAR_TIME_BG));

	return S_OK;
}

//=============================================================================
// 終了処理
// Author : SugawaraTsuksa
//=============================================================================
void CClear_Time_bg::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
// Author : SugawaraTsuksa
//=============================================================================
void CClear_Time_bg::Update(void)
{
	CScene2D::Update();
}

//=============================================================================
// 描画処理
// Author : SugawaraTsuksa
//=============================================================================
void CClear_Time_bg::Draw(void)
{
	CScene2D::Draw();
}