//=============================================================================
//
// 動画再生処理 [Movie.cpp]
// Author : Himiya Sho
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "Movie.h"
#include "input.h"
#include "keyboard.h"
#include "joypad.h"
#include "fade.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define KEYBORAD_MAX		(256)
#define MOVIE_PATH		L"./data/Movie/op_movie_1.avi"

//=============================================================================
// コンストラクタ
//=============================================================================
CMovie::CMovie()
{
	m_wcFileName = MOVIE_PATH;
	m_bIsloop = false;
	m_nNextMode = (int)CManager::MODE_TYPE_TITLE;
}

//=============================================================================
// デストラクタ
//=============================================================================
CMovie::~CMovie()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMovie::Init(void)
{
	// COM初期化
	CoInitialize(NULL);
	HRESULT hRes;

	// フィルタグラフマネージャの取得
	hRes = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&m_pGraph);
	if (FAILED(hRes))
	{
		// 失敗
		return hRes;
	}

	// VMR9フィルタの生成
	CoCreateInstance(CLSID_VideoMixingRenderer9, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&m_pVMR9);
	// フィルタの追加
	m_pGraph->AddFilter(m_pVMR9, L"VMR9");

	// ウィンドウレスモードにする
	IVMRFilterConfig *pVMRCfg = NULL;
	m_pVMR9->QueryInterface(IID_IVMRFilterConfig9, (void**)&pVMRCfg);
	pVMRCfg->SetRenderingMode(VMRMode_Windowless);
	pVMRCfg->Release(); // 使わないので解放
	pVMRCfg = NULL;

	// 描画ウィンドウの指定
	IVMRWindowlessControl *pVMRWndControl = NULL;;
	m_pVMR9->QueryInterface(IID_IVMRWindowlessControl9, (void**)&pVMRWndControl);
	m_hWnd = FindWindow("WindowClass", "Prison Leak");
	pVMRWndControl->SetVideoClippingWindow(m_hWnd);

	// ソースフィルタの作成と登録
	IBaseFilter *pSource = NULL;
	m_pGraph->AddSourceFilter(m_wcFileName, m_wcFileName, &pSource);

	// ICaptureGraphBuilder2インターフェイスの取得
	m_pCGB2 = NULL;
	hRes = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, (void**)&m_pCGB2);
	if (FAILED(hRes))
	{
		// 失敗
		return hRes;
	}
	// インターフェイスの初期化
	hRes = m_pCGB2->SetFiltergraph(m_pGraph);
	if (FAILED(hRes))
	{
		// 失敗
		return hRes;
	}

	// フィルタの接続
	m_pCGB2->RenderStream(0, 0, pSource, 0, m_pVMR9);				// ビデオの接続
	m_pCGB2->RenderStream(0, &MEDIATYPE_Audio, pSource, 0, 0);	// オーディオの接続

	// レンダリングサイズの指定 (フィルタの接続後にやること)
	LONG lWidth, lHeight;
	RECT SrcR, DestR;
	hRes = pVMRWndControl->GetNativeVideoSize(&lWidth, &lHeight, NULL, NULL);
	if (FAILED(hRes))
	{
		// 失敗
		return hRes;
	}

	SetRect(&SrcR, 0, 0, lWidth, lHeight);
	GetClientRect(m_hWnd, &DestR);
	hRes = pVMRWndControl->SetVideoPosition(&SrcR, &DestR);
	if (FAILED(hRes))
	{
		// 失敗
		return hRes;
	}

	pVMRWndControl->Release(); // 使わないので解放
	pVMRWndControl = NULL;

	// 
	IVideoWindow *pVidWnd = NULL;
	m_pGraph->QueryInterface(IID_IVideoWindow, (void**)&pVidWnd);

	// 表示サイズを0にする
	pVidWnd->SetWindowPosition(0, 0, 0, 0);
	// 見えなくする
	pVidWnd->put_Visible(OAFALSE);
	pVidWnd->Release();
	pVidWnd = NULL;

	// 再生終了取得用変数の生成
	m_pGraph->QueryInterface(IID_IMediaEventEx, (void**)&m_pMedEventEx);

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CMovie::Update(void)
{
	if (CManager::GetRenderer()->GetIsUseMovie())
	{
		CInputKeyboard* pKey = CManager::GetKeyboard();
		CFade::FADE_MODE mode = CManager::GetFade()->GetFade();
		long lEventCode;
		LONG_PTR lpEvParam1, lpEvparam2;

		// どこのキーでも反応する様に
		for (int nCnt = ZERO_INT; nCnt <= KEYBORAD_MAX; nCnt++)
		{
			// キーが押されたかつモード遷移中でない場合
			if (pKey->GetTrigger(nCnt) && mode == CFade::FADE_MODE_NONE)
			{
				// 画面遷移
				OnEndMovie();
			}
		}
		// コントローラのボタンを押した場合
		for (int nCnt = ZERO_INT; nCnt < CInputJoypad::JOY_BUTTON_MAX; nCnt++)
		{
			// キーが押されたかつモード遷移中でない場合
			if (CManager::GetJoypad()->GetJoystickTrigger(nCnt, 0) && mode == CFade::FADE_MODE_NONE)
			{
				// 画面遷移
				OnEndMovie();
			}
		}

		// 動画再生が終了したらタイトルに戻る
		m_pMedEventEx->GetEvent(&lEventCode, &lpEvParam1, &lpEvparam2, 0);
		if (lEventCode == EC_COMPLETE)
		{
			m_pMedEventEx->FreeEventParams(lEventCode, lpEvParam1, lpEvparam2);
			if (m_bIsloop)
			{
				Stop();
				Uninit();
				Init();
				Play();
			}
			else
			{
				// 画面遷移
				OnEndMovie();
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CMovie::Draw(void)
{
}

//=============================================================================
// 画面遷移処理
//=============================================================================
void CMovie::OnEndMovie(void)
{
	// 再生を停止
	Stop();
	Uninit();
	CManager::GetRenderer()->SetIsUseMovie(false);
}

//=============================================================================
// 再生する動画を変更する
//=============================================================================
void CMovie::ChangeMovie(WCHAR* path, bool bLoop)
{
	m_wcFileName = path;
	m_bIsloop = bLoop;
	Init();
}

//=============================================================================
// 再生処理
//=============================================================================
HRESULT CMovie::Play(void)
{
	HRESULT hRes;

	// フィルタグラフの実行
	m_pControl = NULL;
	m_pGraph->QueryInterface(IID_IMediaControl, (void**)&m_pControl);

	// メディア再生
	hRes = m_pControl->Run();
	if (FAILED(hRes))
	{
		// 失敗
		return hRes;
	}

	return S_OK;
}

//=============================================================================
// 再生停止処理
//=============================================================================
void CMovie::Stop(void)
{
	// グラフフィルタを停止
	m_pControl->Stop();
}

//=============================================================================
// 終了処理
//=============================================================================
void CMovie::Uninit(void)
{
	// メモリの解放
	m_pControl->Release();
	m_pVMR9->Release();
	m_pCGB2->Release();
	m_pGraph->Release();
}
