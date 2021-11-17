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
CScreenFrame::CScreenFrame(PRIORITY Priority) : CScene2D(Priority)
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
HRESULT CScreenFrame::Init(void)
{
	CScene2D::Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	m_apTexture[FRAME_NORMAL] = pTexture->GetTexture(CTexture::TETXTURE_NUM_SCREENFRAME);
	m_apTexture[FRAME_SECCAM] = pTexture->GetTexture(CTexture::TETXTURE_NUM_SCREENFRAME_SECCAM);
	m_apTexture[FRAME_FUZZ]   = pTexture->GetTexture(CTexture::TETXTURE_NUM_SCREENFRAME_FUZZ);
	BindTexture(m_apTexture[FRAME_NORMAL]);

	m_nCountSec = 0;
	m_bIsChanging = false;
	m_bUseSecCamOld = false;

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CScreenFrame::Update(void)
{
	bool bIsUseSecCam = CManager::GetRenderer()->GetIsUseSecCam();

	// 監視カメラとの切り替えが起きたら
	if (m_bIsChanging)
	{
		// 監視カメラを使用しているか
		if (bIsUseSecCam)
		{
			// 砂嵐をはさんで指定されたテクスチャに変更
			ChangeCamera(m_apTexture[FRAME_SECCAM]);
		}
		else
		{
			// 砂嵐をはさんで指定されたテクスチャに変更
			ChangeCamera(m_apTexture[FRAME_NORMAL]);
		}
	}
	else
	{
		// 1フレーム前と中身が違う場合
		if (m_bUseSecCamOld != bIsUseSecCam)
		{
			// 切り替えが起きた
			m_bIsChanging = true;
		}
		else
		{
			// 監視カメラを使用しているか
			if (bIsUseSecCam)
			{
				// テクスチャ変更
				BindTexture(m_apTexture[FRAME_SECCAM]);
			}
			else
			{
				// テクスチャ変更
				BindTexture(m_apTexture[FRAME_NORMAL]);
			}
		}
	}

	// 監視カメラ使用状況を保存
	m_bUseSecCamOld = bIsUseSecCam;

	CScene2D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CScreenFrame::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// 終了処理
//=============================================================================
void CScreenFrame::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 監視カメラ切り替え時処理
//=============================================================================
void CScreenFrame::ChangeCamera(LPDIRECT3DTEXTURE9 pTex)
{
	m_nCountSec++;
	BindTexture(m_apTexture[FRAME_FUZZ]);

	// 定義したフレーム数の間だけ砂嵐を描画
	if (m_nCountSec >= FRAME_CHANGE_LENGTH)
	{
		m_nCountSec = 0;
		// 指定されたテクスチャに変更
		BindTexture(pTex);
		m_bIsChanging = false;
	}
}

//=============================================================================
// インスタンス生成処理
//=============================================================================
CScreenFrame * CScreenFrame::Create(void)
{
	CScreenFrame *pFrame;
	pFrame = new CScreenFrame;
	pFrame->Init();

	return pFrame;
}
