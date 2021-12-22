//=============================================================================
//
// タイトルロゴ処理 [logo.h]
// Author : 樋宮 匠
//
//=============================================================================

// 二重インクルード防止用
#ifndef _GUAGE_H_
#define _GUAGE_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TIMER_TEX_NUM 2

//*****************************************************************************
// タイトルロゴクラス定義
//*****************************************************************************
class CGauge
{
public:
	CGauge();
	~CGauge();
	HRESULT Init(void);
	void Update(void);
	void DrawStencil(void);
	void Draw(void);
	void Uninit(void);
	void CalcTime(void);
	void OnTimerOver(void);
	void SetIsStencil(bool bIsStencil) { m_bIsStencil = bIsStencil; }
	void SetAngle(float fAngle) { m_fAngle = fAngle; }
	int GetTime(void);
private:
	static LPDIRECT3DTEXTURE9		m_apTexture[TIMER_TEX_NUM];
	D3DXMATRIX			    m_mtxWorld;		// ワールドマトリックス
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;		// 頂点バッファー
	D3DXVECTOR3				m_pos;			// 座標
	D3DXVECTOR3				m_rot;			// 回転
	D3DXVECTOR3				m_scale;		// 拡大率
	D3DXCOLOR				m_col;
	float					m_fHeight;		// 高さ
	float					m_fWidth;		// 幅
	float					m_fAngle;		// 角度
	float					m_fRatio;       // タイマーの割合
	int						m_nTime;
	int						m_nRemainTime;  // 残り時間
	int						m_nElapsedTime;	// 経過時間
	bool					m_bIsStencil;	// ステンシル描画中かどうか
	bool					m_bTimer;		// タイマー用
};

#endif