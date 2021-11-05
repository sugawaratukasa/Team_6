//=============================================================================
//
// 画面分割UI処理 [screenframe.cpp]
// Author : 樋宮 匠
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "Timer.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9 CTimer::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CTimer::CTimer(PRIORITY Priority) : CScene2D(Priority)
{
	m_pScene2D = NULL;
	m_pGuage = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CTimer::~CTimer()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTimer::Init(void)
{
	// タイマーフレームの設定
	m_pScene2D = new CScene2D;
	m_pScene2D->Init(TIMER_POS, TIMER_SIZE);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	m_pScene2D->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_TIMER_FRAME));

	// タイマーゲージの設定
	m_pGuage = new CGauge;
	m_pGuage->Init();

	// 数字の設定
	m_pNumber = CNumber::Create(TIMER_NUM_POS);

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CTimer::Update(void)
{
	// 現在の時間に合わせる
	int nTimeMinit = m_pGuage->GetTime();
	m_pNumber->SetNumber(nTimeMinit);
}

//=============================================================================
// 描画処理
//=============================================================================
void CTimer::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 50);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pGuage->SetIsStencil(true);
	m_pGuage->Update();
	m_pGuage->DrawStencil();

	m_pGuage->SetIsStencil(false);
	m_pGuage->Update();
	m_pGuage->Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}

//=============================================================================
// 終了処理
//=============================================================================
void CTimer::Uninit(void)
{
	m_pGuage->Uninit();
}

//=============================================================================
// インスタンス生成処理
//=============================================================================
CTimer * CTimer::Create(void)
{
	CTimer *pTimer;
	pTimer = new CTimer;
	pTimer->Init();

	return pTimer;
}