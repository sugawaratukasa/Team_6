#ifndef _LOCKER_H_
#define _LOCKER_H_
//=============================================================================
// ロッカー [locker.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// ロッカークラス
// Author : Sugawara Tsukasa
//=============================================================================
class CLocker : public CObject
{
public:
	CLocker(PRIORITY Priority = PRIORITY_MAP);					// コンストラクタ
	~CLocker();													// デストラクタ
	static CLocker*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
private:
};
#endif
