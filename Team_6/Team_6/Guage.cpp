//=============================================================================
//
// ステンシル用ゲージ処理 [screenframe.cpp]
// Author : 樋宮 匠
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "Guage.h"
#include "Timer.h"
#include "fade.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEX_GUAGE 0
#define TEX_STENCIL 1

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9 CGauge::m_apTexture[TIMER_TEX_NUM] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CGauge::CGauge()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CGauge::~CGauge()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGauge::Init(void)
{
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();	//デバイスの取得
	VERTEX_2D *pVtx = nullptr;												//頂点情報へのポインタ

	m_pos = TIMER_POS;	//初期位置の設定

					//頂点バッファの作成
	pD3DDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * NUM_VERTEX,	//バッファサイズ
		D3DUSAGE_WRITEONLY,				//（固定）
		FVF_VERTEX_2D,					//フォーマット
		D3DPOOL_MANAGED,				//(固定)
		&m_pVtxBuff,
		nullptr
	);

	//頂点データをロックし、頂点バッファへのポインタ取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-TIMER_SIZE.x / 2), m_pos.y + (-TIMER_SIZE.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (TIMER_SIZE.x / 2), m_pos.y + (-TIMER_SIZE.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-TIMER_SIZE.x / 2), m_pos.y + (TIMER_SIZE.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (TIMER_SIZE.x / 2), m_pos.y + (TIMER_SIZE.y / 2), 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	m_apTexture[TEX_GUAGE] = pTexture->GetTexture(CTexture::TEXTURE_NUM_TIMER_GUAGE);
	m_apTexture[TEX_STENCIL] = pTexture->GetTexture(CTexture::TEXTURE_NUM_TIMER_STENCIL);

	m_bIsStencil = false;
	m_fAngle = 0.0f;
	m_nTime = time(NULL);
	m_fRatio = 0.0f;
	m_nRemainTime = TIMER_MINIT;
	m_bTimer = false;
	m_nElapsedTime = ZERO_INT;
	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CGauge::Update(void)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx = nullptr;

	//頂点データをロックし、頂点バッファへのポインタ取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (m_bIsStencil)
	{	
		// 経過時間計算
		CalcTime();

		// 計算用変数
		D3DXVECTOR3 pos[NUM_VERTEX];

		// 頂点情報を設定
		pos[0] = D3DXVECTOR3((-TIMER_SIZE.x / 2), (-TIMER_SIZE.y / 2), 0.0f);
		pos[1] = D3DXVECTOR3((TIMER_SIZE.x / 2), (-TIMER_SIZE.y / 2), 0.0f);
		pos[2] = D3DXVECTOR3((-TIMER_SIZE.x / 2), (TIMER_SIZE.y / 2), 0.0f);
		pos[3] = D3DXVECTOR3((TIMER_SIZE.x / 2), (TIMER_SIZE.y / 2), 0.0f);

		// 回転行列用
		D3DXMATRIX mtx;
		// 行列作成
		D3DXMatrixRotationYawPitchRoll(&mtx, 0.0f, 0.0f, m_fAngle);
		// 頂点を回転行列を用いて回転
		for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		{
			D3DXVec3TransformCoord(&pos[nCount], &pos[nCount], &mtx);
			pos[nCount] += m_pos;
		}

		// 頂点情報を設定
		pVtx[0].pos = pos[0];
		pVtx[1].pos = pos[1];
		pVtx[2].pos = pos[2];
		pVtx[3].pos = pos[3];
	}
	else
	{
		// 頂点情報を設定
		pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-TIMER_SIZE.x / 2), m_pos.y + (-TIMER_SIZE.y / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (TIMER_SIZE.x / 2), m_pos.y + (-TIMER_SIZE.y / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-TIMER_SIZE.x / 2), m_pos.y + (TIMER_SIZE.y / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (TIMER_SIZE.x / 2), m_pos.y + (TIMER_SIZE.y / 2), 0.0f);
	}

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ステンシル描画処理
//=============================================================================
void CGauge::DrawStencil(void)
{
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();	//デバイスの取得

	// Zバッファ系
	pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER); // Zバッファを一時的に全て失敗
	// ステンシル
	pD3DDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
	pD3DDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);
	pD3DDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	// ステンシルテストのテスト設定
	pD3DDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	pD3DDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE);
	pD3DDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

	CRenderer *pRenderer = CManager::GetRenderer();

	// 頂点バッファをデータストリームに設定
	pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pD3DDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pD3DDevice->SetTexture(0, m_apTexture[TEX_STENCIL]);

	// ポリゴンの描画
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// Zバッファ比較設定変更
	pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	// ステンシル
	pD3DDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
	pD3DDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);
	pD3DDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	// ステンシルテストのテスト設定
	pD3DDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	pD3DDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	pD3DDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
}

//=============================================================================
// 描画処理
//=============================================================================
void CGauge::Draw(void)
{
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();	//デバイスの取得

	CRenderer *pRenderer = CManager::GetRenderer();

	// 頂点バッファをデータストリームに設定
	pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pD3DDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pD3DDevice->SetTexture(0, m_apTexture[TEX_GUAGE]);

	// ポリゴンの描画
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}
//=============================================================================
// 終了処理
//=============================================================================
void CGauge::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// 経過時間計算処理
//=============================================================================
void CGauge::CalcTime(void)
{

	m_nElapsedTime = time(NULL) - m_nTime;

	// 割合を求めてUIを回転
	m_fRatio = (float)m_nElapsedTime / (float)(TIMER_LENGTH);
	m_fAngle = D3DXToRadian(TIMER_ANGLE * m_fRatio);

	if (m_fAngle >= D3DXToRadian(360))
	{
		m_fAngle = 0.0f;
	}

	// タイムオーバー時の処理
	if (m_fRatio >= 1.0f)
	{
		OnTimerOver();
	}
}

//=============================================================================
// 時間切れ時処理
//=============================================================================
void CGauge::OnTimerOver(void)
{
	// 時間切れ
	CFade *pFade = CManager::GetFade();
	pFade->SetFade(CManager::MODE_TYPE_GAMEOVER);
}

//=============================================================================
// 時間取得処理
//=============================================================================
int CGauge::GetTime(void)
{
	int nElapsedTime = time(NULL) - m_nTime;

	// 1分ごとに1度だけ処理
	if (nElapsedTime % 60 == 0)
	{
		if (!m_bTimer)
		{
			m_nRemainTime -= 1;
			m_bTimer = true;
		}
	}
	else
	{
		m_bTimer = false;
	}

	return m_nRemainTime;
}
