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

//=============================================================================
// コンストラクタ
//=============================================================================
CCaveatBar::CCaveatBar()
{
	m_fUp = 0;
	m_fVecLength = 0;
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
CCaveatBar *CCaveatBar::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
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
			pCaveat->Init(pos, size);	// 初期化処理
		}
	}
	// ポインタを返す
	return pCaveat;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CCaveatBar::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);

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
	// キーボード取得
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	for (int nCntPlayer = ZERO_INT; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		////プレイヤー情報の取得
		CPlayer *pPlayer = CManager::GetModePtr()->GetPlayer(nCntPlayer);
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
		float fPlayerVec = ((PlayerPos.x * PlayerPos.x) + (PlayerPos.z * PlayerPos.z));
		for (int nCntPlayer = ZERO_INT; nCntPlayer < MAX_PLAYER; nCntPlayer++)
		{
			if (m_fUp >= 10.0f)
			{
				m_fUp = 0.0;
				GetSize().x = 0.0f;
				SetSize(GetSize());
			}
			else if (pKeyboard->GetPress(DIK_NUMPADENTER))
			{
				m_fUp += 0.1;
				//バーのサイズ変更
				GetSize().x += m_fUp;
				SetSize(GetSize());
			}
		}
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
