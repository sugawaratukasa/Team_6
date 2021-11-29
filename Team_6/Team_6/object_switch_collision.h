#ifndef _OBJECT_SWITCH_COLLISION_H_
#define _OBJECT_SWITCH_COLLISION_H_
//=============================================================================
// スイッチ判定クラス [object_switch_collision.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"
#include "object_switch.h"
//=============================================================================
// スイッチ判定クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CSwitch_Collision : public CObject
{
public:
	CSwitch_Collision(PRIORITY Priority = PRIORITY_MAP);								// コンストラクタ
	~CSwitch_Collision();																// デストラクタ

	static CSwitch_Collision*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,CSwitch *pSwitch);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);										// 初期化処理
	void Uninit(void);																	// 終了処理
	void Update(void);																	// 更新処理
	void Draw(void);																	// 描画処理
	void Push(void);																	// スイッチを押す関数
private:
	CSwitch *m_pSwitch;	// CSwitchのポインタ
};
#endif