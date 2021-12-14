#ifndef _LEVER_BODY_H_
#define _LEVER_BODY_H_
//=============================================================================
// レバーボディ [lever_body.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "model.h"

//=============================================================================
// レバーボディクラス
// Author : Sugawara Tsukasa
//=============================================================================
class CLever_Body : public CModel
{
public:
	CLever_Body(PRIORITY Priority = PRIORITY_MODEL);				// コンストラクタ
	~CLever_Body();													// デストラクタ

	static CLever_Body *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
private:
};
#endif