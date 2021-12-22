//========================================================================
// ランキングクラス[ranking.h]
// Author : Sugawara Tsukasa
//========================================================================
//========================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//========================================================================
#include "main.h"
#include "scene.h"
//========================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//========================================================================
//========================================================================
// 前方宣言
// Author : Sugawara Tsukasa
//========================================================================
class CTime;
//========================================================================
// ランキングクラス
// Author : Sugawara Tsukasa
//========================================================================
class CRanking : public CScene
{
public:
	enum Rank
	{
		RANK_NONE = -1,
		RANK_1TH,
		RANK_2TH,
		RANK_3TH,
		RANK_4TH,
		RANK_5TH,
		RANK_6TH,
		RANK_MAX
	};

	enum TYPE
	{
		TYPE_RANKING_BOARD = 0,
		TYPE_RANKING_RESULT
	};

	CRanking();						// コンストラクタ
	~CRanking();					// デストラクタ

	static CRanking *Create(TYPE type);				// 生成処理

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 初期化処理
	void Uninit(void);								// 終了処理
	void Update(void);								// 更新処理 
	void Draw(void);								// 描画処理
private:
	void ReadPlayerFile(void);		// プレイヤーのテキスト読み込み
	void ReadFile(void);			// 読み込み
	void WriteFile(void);			// 書き込み
	void SetRanking(int nTime);		// タイム
	void CreateTime(void);			// タイム生成

	CTime *m_apTime[RANK_MAX];		// タイムのポインタ配列
	int m_anTime[RANK_MAX];			// タイムの配列
	int m_nPlayerTime;				// プレイヤーのタイム
	TYPE m_Type;					// タイプ
};