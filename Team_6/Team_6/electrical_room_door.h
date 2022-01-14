#ifndef _ELETRICAL_ROOM_DOOR_H_
#define _ELETRICAL_ROOM_DOOR_H_
//=============================================================================
// 電気室のドア [electrical_room_door.h]
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
class CElectrical_Room_Door : public CDoor
{
public:
	CElectrical_Room_Door(PRIORITY Priority = PRIORITY_MAP);								// コンストラクタ
	~CElectrical_Room_Door();															// デストラクタ
	static CElectrical_Room_Door *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, SIDE side);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);										// 初期化処理
	void Uninit(void);																	// 終了処理
	void Update(void);																	// 更新処理
	void Draw(void);																	// 描画処理
private:
};
#endif