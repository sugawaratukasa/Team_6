#ifndef _MODE_RANKING_H_
#define _MODE_RANKING_H_
//=============================================================================
//
// ランキングクラス [mode_ranking.h]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "mode_base.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// 前方宣言
//=============================================================================
class CRanking;
//=============================================================================
// クラス定義
//=============================================================================
class CMode_Ranking : public CModeBase
{
public:
	CMode_Ranking();					// コンストラクタ
	~CMode_Ranking();					// デストラクタ

	HRESULT Init(void);			// 初期化処理
	void Uninit(void);			// 終了処理
	void Update(void);			// 更新処理
	void Draw(void);			// 描画処理
	void RankingCreate(void);	// ランキングの生成関数
	void ModeTransition(void);	// 遷移
private:
	CRanking *m_pRankig;	// ランキングのポインタ
	bool m_bIsPlayedMovie;
};
#endif