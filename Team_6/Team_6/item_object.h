#ifndef _ITEM_OBJECT_H_
#define _ITEM_OBJECT_H_
//=============================================================================
// アイテムオブジェクト [item_object.h]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// インクルード
// Author : Nikaido Taichi
//=============================================================================
#include "model.h"

//=============================================================================
// オブジェクトクラス
// Author : Nikaido Taichi
//=============================================================================
class CItemObject : public CScene
{
public:
	enum ITEM_OBJECT_LIST
	{
		ITEM_OBJECT_NONE = -1,
		ITEM_OBJECT_KEY_STORAGE,
		ITEM_OBJECT_KEY_JAILER_ROOM,
		ITEM_OBJECT_KEY_CONTOROL_ROOM,
		ITEM_OBJECT_KEY_ELECTRICAL_ROOM,
		ITEM_OBJECT_KEY_PC_ROOM,
		ITEM_OBJECT_BATON,
		ITEM_OBJECT_MAP,
		ITEM_OBJECT_MAX
	};
	CItemObject(PRIORITY Priority = PRIORITY_MODEL);	// コンストラクタ
	virtual ~CItemObject();								// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理
	void Draw(void);									// 描画処理
	//=============================================================================
	//　Set関数
	//=============================================================================
	void SetPos(D3DXVECTOR3 Pos) { m_Position = Pos; }
	void SetSize(D3DXVECTOR3 Size) { m_Size = Size; }
	void SetType(ITEM_OBJECT_LIST Type) { m_Type = Type; }
	//=============================================================================
	//　Get関数
	//=============================================================================
	D3DXVECTOR3 GetPos(void) { return m_Position; }
	D3DXVECTOR3 GetSize(void) { return m_Size; }
	ITEM_OBJECT_LIST GetType(void) { return m_Type; }
private:
	void Collision(void);		// 衝突処理
	D3DXVECTOR3 m_Position;		// 位置
	D3DXVECTOR3 m_Size;			// サイズ
	D3DXVECTOR3 m_Rotation;		// 向き
	ITEM_OBJECT_LIST m_Type;	// 種類
};
#endif