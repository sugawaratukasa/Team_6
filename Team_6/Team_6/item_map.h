#ifndef _ITEM_MAP_H_
#define _ITEM_MAP_H_
//=============================================================================
//
// 地図効果 [item_map.h]
// Author : Nikaido Taichi
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "item.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// 前方宣言
//=============================================================================
class CMapTexture;

//=============================================================================
// プレイヤークラス
//=============================================================================
class CItemMap : public CItem
{
public:
	CItemMap();
	~CItemMap();
	static CItemMap * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void ItemCreate(int nPlayer);
private:
	CMapTexture * m_pMapTexture;
};
#endif
