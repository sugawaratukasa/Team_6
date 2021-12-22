#ifndef _STORAGE_DOOR_
#define _STORAGE_DOOR_
//=============================================================================
// 倉庫の扉 [storage_door.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "object_door.h"

//=============================================================================
// 倉庫の扉クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CStorage_Door : public CDoor
{
public:
	CStorage_Door(PRIORITY Priority = PRIORITY_MAP);				// コンストラクタ
	~CStorage_Door();													// デストラクタ
	static CStorage_Door *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
private:
};
#endif
