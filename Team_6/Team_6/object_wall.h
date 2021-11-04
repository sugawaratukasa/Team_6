#ifndef _OBJECT_WALL_H_
#define _OBJECT_WALL_H_
//=============================================================================
// 壁クラス [object_wall.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// 壁クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CWall : public CObject
{
public:
	CWall(PRIORITY Priority = PRIORITY_MODEL);				// コンストラクタ
	~CWall();												// デストラクタ
	static CWall*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// 初期化処理
	void Uninit(void);										// 終了処理
	void Update(void);										// 更新処理
	void Draw(void);										// 描画処理
private:
};
#endif