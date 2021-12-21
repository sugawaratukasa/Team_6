#ifndef _CONTROL_ROOM_DOOR_
#define _CONTROL_ROOM_DOOR_
//=============================================================================
// 制御室の扉 [control_room_door.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "object_door.h"

//=============================================================================
// 制御室の扉クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CControl_Room_Door : public CDoor
{
public:
	CControl_Room_Door(PRIORITY Priority = PRIORITY_MODEL);				// コンストラクタ
	~CControl_Room_Door();													// デストラクタ
	static CControl_Room_Door *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
private:
};
#endif