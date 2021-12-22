#ifndef _GOAL_DOOR_H_
#define _GOAL_DOOR_H_
//=============================================================================
// ゴールの扉 [goal_door.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "object_door.h"
#include "lever.h"
//=============================================================================
// 前方宣言
// Author : Sugawara Tsukasa
//=============================================================================
class CLever;
//=============================================================================
// ゴールの扉クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CGoal_Door : public CDoor
{
public:
	CGoal_Door(PRIORITY Priority = PRIORITY_MODEL);													// コンストラクタ
	~CGoal_Door();																					// デストラクタ
	static CGoal_Door *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CLever *pLever1, CLever *pLever2);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);													// 初期化処理
	void Uninit(void);																				// 終了処理
	void Update(void);																				// 更新処理
	void Draw(void);																				// 描画処理
	void Open(void);																				// 開く処理
	void Close(void);																				// 閉じる処理
private:
	CLever *m_pLever1;	// CLeverのポインタ
	CLever *m_pLever2;	// CLeverのポインタ
	D3DXVECTOR3 m_InitPos;	// 初期位置
};
#endif