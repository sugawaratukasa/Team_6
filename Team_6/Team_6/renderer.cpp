//=============================================================================
//
// レンダラー処理 [renderer.cpp]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "renderer.h"
#include "scene.h"
#include "fade.h"
#include "manager.h"
#include "camera.h"
#include "game.h"
#include "keyboard.h"
#include "polygon.h"
#include "shadow.h"
#include "debug_proc.h"
#include "camera_game.h"
#include "fog.h"
#include "textlog.h"
#include "texture.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define FOG_START_PLAYER 1600.0f
#define FOG_START_SECCAM 1900.0f
#define FOG_END_PLAYER 2300.0f
#define FOG_END_SECCAM 2500.0f

//=============================================================================
// レンダリングクラスのコンストラクタ
//=============================================================================
CRenderer::CRenderer()
{
	m_pD3D = nullptr;			// Direct3Dオブジェクト
	m_fillMode = D3DFILL_SOLID;
	m_bIsUseMovie = false;
}

//=============================================================================
// レンダリングクラスのデストラクタ
//=============================================================================
CRenderer::~CRenderer()
{

}

//=============================================================================
// レンダリングクラスの初期化処理
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;	//プレゼンテーションパラメータ
	D3DDISPLAYMODE d3ddm;	//ディスプレイモード

							// Direct3Dオブジェクトの作成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == nullptr)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;										// バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;							// カラーモードの指定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						// 映像信号に同期してフリップする
	d3dpp.EnableAutoDepthStencil = TRUE;							// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;					// デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;										// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル

	m_pD3DInterface = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3DInterface == nullptr)
	{
		// 作成失敗
		return E_FAIL;
	}


	// デバイスの生成
	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,				// D3DDEVTYPE_HAL：ハードウェアでラスタ化とシェーディングを行い、(座標変換と照明計算)を行う
		D3DDEVTYPE_HAL,												// D3DDEVTYPE_REF:リファレンスラスタライザ。ドライバのバグをチェックできる
		hWnd,														// D3DCREATE_PUREDEVICE                :ラスタ化、座標変換、照明計算、シェーディングを指定、上のフラグの修飾子
		D3DCREATE_HARDWARE_VERTEXPROCESSING,						// D3DCREATE_SOFTWARE_VERTEXPROCESSING：ソフトウェアによる頂点処理を指定
		&d3dpp, &m_pD3DDevice)))									// D3DCREATE_HARDWARE_VERTEXPROCESSING：ハードウェアによる頂点処理。
	{																// D3DCREATE_MIXED_VERTEXPROCESSING   ：ミックス(ソフトウェアとハードウェアの両方)による頂点処理を指定します。

																	// 上記の設定が失敗したら								
																	// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice)))
			{
				// 生成失敗
				return E_FAIL;
			}
		}
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	// レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);					// 裏面を（左回り）をカリング
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);							// Zバッファを使用
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);					// αブレンドを行う
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			// αソースカラーの指定
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// αデスティネーションカラーの設定

																				// サンプラーステートの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);		// テクスチャのU値の繰り返し
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);		// テクスチャのV値の繰り返し
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);		// テクスチャ拡大時の補完設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);		// テクスチャ縮小時の補完設定

																				// テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);		// アルファブレンディング処理
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		// 最初のアルファ引数（初期値）
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);		// 2番目のアルファ引数（初期値）

	//環境光
	D3DMATERIAL9 material;
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient.r = 1.0f;
	material.Ambient.g = 1.0f;
	material.Ambient.b = 1.0f;
	material.Ambient.a = 1.0f;
	m_pD3DDevice->SetMaterial(&material);
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x44444444);

	m_bUseSecCam = false;

	InitFog();

	return S_OK;
}

//=============================================================================
// レンダリングクラスの終了処理
//=============================================================================
void CRenderer::Uninit(void)
{
	// デバイスの破棄
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	// Direct3Dオブジェクトの破棄
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
}

//=============================================================================
// レンダリングクラスの更新処理
//=============================================================================
void CRenderer::Update(void)
{
	// キーボード情報
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// ポリゴンの表示
	if (pKeyboard->GetTrigger(DIK_M))
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスへのポインタ

		switch (m_fillMode)
		{
		case D3DFILL_SOLID:
			m_fillMode = D3DFILL_WIREFRAME;
			break;
		case D3DFILL_WIREFRAME:
			m_fillMode = D3DFILL_SOLID;
			break;
		}

		pDevice->SetRenderState(D3DRS_FILLMODE, m_fillMode);
	}

	if (pKeyboard->GetTrigger(DIK_3))
	{
		SwitchCam();
	}

	if (pKeyboard->GetTrigger(DIK_4))
	{
		SetFogState(FOG_END);
	}
	if (pKeyboard->GetTrigger(DIK_5))
	{
		SetFogState(FOG_WARNING);
	}
	if (pKeyboard->GetTrigger(DIK_6))
	{
		CTextLog::Create(CTexture::TEXTURE_NUM_TEXTLOG_TEST);
	}
	// 全ての更新
	CScene::UpdateAll();
}

