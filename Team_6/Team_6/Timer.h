//=============================================================================
//
// タイマー処理 [timer.h]
// Author : 樋宮 匠
//
//=============================================================================

// 二重インクルード防止用
#ifndef _TIMER_H_
#define _TIMER_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"
#include "scene_2d.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"
#include "Guage.h"
#include "Number.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TIMER_POS D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 30.0f, 0.0f)
#define TIMER_SIZE D3DXVECTOR3(250.0f, 250.0f, 250.0f)
#define TIMER_MINIT 6
#define TIMER_LENGTH (60 * TIMER_MINIT)
#define TIMER_ANGLE 180.0f
#define TIMER_NUM_POS D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 40.0f, 0.0f)

//*****************************************************************************
// タイトルロゴクラス定義
//*****************************************************************************
class CTimer : public CScene2D
{
public:
	CTimer(PRIORITY = PRIORITY_UI);
	~CTimer();

	HRESULT Init(void);
	void Update(void);
	void Draw(void);
	void Uninit(void);
	static CTimer * Create(void);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture;	 // テクスチャへのポインタ
	CGauge *m_pGuage;
	CNumber *m_pNumber;
};

#endif