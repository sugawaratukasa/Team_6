//========================================================================
// ランキングクラス[ranking.cpp]
// Author : Sugawara Tsukasa
//========================================================================
//========================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//========================================================================
#include "ranking.h"
#include "ranking_bg.h"
#include "time.h"
//========================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//========================================================================
#define POS	(D3DXVECTOR3(SCREEN_WIDTH / 2 + 160.0f,180.0f + 87* nCnt,0.0f))	// タイム位置
#define MOVE_RANKING	(1)													// 順位移動
#define RANKIG_TEXT		("data/Text/Ranking/Ranking.txt")					// ランキングテキスト
#define SIZE_VALUE		(D3DXVECTOR3(50.0f,50.0f,0.0f))						// サイズ量
//========================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//========================================================================
CRanking::CRanking()
{
	memset(m_apTime, NULL, sizeof(m_apTime));
	memset(m_anTime, ZERO_INT, sizeof(m_anTime));
	m_nPlayerTime = ZERO_INT;
	m_Type = TYPE_RANKING_RESULT;
}
//========================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//========================================================================
CRanking::~CRanking()
{
}
//========================================================================
// 生成処理関数
// Author : Sugawara Tsukasa
//========================================================================
CRanking * CRanking::Create(TYPE type)
{
	// CRankingのポインタ
	CRanking *pRanking = nullptr;

	// nullcheck
	if (pRanking == nullptr)
	{
		// メモリ確保
		pRanking = new CRanking;

		// !nullcheck
		if (pRanking != nullptr)
		{
			// タイプ代入
			pRanking->m_Type = type;

			// 初期化処理
			pRanking->Init(ZeroVector3, ZeroVector3);
		}
	}
	// ポインタを返す
	return pRanking;
}
//========================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//========================================================================
HRESULT CRanking::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{	
	// リザルト時にだす場合
	if (m_Type == TYPE_RANKING_RESULT)
	{
		// 読み込み
		ReadPlayerFile();

		// ランキング設定
		SetRanking(m_nPlayerTime);
	}
	// ファイル読み込み
	ReadFile();

	// タイム生成
	CreateTime();
	return S_OK;
}
//========================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//========================================================================
void CRanking::Uninit(void)
{
	// 最大数繰り返す
	for (int nCnt = ZERO_INT; nCnt < RANK_MAX; nCnt++)
	{
		// !nullcheck
		if (m_apTime[nCnt] != nullptr)
		{
			// 終了
			m_apTime[nCnt]->Uninit();

			// nullptr代入
			m_apTime[nCnt] = nullptr;
		}
	}
	// 終了
	Release();
}
//========================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//========================================================================
void CRanking::Update(void)
{
}
//========================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//========================================================================
void CRanking::Draw(void)
{
}
//========================================================================
// プレイヤーのタイムテキスト読み込み
// Author : Sugawara Tsukasa
//========================================================================
void CRanking::ReadPlayerFile(void)
{
	FILE * pFile;
	// ファイルの読み込み
	pFile = fopen("data/Text/Time/Player_Time.txt", "r");

	// ファイルが空じゃないか
	if (pFile != NULL)
	{
		// 読み込み
		fscanf(pFile, "%d\n", &m_nPlayerTime);
		// ファイルを閉じる
		fclose(pFile);
	}
}
//========================================================================
// テキスト読み込み
// Author : Sugawara Tsukasa
//========================================================================
void CRanking::ReadFile(void)
{
	// ファイルのポインタ
	FILE * pFile;
	// ファイルの読み込み
	pFile = fopen(RANKIG_TEXT, "r");
	// ファイルが空じゃないか
	if (pFile != NULL)
	{
		// 読み込み
		for (int nCnt = ZERO_INT; nCnt < RANK_MAX; nCnt++)
		{
			fscanf(pFile, "%d\n", &m_anTime[nCnt]);
		}
		// ファイルを閉じる
		fclose(pFile);
	}
}
//========================================================================
// テキスト書き込み
// Author : Sugawara Tsukasa
//========================================================================
void CRanking::WriteFile(void)
{
	// ファイルポインタ
	FILE * pFile;
	// ファイルの書き出し
	pFile = fopen(RANKIG_TEXT, "w");
	// ファイルが空じゃないか
	if (pFile != NULL)
	{
		// 書き込み
		for (int nCnt = ZERO_INT; nCnt < RANK_MAX; nCnt++)
		{
			fprintf(pFile, "%d\n", m_anTime[nCnt]);
		}
		// ファイルを閉じる
		fclose(pFile);
	}
}
//========================================================================
// ランキング設定
// Author : Sugawara Tsukasa
//========================================================================
void CRanking::SetRanking(int nTime)
{
	// ランキングの最大数繰り返す
	for (int nCount = ZERO_INT; nCount < RANK_MAX; nCount++)
	{
		// ランキングを更新する場所判定
		if (m_anTime[nCount] == ZERO_INT || nTime < m_anTime[nCount])
		{
			// 以降のランキングデータを後ろに移動
			for (int nCntMove = RANK_MAX - MOVE_RANKING; nCntMove > nCount; nCntMove--)
			{
				m_anTime[nCntMove] = m_anTime[nCntMove - MOVE_RANKING];
			}
			// 代入
			m_anTime[nCount] = nTime;
			break;
		}
	}
	// ファイル書き込み
	WriteFile();
}
//========================================================================
// タイム生成処理関数
// Author : Sugawara Tsukasa
//========================================================================
void CRanking::CreateTime(void)
{
	// ランキングの最大数まで繰り返す
	for (int nCnt = ZERO_INT; nCnt < RANK_MAX; nCnt++)
	{
		// タイム生成
		m_apTime[nCnt] = CTime::Create(POS, SIZE_VALUE);

		// タイム設定
		m_apTime[nCnt]->SetTime(m_anTime[nCnt]);
	}
}
