#ifndef _ITEM_OBJECT_PC_STORAGE_KEY_H_
#define _ITEM_OBJECT_PC_STORAGE_KEY_H_
//=============================================================================
// PC室の鍵オブジェクト [item_object_pc_storage_key.h]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// インクルード
// Author : Nikaido Taichi
//=============================================================================
#include "item_object.h"

//=============================================================================
// PC室の鍵オブジェクトクラス
// Author : Nikaido Taichi
//=============================================================================
class CStorageKeyObject : public CItemObject
{
public:
	CStorageKeyObject(PRIORITY Priority = PRIORITY_MODEL);	// コンストラクタ
	virtual ~CStorageKeyObject();							// デストラクタ
	static CStorageKeyObject * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// 初期化処理
	void Uninit(void);										// 終了処理
	void Update(void);										// 更新処理
	void Draw(void);										// 描画処理
private:
};
#endif