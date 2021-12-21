#ifndef _ITEM_OBJECT_BATON_H_
#define _ITEM_OBJECT_BATON_H_
//=============================================================================
// 警棒オブジェクト [item_object_baton.h]
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
// 警棒オブジェクトクラス
// Author : Nikaido Taichi
//=============================================================================
class CBatonObject : public CItemObject
{
public:
	CBatonObject(PRIORITY Priority = PRIORITY_MODEL);		// コンストラクタ
	virtual ~CBatonObject();								// デストラクタ
	static CBatonObject * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// 初期化処理
	void Uninit(void);										// 終了処理
	void Update(void);										// 更新処理
	void Draw(void);										// 描画処理
private:
	CParticle_Emitter * m_pParticleEmitter;
};
#endif