//=============================================================================
//
// 画面分割UI処理 [screenframe.cpp]
// Author : 樋宮 匠
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "Screenframe.h"
#include "renderer.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9 CScreenFrame::m_apTexture[MAX_FRAME_TEX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CScreenFrame::CScreenFrame(PRIORITY Priority) : CScene(Priority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CScreenFrame::~CScreenFrame()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScreenFrame::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	m_apTexture[FRAME_NORMAL] = pTexture->GetTexture(CTexture::TETXTURE_NUM_SCREENFRAME);
	m_apTexture[FRAME_SECCAM] = pTexture->GetTexture(CTexture::TETXTURE_NUM_SCREENFRAME_SECCAM);
	m_apTexture[FRAME_FUZZ]   = pTexture->GetTexture(CTexture::TETXTURE_NUM_SCREENFRAME_FUZZ);

	for (int nCount = 0; nCount < FRAME_MAX; nCount++)
	{
		m_pScene2D[nCount] = new CScene2D;
		m_pScene2D[nCount]->Init(D3DXVECTOR3(SCREEN_WIDTH / 4 + (SCREEN_WIDTH / 2.0f) * nCount, SCREEN_HEIGHT / 2, 0.0f),D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT, 0.0f));
		m_pScene2D[nCount]->BindTexture(m_apTexture[FRAME_NORMAL]);
		m_pScene2D[nCount]->SetIsDraw(false);
		m_nCountSec[nCount] = 0;
		m_bIsChanging[nCount] = false;
		m_bUseSecCamOld[nCount] = false;
	}

	m_bIsEnableCam = true;

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CScreenFrame::Update(void)
{
	for (int nCount = 0; nCount < FRAME_MAX; nCount++)
	{	
		bool bIsUseSecCamPlayer = CManager::GetRenderer()->GetIsUseSecCamPlayer(nCount);
		// 監視カメラとの切り替えが起きたら
		if (m_bIsChanging[nCount])
		{
			// 監視カメラを使用しているか
			if (bIsUseSecCamPlayer)
			{
				// 砂嵐をはさんで指定されたテクスチャに変更
				ChangeCamera(nCount, m_apTexture[FRAME_SECCAM]);
			}
			else
			{
				// 砂嵐をはさんで指定されたテクスチャに変更
				ChangeCamera(nCount, m_apTexture[FRAME_NORMAL]);
			}
		}
		else
		{
			// 1フレーム前と中身が違う場合
			if (m_bUseSecCamOld[nCount] != bIsUseSecCamPlayer)
			{
				// 切り替えが起きた
				m_bIsChanging[nCount] = true;
			}
		}
		// 監視カメラ使用状況を保存
		m_bUseSecCamOld[nCount] = bIsUseSecCamPlayer;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CScreenFrame::Draw(void)
{
	for (int nCount = 0; nCount < FRAME_MAX; nCount++)
	{
		m_pScene2D[nCount]->SetIsDraw(true);
		m_pScene2D[nCount]->Draw();
		m_pScene2D[nCount]->SetIsDraw(false);
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void CScreenFrame::Uninit(void)
{
	for (int nCount = 0; nCount < FRAME_MAX; nCount++)
	{
		m_pScene2D[nCount]->Uninit();
		m_pScene2D[nCount] = NULL;
	}
	Release();
}

//=============================================================================
// 監視カメラ切り替え時処理
//=============================================================================
void CScreenFrame::ChangeCamera(int nFrameID, LPDIRECT3DTEXTURE9 pTex)
{
	m_nCountSec[nFrameID]++;
	m_pScene2D[nFrameID]->BindTexture(m_apTexture[FRAME_FUZZ]);

	// 定義したフレーム数の間だけ砂嵐を描画
	if (m_nCountSec[nFrameID] >= FRAME_CHANGE_LENGTH && m_bIsEnableCam)
	{
		m_nCountSec[nFrameID] = 0;
		// 指定されたテクスチャに変更
		m_pScene2D[nFrameID]->BindTexture(pTex);
		m_bIsChanging[nFrameID] = false;
	}
}

//=============================================================================
// インスタンス生成処理
//=============================================================================
CScreenFrame * CScreenFrame::Create(void)
{
	CScreenFrame *pFrame;
	pFrame = new CScreenFrame;
	pFrame->Init(ZeroVector3, ZeroVector3);

	return pFrame;
}
