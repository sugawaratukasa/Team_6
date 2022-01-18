//=============================================================================
//
// 警告マーク [caveatmark.cpp]
// Author : Oguma Akira
//
//=============================================================================

//=============================================================================
// マクロ定義
//=============================================================================
#define DEF_SIZE (D3DXVECTOR3(50.0f, 50.0f, 0.0f))	//テクスチャのデフォルトサイズ
#define MAX_SIZE_X (540.0f)	//横の最大サイズ
#define MAX_BAR_RATIO (540.0f)	//バーの最大比率
#define INCDEC_COLOR_BAR (0.1f)	//色の増減値
#define SIZE_RATIO (MAX_SIZE_X / 4)	//テクスチャの割合での大きさ
#define MAX_COLOR_BAR (1.0f)	//色の最大値
#define MAX_FLASH_BAR (30)	//点滅の秒数

//=============================================================================
// インクルード
//=============================================================================
#include "caveatmark.h"
#include "texture.h"
#include "resource_manager.h"
#include "manager.h"
#include "mode_base.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CCaveatMark::CCaveatMark()
{
	m_state = NONE_STATE;
	m_nFrameCnt = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CCaveatMark::~CCaveatMark()
{

}

//=============================================================================
// 生成
//=============================================================================
CCaveatMark *CCaveatMark::Create(D3DXVECTOR3 pos)
{
	// CCaveatBarのポインタ
	CCaveatMark *pCaveat = nullptr;

	// nullcheck
	if (pCaveat == nullptr)
	{
		pCaveat = new CCaveatMark;// メモリ確保

		// !nullcheck
		if (pCaveat != nullptr)
		{
			pCaveat->Init(pos);	// 初期化処理
		}
	}
	// ポインタを返す
	return pCaveat;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CCaveatMark::Init(D3DXVECTOR3 pos)
{
	CScene2D::Init(pos, DEF_SIZE);

	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_CAVEAT));

	//色の設定
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================================================
// 更新
//=============================================================================
void CCaveatMark::Update(void)
{
	CScene2D::Update();

	//赤になった場合(Updateの所でしか動かないためここでやる)
	if (m_state == FLASH_STATE)
	{
		FlashCaveat(30);
	}
}

//=============================================================================
// 終了
//=============================================================================
void CCaveatMark::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 描画
//=============================================================================
void CCaveatMark::Drow(void)
{
	CScene2D::Draw();
}

//=============================================================================
// 色の状態変化
//=============================================================================
void CCaveatMark::ColorState(State state)
{
	m_state = state;
	switch (state)
	{
	case CCaveatMark::FADEIN_STATE:
		if (0.0f < GetColor().a)
		{
			GetColor().a -= 0.1f;
		}
		break;

		//通常
	case CCaveatMark::NORMAL_STATE:
		//色の設定
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;

	default:
		break;
	}
}
//====================================================================
// 警告マークの点滅
//====================================================================
void CCaveatMark::FlashCaveat(int nFlashFlame)
{
		m_nFrameCnt++;
		if (m_nFrameCnt < nFlashFlame/2)
		{
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else if (m_nFrameCnt > nFlashFlame/2)
		{
			SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		}
		if (m_nFrameCnt == nFlashFlame)
		{
			m_nFrameCnt = 0;
		}
}


