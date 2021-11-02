#ifndef _ITEM_OBJECT_MAP_H_
#define _ITEM_OBJECT_MAP_H_
//=============================================================================
// マップオブジェクト [item_object_map.h]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// インクルード
// Author : Nikaido Taichi
//=============================================================================
#include "item_object.h"

//=============================================================================
// マップオブジェクトクラス
// Author : Nikaido Taichi
//=============================================================================
class CMapObject : public CItemObject
{
public:
	CMapObject(PRIORITY Priority = PRIORITY_MODEL);	// コンストラクタ
	virtual ~CMapObject();							// デストラクタ
	static CMapObject * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// 初期化処理
	void Uninit(void);										// 終了処理
	void Update(void);										// 更新処理
	void Draw(void);										// 描画処理
private:
};
#endif