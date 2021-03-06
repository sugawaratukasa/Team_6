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

	CScene2D::Init(TIMER_POS, TIMER_SIZE);	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	CScene2D::BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_TIMER_FRAME));

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
	if (nTimeMinit <= 0)
	{
		nTimeMinit = 0;
	}
	m_pNumber->SetNumber(nTimeMinit);

	// タイム設定
	m_pGuage->SetCurrentTime();
}

//=============================================================================
// 描画処理
//=============================================================================
void CTimer::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// フォグを無効化
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

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

	CScene2D::Draw();

	// フォグを有効化
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
}

//=============================================================================
// 終了処理
//=============================================================================
void CTimer::Uninit(void)
{
	m_pGuage->Uninit();
	m_pGuage = NULL;
	CScene2D::Uninit();
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