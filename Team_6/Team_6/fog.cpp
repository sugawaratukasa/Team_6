//=============================================================================
//
// フォグヘッダー [fog.h]
// Author : Himiya Sho
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "fog.h"
#include "renderer.h"
#include "manager.h"
#include "scene3d.h"

//=======================================================================================
// マクロ定義
//=======================================================================================
#define FOG_START_PLAYER 1600.0f
#define FOG_START_SECCAM 1900.0f
#define FOG_END_PLAYER 2300.0f
#define FOG_END_SECCAM 2500.0f
#define FOG_FADE_LENGTH 60.0f

//=======================================================================================
// グローバル変数宣言
//=======================================================================================
int g_nFogCount;
FOG_STATE g_FogState;
D3DXCOLOR g_col;
float g_fColRate;
bool g_bFadeIn;

//=======================================================================================
// フォグ初期化
//=======================================================================================
HRESULT InitFog(void)
{
	g_nFogCount = 0;
	g_FogState = FOG_NONE;
	g_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	g_fColRate = 0.0f;
	g_bFadeIn = true;
	return S_OK;
}

//=======================================================================================
// プレイヤーフォグ初期化処理
//=======================================================================================
HRESULT InitPlayerFog(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// フォグ有効化
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	// フォグカラー設定
	pDevice->SetRenderState(D3DRS_FOGCOLOR, g_col);
	// バーテックスフォグ(線形公式)を使用
	pDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR);
	// 範囲ベースのフォグを使用
	pDevice->SetRenderState(D3DRS_RANGEFOGENABLE, TRUE);

	float fStart = FOG_START_PLAYER;
	float fEnd = FOG_END_PLAYER;
	// フォグ範囲設定
	pDevice->SetRenderState(D3DRS_FOGSTART, *((LPDWORD)(&fStart)));
	pDevice->SetRenderState(D3DRS_FOGEND, *((LPDWORD)(&fEnd)));

	return S_OK;
}

//=======================================================================================
// 監視カメラフォグ初期化処理
//=======================================================================================
HRESULT InitSecCamFog(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// フォグ有効化
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	// フォグカラー設定
	pDevice->SetRenderState(D3DRS_FOGCOLOR, g_col);
	// バーテックスフォグ(線形公式)を使用
	pDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR);
	// 範囲ベースのフォグを使用
	pDevice->SetRenderState(D3DRS_RANGEFOGENABLE, TRUE);

	float fStart = FOG_START_SECCAM;
	float fEnd = FOG_END_SECCAM;
	// フォグ範囲設定
	pDevice->SetRenderState(D3DRS_FOGSTART, *((LPDWORD)(&fStart)));
	pDevice->SetRenderState(D3DRS_FOGEND, *((LPDWORD)(&fEnd)));

	return S_OK;
}

//=======================================================================================
// フォグステート変更関数
//=======================================================================================
void SetFogState(FOG_STATE state)
{
	g_FogState = state;
}

//=======================================================================================
// フォグ更新処理
//=======================================================================================
void UpdateFog(void)
{
	switch (g_FogState)
	{
	case FOG_NONE:
		g_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		break;
	case FOG_END:
		if (g_bFadeIn)
		{
			g_fColRate += 1.0f / FOG_FADE_LENGTH;
			if (g_fColRate >= 1.0f)
			{
				g_bFadeIn = false;
			}
		}
		else
		{
			g_fColRate -= 1.0f / FOG_FADE_LENGTH;
			if (g_fColRate <= 0.0f)
			{
				SetFogState(FOG_NONE);
				g_bFadeIn = true;
			}
		}

		g_col = D3DXCOLOR(0.0f + g_fColRate, 0.0f, 0.0f, 1.0f);
		break;
	case FOG_WARNING:
		if (g_bFadeIn)
		{
			g_fColRate += 1.0f / FOG_FADE_LENGTH;
			if (g_fColRate >= 1.0f)
			{
				g_bFadeIn = false;
			}
		}
		else
		{
			g_fColRate -= 1.0f / FOG_FADE_LENGTH;
			if (g_fColRate <= 0.0f)
			{
				g_bFadeIn = true;
			}
		}

		g_col = D3DXCOLOR(0.0f + g_fColRate, 0.0f, 0.0f, 1.0f);
		break;
	default:
		break;
	}
}
