#ifndef _LEVER_H_
#define _LEVER_H_
//=============================================================================
// レバー [レバー.h]
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
class CLever_Handle;
//=============================================================================
// ドアの判定クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CLever : public CDoor_Collision
{
public:
	CLever(PRIORITY Priority = PRIORITY_OBJ_COLLISION);						// コンストラクタ
	~CLever();																// デストラクタ

	static CLever *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);							// 初期化処理
	void Uninit(void);														// 終了処理
	void Update(void);														// 更新処理
	void Draw(void);														// 描画処理
	void LeverCrate(D3DXVECTOR3 pos, D3DXVECTOR3 rot);						// レバー生成処理
	void DownLever(void);													// レバーを下げる処理
private:
	CDoor *m_pDoor;					// CDoorのポインタ
	CLever_Handle *m_pLever_Handle;	// CLever_Handleのポインタ
};
#endif