//=============================================================================
// レンダリングクラスの描画処理
//=============================================================================
void CRenderer::Draw(void)
{

	float fStart = 500.0f;
	float fEnd = 1000.0f;

	if (m_bIsUseMovie)
	{

	}
	else
	{
		m_pD3DDevice->Clear(0,
			nullptr,
			(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
			D3DCOLOR_RGBA(0, 255, 255, 0),
			1.0f,
			0);


		m_pD3DDevice->Clear(0,
			nullptr,
			D3DCLEAR_STENCIL,
			D3DCOLOR_XRGB(0, 0, 0),
			1.0f,
			0);

		CFade *pFade = CManager::GetFade();

		// Direct3Dによる描画の開始
		if (SUCCEEDED(m_pD3DDevice->BeginScene()))
		{

			// モードがgameなら
			if (CManager::GetMode() == CManager::MODE_TYPE_GAME)
			{

				// 監視カメラを見ているなら
				if (m_bUseSecCam)
				{
					InitSecCamFog();

					// ビューポート設定
					SetUpViewPort(CCamera::SCREEN_NONE);
					//オブジェクトクラスの全描画処理呼び出し
					CScene::DrawAll();


					if (pFade != nullptr)
					{
						// 描画処理
						pFade->Draw();
					}
				}
				else
				{
					// ビューポートの数だけ描画する
					for (int nCount = 0; nCount < CCamera::SCREEN_MAX - 1; nCount++)
					{
						InitPlayerFog();

						// ビューポート設定
						SetUpViewPort((CCamera::SCREEN_ID)(nCount + 1));

						// バッファのクリア
						m_pD3DDevice->Clear(0,
							nullptr,
							(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
							D3DCOLOR_RGBA(0, 255, 255, 0),
							1.0f,
							0);

						m_pD3DDevice->Clear(0,
							nullptr,
							D3DCLEAR_STENCIL,
							D3DCOLOR_XRGB(0, 0, 0),
							1.0f,
							0);


						// カメラ位置を修正
						((CGame*)CManager::GetModePtr())->GetCamera((CGame::CAMERA_ID)nCount)->ModifyCamera((CGame::CAMERA_ID)nCount);

						//オブジェクトクラスの全描画処理呼び出し
						CScene::DrawAll();

						if (pFade != nullptr)
						{
							// 描画処理
							pFade->Draw();
						}
					}
				}

				UpdateFog();
			}
			else
			{
				// ビューポート設定
				SetUpViewPort(CCamera::SCREEN_NONE);


				//オブジェクトクラスの全描画処理呼び出し
				CScene::DrawAll();


				if (pFade != nullptr)
				{
					// 描画処理
					pFade->Draw();
				}
			}

			// デバッグプロシージャ
			CDebugProc *pDebugProc = CManager::GetDebugProc();
			if (pDebugProc != nullptr)
			{
				pDebugProc->Draw();
			}

			// Direct3Dによる描画の終了
			m_pD3DDevice->EndScene();
		}

		// バックバッファとフロントバッファの入れ替え
		m_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
	}
}

//=============================================================================
// ステンシルの設定
// Author : Konishi Yuuto
//=============================================================================
void CRenderer::SetStateStencil(void)
{
	//------------------------------------------------------------
	// パス1:影ボリュームの描画
	//------------------------------------------------------------
	// 深度バッファに書き込みはしない
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// レンダリングターゲットに書き込みはしない
	m_pD3DDevice->SetRenderState(D3DRS_COLORWRITEENABLE, FALSE);

	// 両面描く
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// 両面ステンシルを使用する
	m_pD3DDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE, TRUE);

	// ステンシルテストは常に合格にする
	m_pD3DDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);

	// 表面は深度テストに合格したらステンシルバッファの内容を+1する
	m_pD3DDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);

	// 裏面は深度テストに合格したらステンシルバッファの内容を-1する
	m_pD3DDevice->SetRenderState(D3DRS_CCW_STENCILPASS, D3DSTENCILOP_DECR);
}

//=============================================================================
// ステンシルテスト設定
// Author : Konishi Yuuto
//=============================================================================
void CRenderer::SetStencilTest(void)
{
	// 状態を元に戻す
	m_pD3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);

	//--------------------------------------------------------------
	// パス2:影の描画
	//--------------------------------------------------------------
	// アルファブレンディングは線型に掛ける
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	// ステンシルバッファの値が1以上の時に書き込む
	m_pD3DDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
	m_pD3DDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL);

	// 透過あり
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// ステンシル設定リセット
// Author : Konishi Yuuto
//=============================================================================
void CRenderer::ReSetStateStencil(void)
{
	// 状態を元に戻す
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}

//=============================================================================
// デバイスの取得処理
//=============================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}

//=============================================================================
// ビューポートの設定
//=============================================================================
void CRenderer::SetUpViewPort(CCamera::SCREEN_ID id)
{
	// ビューポートパラメータ
	D3DVIEWPORT9 view_port;
	D3DXVECTOR2 size;

	// ID別にスクリーンサイズの設定
	switch (id)
	{
	case CCamera::SCREEN_NONE:
		// スクリーンサイズ設定
		size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);

		// 左上座標(原点)の設定
		view_port.X = ZeroVector2.x;
		view_port.Y = ZeroVector2.y;

		// ビューポートの幅
		view_port.Width = SCREEN_WIDTH;
		// ビューポートの高さ
		view_port.Height = SCREEN_HEIGHT;
		break;
	case CCamera::SCREEN_LEFT:
		// スクリーンサイズ設定
		size = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

		// 左上座標(原点)の設定
		view_port.X = ZeroVector2.x;
		view_port.Y = ZeroVector2.y;

		// ビューポートの幅
		view_port.Width = SCREEN_WIDTH / 2;
		// ビューポートの高さ
		view_port.Height = SCREEN_HEIGHT;
		break;
	case CCamera::SCREEN_RIGHT:
		// スクリーンサイズ設定
		size = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

		// 左上座標(原点)の設定
		view_port.X = SCREEN_WIDTH / 2;
		view_port.Y = ZeroVector2.y;

		// ビューポートの幅
		view_port.Width = SCREEN_WIDTH / 2;
		// ビューポートの高さ
		view_port.Height = SCREEN_HEIGHT;
		break;
	default:
		break;
	}

	// ビューポート深度設定
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ビューポート設定
	pDevice->SetViewport(&view_port);
}