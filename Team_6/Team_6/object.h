#ifndef _OBJECT_H_
#define _OBJECT_H_
//=============================================================================
// オブジェクト [object.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "model.h"

//=============================================================================
// オブジェクトクラス
// Author : Sugawara Tsukasa
//=============================================================================
class CObject : public CModel
{
public:
	CObject(PRIORITY Priority = PRIORITY_MODEL);			// コンストラクタ
	~CObject();												// デストラクタ
	static CObject *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// 初期化処理
	void Uninit(void);										// 終了処理
	void Update(void);										// 更新処理
	void Draw(void);										// 描画処理
private:
};
#endif