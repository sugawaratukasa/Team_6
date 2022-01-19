//=============================================================================
// レバーマネージャー [lever_manager.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "lever_manager.h"
#include "textlog.h"
#include "texture.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define LEVER_CNT	(150)		// レバーカウント
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CLever_Manager::CLever_Manager(PRIORITY Priority)
{
	m_nLeverCnt = ZERO_INT;
	m_bOpen		= false;
	m_pLever1	= nullptr;
	m_pLever2	= nullptr;
}
//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CLever_Manager::~CLever_Manager()
{
}
//=============================================================================
// 生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
CLever_Manager * CLever_Manager::Create(CLever * pLever1, CLever * pLever2)
{
	// CLever_Managerのポインタ
	CLever_Manager *pLeverManager = nullptr;

	// nullcheck
	if (pLeverManager == nullptr)
	{
		// メモリ確保
		pLeverManager = new CLever_Manager;

		// !nullcheck
		if (pLeverManager != nullptr)
		{
			// ポインタ代入
			pLeverManager->m_pLever1 = pLever1;
			pLeverManager->m_pLever2 = pLever2;

			// 初期化
			pLeverManager->Init(ZeroVector3, ZeroVector3);
		}
	}
	// ポインタを返す
	return pLeverManager;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CLever_Manager::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CLever_Manager::Uninit(void)
{
	// ポインタ初期化
	if (m_pLever1 != nullptr)
	{
		// nullptr代入
		m_pLever1 = nullptr;
	}
	// ポインタ初期化
	if (m_pLever2 != nullptr)
	{
		// nullptr代入
		m_pLever2 = nullptr;
	}
	// 破棄処理
	Release();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CLever_Manager::Update(void)
{
	// 下がっているか取得
	bool bDown1 = m_pLever1->GetbDownLever();
	bool bDown2 = m_pLever2->GetbDownLever();

	// レバーが1が下がっている場合
	if (bDown1 == true && bDown2 == false)
	{
		// インクリメント
		m_nLeverCnt++;

		// 2.5秒を超えた場合
		if (m_nLeverCnt > LEVER_CNT)
		{
			// テキストログ生成
			CTextLog::Create(CTexture::TEXTURE_LOG_P1_NOT_SHUTTER_DOWN);

			// 0に戻す
			m_nLeverCnt = ZERO_INT;
		}
	}
	// レバーが1が下がっている場合
	if (bDown1 == false && bDown2 == true)
	{
		// インクリメント
		m_nLeverCnt++;

		// 2.5秒を超えた場合
		if (m_nLeverCnt > LEVER_CNT)
		{
			// 0に戻す
			m_nLeverCnt = ZERO_INT;

			// テキストログ生成
			CTextLog::Create(CTexture::TEXTURE_LOG_P2_NOT_SHUTTER_DOWN);
		}
	}
	// レバーが両方下がっているか
	if (bDown1 == true && bDown2 == true)
	{
		// ドアが開いていない場合
		if (m_bOpen == false)
		{
			// ドアが開いた事を設定する
			m_pLever1->SetOpen(true);

			m_pLever2->SetOpen(true);

			// テキストログ生成
			CTextLog::Create(CTexture::TEXTURE_LOG_P1_SHUTTER_DOWN);

			// テキストログ生成
			CTextLog::Create(CTexture::TEXTURE_LOG_P2_SHUTTER_DOWN);

			// trueに
			m_bOpen = true;
		}
	}
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CLever_Manager::Draw(void)
{
}