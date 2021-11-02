#ifndef _RENDERER_H_
#define _RENDERER_H_
//=============================================================================
//
// レンダラー処理 [renderer.h]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "camera.h"

//=============================================================================
// レンダラークラス
//=============================================================================
class CRenderer
{
public:
	CRenderer();	// コンストラクタ
	~CRenderer();	// デストラクタ

	HRESULT Init(HWND hWnd, bool bWindow);		// 初期化処理
	void Uninit(void);							// 終了処理
	void Update(void);							// 更新処理
	void Draw(void);							// 描画処理

	void SetStateStencil(void);					// ステンシルの設定
	void SetStencilTest(void);					// ステンシルテスト設定
	void ReSetStateStencil(void);				// ステンシル情報リセット
	void SetUpViewPort(CCamera::SCREEN_ID id);

	LPDIRECT3DDEVICE9 GetDevice(void);			// デバイス情報

private:
	LPDIRECT3DDEVICE9 m_pD3DDevice;				// Deviceオブジェクト(描画に必要)
	LPDIRECT3D9	m_pD3D;							// Direct3Dオブジェクト
	LPDIRECT3D9 m_pD3DInterface;				// DirectXインターフェース
	D3DFILLMODE m_fillMode;						// ワイヤーフレーム
};

#endif