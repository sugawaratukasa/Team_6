//=============================================================================
//
// 警告バー [caveat.cpp]
// Author : Oguma Akira
//
//=============================================================================

//=============================================================================
// マクロ定義
//=============================================================================
#define DEF_SIZE (D3DXVECTOR3(0.0f, 100.0f, 0.0f))	//テクスチャのデフォルトサイズ
#define MAX_SIZE_X (540.0f)	//横の最大サイズ
#define MAX_BAR_RATIO (540.0f)	//バーの最大比率
#define INCDEC_COLOR_BAR (0.1f)	//色の増減値
#define SIZE_RATIO (MAX_SIZE_X / 4)	//テクスチャの割合での大きさ
#define MAX_COLOR_BAR (1.0f)	//色の最大値

//=============================================================================
// インクルード
//=============================================================================
#include "caveatbar.h"
#include "caveatmark.h"
#include "texture.h"
#include "resource_manager.h"
#include "manager.h"
#include "mode_base.h"
#include "jailer_spot.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CCaveatBar::CCaveatBar()
{
	m_fBarNow = ZERO_FLOAT;
	m_nPlayerNum = ZERO_INT;
	m_pCaveat = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CCaveatBar::~CCaveatBar()
{

}

//=============================================================================
// 生成
//=============================================================================
CCaveatBar *CCaveatBar::Create(D3DXVECTOR3 pos, const int nPlayer)
{
	// CCaveatBarのポインタ
	CCaveatBar *pCaveatBar = nullptr;

	// nullcheck
	if (pCaveatBar == nullptr)
	{	
		pCaveatBar = new CCaveatBar;// メモリ確保

		// !nullcheck
		if (pCaveatBar != nullptr)
		{
			pCaveatBar->m_nPlayerNum = nPlayer;
			pCaveatBar->Init(pos);	// 初期化処理
		}
	}
	// ポインタを返す
	return pCaveatBar;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CCaveatBar::Init(D3DXVECTOR3 pos)
{
	CScene2D::Init(pos, DEF_SIZE);
	//警告マークの生成
	m_pCaveat = CCaveatMark::Create(D3DXVECTOR3(pos.x, pos.y - 50, pos.z));
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_CAVEATBAR));
	return S_OK;
}

//=============================================================================
// 更新
//=============================================================================
void CCaveatBar::Update(void)
{
	//ベクトルの長さ
	float fVecLength = VecLength();
	BarMove(fVecLength);

	//警告マークの更新
	if (m_pCaveat!=nullptr)
	{
		m_pCaveat->Update();
	}
	CScene2D::Update();
}

//=============================================================================
// 終了
//=============================================================================
void CCaveatBar::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 描画
//=============================================================================
void CCaveatBar::Drow(void)
{
	CScene2D::Draw();
}


//=============================================================================
// ベクトルの長さ
//=============================================================================
float CCaveatBar::VecLength(void)
{
	//各プレイヤー情報の取得
	CPlayer *pPlayer = CManager::GetModePtr()->GetPlayer(m_nPlayerNum);
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

	float fLength = 1000000.0f;	//距離

	//各看守の情報取得
	for (int nCntJalier = ZERO_INT; nCntJalier < MAX_JAILER; nCntJalier++)
	{
		//看守情報の取得
		CJailer *pJalier = CManager::GetModePtr()->GetJailer(nCntJalier);

		//各看守の居る側と各プレイヤーがいる側が一致しない場合
		if (pJalier->GetJailerSpot()->GetArea() != m_nPlayerNum)
		{
			continue;
		}

		D3DXVECTOR3 JalierPos = pJalier->GetPos();
		D3DXVECTOR3 distance = JalierPos - PlayerPos;
		float fdistance = D3DXVec3Length(&distance);	//長さ取得

		//各看守とプレイヤーとの長さ比較
		if (fdistance < fLength)
		{
			fLength = fdistance;
		}
	}
	return fLength;
}

//=============================================================================
//バーの動き
//=============================================================================
void CCaveatBar::BarMove(const float fLength)
{
	//変数宣言
	m_fBarNow = MAX_BAR_RATIO / fLength * MAX_SIZE_X;

	if (m_fBarNow < MAX_BAR_RATIO)
	{
		GetSize().x = m_fBarNow ;
		BarColor();
	}
}

//=============================================================================
// バーの色変化
//=============================================================================
void CCaveatBar::BarColor(void)
{
	D3DXCOLOR color = GetColor();
	//緑
	if (m_fBarNow < MAX_SIZE_X / 3)
	{
		m_pCaveat->ColorState(CCaveatMark::FADEIN_STATE);
		if (ZERO_FLOAT < color.a)
		{
			color.a -= INCDEC_COLOR_BAR;
		}
		color = D3DXCOLOR(ZERO_FLOAT, MAX_COLOR_BAR, ZERO_FLOAT, color.a);

	}	
	//黄色
	else if (m_fBarNow < MAX_SIZE_X / 1.5f)
	{
		m_pCaveat->ColorState(CCaveatMark::NORMAL_STATE);
		if (color.a < MAX_COLOR_BAR)
		{
			color.a += INCDEC_COLOR_BAR;
		}
		color = D3DXCOLOR(MAX_COLOR_BAR, MAX_COLOR_BAR, ZERO_FLOAT, color.a);
	}
	//赤
	else
	{
		m_pCaveat->ColorState(CCaveatMark::FLASH_STATE);
		if (color.a < MAX_COLOR_BAR)
		{
			color.a += INCDEC_COLOR_BAR;
		}
		color = D3DXCOLOR(MAX_COLOR_BAR, ZERO_FLOAT, ZERO_FLOAT, color.a);
	}
	SetColor(color);
}
