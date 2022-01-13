//=============================================================================
//
// ゲームオーバー背景 [bg_gameover.h]
// Author : 二階堂汰一
//
//=============================================================================
#include "main.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "scene_2d.h"
#include "bg_gameover.h"

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CGameOverBG::CGameOverBG(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CGameOverBG::~CGameOverBG()
{
}

//=============================================================================
// 生成処理関数
// Author : Nikaido Taichi
//=============================================================================
CGameOverBG * CGameOverBG::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CGameOverBGのポインタ
	CGameOverBG *pGameOverBG = nullptr;

	// nullcheck
	if (pGameOverBG == nullptr)
	{
		// メモリ確保
		pGameOverBG = new CGameOverBG;

		// !nullcheck
		if (pGameOverBG != nullptr)
		{
			// 初期化処理
			pGameOverBG->Init(pos, size);
		}
	}
	// ポインタを返す
	return pGameOverBG;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CGameOverBG::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン2Dの初期化処理関数呼び出し
	CScene2D::Init(pos, size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_GAMEOVER));
	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CGameOverBG::Uninit(void)
{
	// シーン2Dの終了処理関数呼び出し
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CGameOverBG::Update(void)
{
	// シーン2Dの更新処理関数呼び出し
	CScene2D::Update();
}

//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CGameOverBG::Draw(void)
{
	// シーン2Dの描画処理関数呼び出し
	CScene2D::Draw();
}
