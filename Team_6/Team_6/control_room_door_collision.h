#ifndef _CONTROL_ROOM_DOOR_COLLISON_H_
#define _CONTROL_ROOM_DOOR_COLLISON_H_
//=============================================================================
// 制御室の判定 [control_room_door_collision.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "model.h"
#include "door_collision.h"
//=============================================================================
// 前方宣言
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// 制御室の判定クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CControl_Room_Door_Collision : public CDoor_Collision
{
public:
	CControl_Room_Door_Collision(PRIORITY Priority = PRIORITY_OBJ_COLLISION);						// コンストラクタ
	~CControl_Room_Door_Collision();																// デストラクタ

	static CControl_Room_Door_Collision *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CDoor *pDoor);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);													// 初期化処理
	void Uninit(void);																				// 終了処理
	void Update(void);																				// 更新処理
	void Draw(void);																				// 描画処理
	void Open(int nPlayer);																			// 開く処理
	void NotOpen(int nPlayer);																		// 扉が開けない処理
private:
};
#endif