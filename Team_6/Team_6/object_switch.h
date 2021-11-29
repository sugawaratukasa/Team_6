#ifndef _OBJECT_SWITCH_H_
#define _OBJECT_SWITCH_H_
//=============================================================================
// スイッチクラス [object_wall.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"
#include "prison_cell_door.h"
//=============================================================================
// スイッチクラス
// Author : Sugawara Tsukasa
//=============================================================================
class CSwitch : public CObject
{
public:
	CSwitch(PRIORITY Priority = PRIORITY_MAP);				// コンストラクタ
	~CSwitch();												// デストラクタ

	static CSwitch*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CPrison_Cell_Door *pPrison_Cell_Door);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);													// 初期化処理
	void Uninit(void);																				// 終了処理
	void Update(void);																				// 更新処理
	void Draw(void);																				// 描画処理
	void Push(void);																				// ボタンを押す処理関数
private:
	CPrison_Cell_Door *m_pPrison_Cell_Door;	// 独房のドア
};
#endif