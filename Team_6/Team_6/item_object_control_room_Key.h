#ifndef _ITEM_OBJECT_CONTROL_ROOM_H_
#define _ITEM_OBJECT_CONTROL_ROOM_H_
//=============================================================================
// 制御室の鍵 [item_object_control_room.h]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// インクルード
// Author : Nikaido Taichi
//=============================================================================
#include "item_object.h"

//=============================================================================
// 前方宣言
// Author : Nikaido Taichi
//=============================================================================
class CParticle_Emitter;

//=============================================================================
// マップオブジェクトクラス
// Author : Nikaido Taichi
//=============================================================================
class CControlRoomKeyObject : public CItemObject
{
public:
	CControlRoomKeyObject(PRIORITY Priority = PRIORITY_MODEL);	// コンストラクタ
	virtual ~CControlRoomKeyObject();							// デストラクタ
	static CControlRoomKeyObject * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理
private:
	CParticle_Emitter * m_pParticleEmitter;
};
#endif