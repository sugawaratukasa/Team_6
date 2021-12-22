//=============================================================================
// タイム [time.h]
// Author : SugawaraTsukasa
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

//*****************************************************************************
// インクルードファイル
// Author : SugawaraTsukasa
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "scene_2d.h"
//*****************************************************************************
// マクロ定義
// Author : SugawaraTsukasa
//*****************************************************************************
#define MAX_TIME	(4)	// タイムの最大数
//*****************************************************************************
// 前方宣言
// Author : SugawaraTsukasa
//*****************************************************************************
class CScene2D;
//*****************************************************************************
// タイムクラス
// Author : SugawaraTsukasa
//*****************************************************************************
class CTime : public CScene
{
public:
	CTime();												// コンストラクタ
	~CTime();												// デストラクタ
	static CTime *Create(D3DXVECTOR3 pos);					// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// 初期化処理
	void Uninit(void);										// 終了処理
	void Update(void);										// 更新処理
	void Draw(void);										// 描画処理
	void SetTime(int nTime);							// ナンバー設定
private:
	void CreateTime(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// タイム生成
	CScene2D *m_apTime[MAX_TIME];							// CScene_2Dのポインタ配列
	CScene2D *m_pColon;										// CScene_2Dのポインタ
};

#endif