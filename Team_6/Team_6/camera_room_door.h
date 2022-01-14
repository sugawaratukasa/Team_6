#ifndef _CAMERA_ROOM_DOOR_H_
#define _CAMERA_ROOM_DOOR_H_
//=============================================================================
// カメラ室のドア [camera_room_door.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "object_door.h"

//=============================================================================
// ドア用の壁クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CCamera_Room_Door : public CDoor
{
public:
	CCamera_Room_Door(PRIORITY Priority = PRIORITY_MAP);							// コンストラクタ
	~CCamera_Room_Door();															// デストラクタ
	static CCamera_Room_Door *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, SIDE side);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);									// 初期化処理
	void Uninit(void);																// 終了処理
	void Update(void);																// 更新処理
	void Draw(void);																// 描画処理
private:
};
#endif#pragma once
