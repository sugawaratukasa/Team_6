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
// タイトルロゴクラス定義
//*****************************************************************************
class CScreenFrame :public CScene2D
{
public:
	CScreenFrame();
	~CScreenFrame();
	HRESULT Init(void);
	void Update(void);
	void Draw(void);
	void Uninit(void);
	static CScreenFrame * Create(void);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture;	 // テクスチャへのポインタ
};

#endif