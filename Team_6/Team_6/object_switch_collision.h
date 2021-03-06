#ifndef _SWITCH_COLLISON_H_
#define _SWITCH_COLLISON_H_
//=============================================================================
// スイッチ判定 [switch_collision.h]
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
class CSwitch;
//=============================================================================
// ドアの判定クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CSwitch_Collision : public CDoor_Collision
{
public:
	CSwitch_Collision(PRIORITY Priority = PRIORITY_OBJ_COLLISION);							// コンストラクタ
	~CSwitch_Collision();																	// デストラクタ

	static CSwitch_Collision *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CSwitch *pSwitch);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);											// 初期化処理
	void Uninit(void);																		// 終了処理
	void Update(void);																		// 更新処理
	void Draw(void);																		// 描画処理
	void Open(void);																		// 独房のドアを開く
private:
	CSwitch *m_pSwitch;	// CSwitchのポインタ
};
#endif