//=======================================================================================
//
// リザルトクラス [tutorial.cpp]
// Author : Sugawara Tsukasa
//
//=======================================================================================

//=======================================================================================
// インクルードファイル
//=======================================================================================
#include "result.h"
#include "scene_2d.h"
#include "manager.h"
#include "keyboard.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "sound.h"
#include "joypad.h"
#include "resource_manager.h"

//=======================================================================================
// コンストラクタ
//=======================================================================================
CResult::CResult()
{
}

//=======================================================================================
// デストラクタ
//=======================================================================================
CResult::~CResult()
{
	// 終了処理
	Uninit();
}

//=======================================================================================
// 初期化処理
//=======================================================================================
HRESULT CResult::Init(void)
{

	return S_OK;
}

//=======================================================================================
// 終了処理
//=======================================================================================
void CResult::Uninit(void)
{
}

//=======================================================================================
// 更新処理
//=======================================================================================
void CResult::Update(void)
{
}

//=======================================================================================
// 描画処理
//=======================================================================================
void CResult::Draw(void)
{

}
