#ifndef _LEVER_MANAGER_H_
#define _LEVER_MANAGER_H_
//=============================================================================
// レバーマネージャー [lever_manager.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "lever.h"
//=============================================================================
// 前方宣言
// Author : Sugawara Tsukasa
//=============================================================================
class CLever;
//=============================================================================
// ゴールの扉クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CLever_Manager : public CScene
{
public:
	CLever_Manager(PRIORITY Priority = PRIORITY_MODEL);				// コンストラクタ
	~CLever_Manager();												// デストラクタ
	static CLever_Manager *Create(CLever *pLever1, CLever *pLever2);// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
private:
	CLever *m_pLever1;		// CLeverのポインタ
	CLever *m_pLever2;		// CLeverのポインタ
	int m_nLeverCnt;		// カウント
	bool m_bOpen;			// 開いた判定
};
#endif