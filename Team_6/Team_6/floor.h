//=============================================================================
// 床 [floor.h]
// Author : Sugawara Tsukasa
//=============================================================================
#ifndef _FLOOR_H_
#define _FLOOR_H_
//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "scene3D.h"
//=============================================================================
// マップクラス
// Author : Sugawara Tsukasa
//=============================================================================
class CFloor : public CScene3D
{
public:
	CFloor(PRIORITY Priority = PRIORITY_1);					// コンストラクタ
	~CFloor();													// デストラクタ
	static CFloor *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理
private:
};
#endif