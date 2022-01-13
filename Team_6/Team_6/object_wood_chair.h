#ifndef _OBJECT_WOOD_CHAIR_H_
#define _OBJECT_WOOD_CHAIR_H_
//=============================================================================
// 木の椅子 [object_wood_chair.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// 木の椅子クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CWood_Chair : public CObject
{
public:
	CWood_Chair(PRIORITY Priority = PRIORITY_MAP);					// コンストラクタ
	~CWood_Chair();													// デストラクタ
	static CWood_Chair*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
private:
};
#endif