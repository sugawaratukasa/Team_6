#ifndef _ITEM_OBJECT_ELECTRICAL_ROOM_KEY_H_
#define _ITEM_OBJECT_ELECTRICAL_ROOM_KEY_H_
//=============================================================================
// 電気室の鍵 [item_object_electrical_room_key.h]
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
class CElectricalRoomKeyObject : public CItemObject
{
public:
	CElectricalRoomKeyObject(PRIORITY Priority = PRIORITY_MODEL);		// コンストラクタ
	virtual ~CElectricalRoomKeyObject();								// デストラクタ
	static CElectricalRoomKeyObject * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理
private:
	CParticle_Emitter * m_pParticleEmitter;
};
#endif