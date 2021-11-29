//=============================================================================
//
// タイトル背景 [bg_title.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _TITLE_BG_H_
#define _TITLE_BG_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene_2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTitleBG :public CScene2D
{
public:
	CTitleBG(PRIORITY Priority = PRIORITY_UI);
	~CTitleBG();
	static CTitleBG * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
};
#endif