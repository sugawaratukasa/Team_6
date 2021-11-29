#ifndef _GUARDS_DOOR_
#define _GUARDS_DOOR_
//=============================================================================
// 看守の扉 [guards_door.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "object_door.h"

//=============================================================================
// 看守の扉クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CGuards_Door : public CDoor
{
public:
	CGuards_Door(PRIORITY Priority = PRIORITY_MODEL);				// コンストラクタ
	~CGuards_Door();													// デストラクタ
	static CGuards_Door *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
private:
};
#endif