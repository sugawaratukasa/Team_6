#ifndef _DOOR_PC_ROOM_H_
#define _DOOR_PC_ROOM_H_
//=============================================================================
// PC室の扉 [door_pc_room.h]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// インクルード
// Author : Nikaido Taichi
//=============================================================================
#include "object_door.h"

//=============================================================================
// オブジェクトクラス
// Author : Nikaido Taichi
//=============================================================================
class CPCRoomDoor : public CDoor
{
public:
	CPCRoomDoor(PRIORITY Priority = PRIORITY_MODEL);				// コンストラクタ
	~CPCRoomDoor();													// デストラクタ
	static CPCRoomDoor *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
private:
};
#endif