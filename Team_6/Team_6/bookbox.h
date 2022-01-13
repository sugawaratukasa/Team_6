#ifndef _BOOKBOX_H_
#define _BOOKBOX_H_
//=============================================================================
// 本棚 [bookbox.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// 本棚クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CBookBox : public CObject
{
public:
	CBookBox(PRIORITY Priority = PRIORITY_MAP);					// コンストラクタ
	~CBookBox();													// デストラクタ
	static CBookBox*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
private:
};
#endif
