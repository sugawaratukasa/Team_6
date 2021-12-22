//=============================================================================
// タイム [time.h]
// Author : SugawaraTsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : SugawaraTsukasa
//=============================================================================
#include "time.h"
#include "scene_2d.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"
//=============================================================================
// マクロ定義
// Author : SugawaraTsukasa
//=============================================================================
#define DIVIDE			(10.0f)							// 割る数
#define SIZE_VALUE		(D3DXVECTOR3(50.0f,50.0f,0.0f))	// サイズ量
#define TEX_SEPARATE	(11)							// テクスチャ分割数
//=============================================================================
// コンストラクタ
// Author : SugawaraTsukasa
//=============================================================================
CTime::CTime()
{
	memset(m_apTime, NULL, sizeof(m_apTime));
	m_pColon = nullptr;
}
//=============================================================================
// デストラクタ
// Author : SugawaraTsukasa
//=============================================================================
CTime::~CTime()
{
}
//=============================================================================
// 生成処理関数
// Author : SugawaraTsukasa
//=============================================================================
CTime * CTime::Create(D3DXVECTOR3 pos)
{
	// CTimeのポインタ
	CTime *pTime = nullptr;

	// nullceck
	if (pTime == nullptr)
	{
		// メモリ確保
		pTime = new CTime;

		// !nullcheck
		if (pTime != nullptr)
		{
			// 初期化
			pTime->Init(pos, SIZE_VALUE);
		}
	}
	// ポインタを返す
	return pTime;
}
//=============================================================================
// 初期化処理関数
// Author : SugawaraTsukasa
//=============================================================================
HRESULT CTime::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 生成
	CreateTime(pos, size);

	// タイム設定
	SetTime(0);
	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : SugawaraTsukasa
//=============================================================================
void CTime::Uninit(void)
{
	// 破棄
	if (m_pColon != nullptr)
	{
		// 破棄
		m_pColon->Uninit();

		// nullptr代入
		m_pColon = nullptr;
	}
	// 最大数繰り返す
	for (int nCnt = ZERO_INT; nCnt < MAX_TIME; nCnt++)
	{
		// 破棄
		if (m_apTime[nCnt] != nullptr)
		{
			// 破棄
			m_apTime[nCnt]->Uninit();

			// nullptr代入
			m_apTime[nCnt] = nullptr;
		}
	}
}
//=============================================================================
// 更新処理関数
// Author : SugawaraTsukasa
//=============================================================================
void CTime::Update(void)
{
	// 最大数繰り返す
	for (int nCnt = ZERO_INT; nCnt < MAX_TIME; nCnt++)
	{
		// !nullcheck
		if (m_apTime[nCnt] != nullptr)
		{
			m_apTime[nCnt]->SetVertex();
		}
	}
}
//=============================================================================
// 描画処理関数
// Author : SugawaraTsukasa
//=============================================================================
void CTime::Draw(void)
{
}
//=============================================================================
// タイム設定
// Author : SugawaraTsukasa
//=============================================================================
void CTime::SetTime(int nTime)
{
	// 計算用変数
	int nInteger = ZERO_INT;

	// カウント
	int nCntNumber = ZERO_INT;

	// ナンバー
	int nNum = ZERO_INT;

	// 最大数分繰り返す
	for (int nCntDigit = 1; nCntDigit <= MAX_TIME; nCntDigit++, nCntNumber++)
	{
		// 1の位以下を切り捨てる
		nInteger = int(nTime / std::pow(DIVIDE, nCntDigit));
		nInteger = int(nInteger * std::pow(DIVIDE, nCntDigit));
		nNum = int((nTime - nInteger) / std::pow(DIVIDE, nCntDigit - 1));

		// スコアを設定
		m_apTime[nCntNumber]->InitAnimation(nNum, TEX_SEPARATE, 0);
	}
}
//=============================================================================
// タイム生成
// Author : SugawaraTsukasa
//=============================================================================
void CTime::CreateTime(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// タイム生成
	for (int nCnt = ZERO_INT; nCnt < MAX_TIME; nCnt++)
	{
		//	位置
		D3DXVECTOR3 Pos = pos;

		if (nCnt > 1)
		{
			// 位置計算
			Pos.x -= (size.x * (1 + nCnt));
		}
		else
		{
			// 位置計算
			Pos.x -= (size.x * nCnt);

		}

		// 生成
		m_apTime[nCnt] = CScene2D::Create(Pos, size);

		// テクスチャの設定
		CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
		m_apTime[nCnt]->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_RANKING_NUMBER));
	}
	pos.x -= size.x * 2;
	m_pColon = CScene2D::Create(pos, size);

	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	m_pColon->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_RANKING_NUMBER));

	// スコアを設定
	m_pColon->InitAnimation(10, TEX_SEPARATE, 0);
}