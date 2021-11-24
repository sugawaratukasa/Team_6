#include "main.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "scene_2d.h"
#include "bg_pause.h"

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CPauseBG::CPauseBG(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CPauseBG::~CPauseBG()
{
}

//=============================================================================
// 生成処理関数
// Author : Nikaido Taichi
//=============================================================================
CPauseBG * CPauseBG::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CPauseのポインタ
	CPauseBG *pPauseBG = nullptr;

	// nullcheck
	if (pPauseBG == nullptr)
	{
		// メモリ確保
		pPauseBG = new CPauseBG;

		// !nullcheck
		if (pPauseBG != nullptr)
		{
			// 初期化処理
			pPauseBG->Init(pos, size);
		}
	}
	// ポインタを返す
	return pPauseBG;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CPauseBG::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン2Dの初期化処理関数呼び出し
	CScene2D::Init(pos, size);
	SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f));
	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPauseBG::Uninit(void)
{
	// シーン2Dの終了処理関数呼び出し
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPauseBG::Update(void)
{
	// シーン2Dの更新処理関数呼び出し
	CScene2D::Update();
}

//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPauseBG::Draw(void)
{
	// シーン2Dの描画処理関数呼び出し
	CScene2D::Draw();
}
