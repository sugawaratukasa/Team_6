//=============================================================================
//
// 説明背景 [guid_bg.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _GUID_BG_H_
#define _GUID_BG_H_

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
class CGuidBG :public CScene2D
{
public:
	CGuidBG(PRIORITY Priority = PRIORITY_GUID_TEXTURE);
	~CGuidBG();
	static CGuidBG * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
};
#endif