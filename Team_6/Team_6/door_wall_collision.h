#ifndef _DOOR_WALL_COLLISION_H_
#define _DOOR_WALL_COLLISION_H_
//=============================================================================
// ドアの壁の当たり判定用クラス [door_wall_collision.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// ドアの壁の当たり判定用クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CDoorWallCollision : public CObject
{
public:
	CDoorWallCollision(PRIORITY Priority = PRIORITY_MAP);					// コンストラクタ
	~CDoorWallCollision();													// デストラクタ
	static CDoorWallCollision *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);							// 初期化処理
	void Uninit(void);														// 終了処理
	void Update(void);														// 更新処理
	void Draw(void);														// 描画処理
private:
};
#endif