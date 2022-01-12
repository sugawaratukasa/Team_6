//=============================================================================
//
// 警告バー [caveat.cpp]
// Author : Oguma Akira
//
//=============================================================================

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_BER (20)
#define DEFAULT_SIZE (D3DXVECTOR3(0.0f, 100.0f, 0.0f))	//画像の大きさ
#define MAX_SIZE_X (500.0f)

//=============================================================================
// インクルード
//=============================================================================
#include "caveatbar.h"
#include "keyboard.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"
#include "player.h"
#include "jailer.h"
#include "manager.h"
#include "mode_base.h"
#include "jailer_spot.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CCaveatBar::CCaveatBar()
{
	m_fUp = 0;
	m_fVecLength = 0;
	m_nPlayerNum = 0;

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
	CCaveatBar *pCaveat = nullptr;

	// nullcheck
	if (pCaveat == nullptr)
	{	
		pCaveat = new CCaveatBar;// メモリ確保

		// !nullcheck
		if (pCaveat != nullptr)
		{
			pCaveat->m_nPlayerNum = nPlayer;
			pCaveat->Init(pos);	// 初期化処理
		}
	}
	// ポインタを返す
	return pCaveat;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CCaveatBar::Init(D3DXVECTOR3 pos)
{
	CScene2D::Init(pos, DEFAULT_SIZE);

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
	SizeMove(fVecLength);

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
// テクスチャサイズの動き
//=============================================================================
void CCaveatBar::SizeMove(const float fLength)
{
	//長さによってBarの長さを変える
	GetSize().x = fLength - MAX_SIZE_X;;
	SetSize(GetSize());

	if (GetSize().x > ZERO_INT)
	{
		GetSize().x = ZERO_FLOAT;
		SetSize(GetSize());
	}
}
