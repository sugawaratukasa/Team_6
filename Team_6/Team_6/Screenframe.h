//=============================================================================
//
// タイトルロゴ処理 [logo.h]
// Author : 樋宮 匠
//
//=============================================================================

// 二重インクルード防止用
#ifndef _SCREEN_FRAME_H_
#define _SCREEN_FRAME_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"
#include "scene_2d.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_FRAME_TEX 3
#define FRAME_NORMAL 0
#define FRAME_SECCAM 1
#define FRAME_FUZZ   2
#define FRAME_CHANGE_LENGTH 30

//*****************************************************************************
// タイトルロゴクラス定義
//*****************************************************************************
class CScreenFrame :public CScene2D
{
public:
	CScreenFrame(PRIORITY Priority = PRIORITY_SCREENFRAME);
	~CScreenFrame();
	HRESULT Init(void);
	void Update(void);
	void Draw(void);
	void Uninit(void);
	void ChangeCamera(LPDIRECT3DTEXTURE9 pTex);
	static CScreenFrame * Create(void);
private:
	static LPDIRECT3DTEXTURE9		m_apTexture[MAX_FRAME_TEX];	 // テクスチャへのポインタ
	CScene2D *m_pScene2D;
	int m_nCountSec;
	bool m_bIsChanging;
	bool m_bUseSecCamOld;
	bool m_bIsEnableCam;
};

#endif