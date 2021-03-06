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
class CMap1Texture;
class CMap2Texture;

//=============================================================================
// プレイヤークラス
//=============================================================================
class CItemMap : public CItem
{
public:
	CItemMap();									// コンストラクタ
	~CItemMap();								// デストラクタ
	static CItemMap * Create(void);				// 生成処理
	HRESULT Init(void);							// 初期化処理
	void Uninit(void);							// 終了処理
	void Update(void);							// 更新処理
	void ItemCreate(int nPlayer);				// アイテム生成処理
	void DuctPass(D3DXVECTOR3 pos);				// ダクト受け渡し処理
private:
	void PlayerItemGet(void);					// プレイヤーアイテム取得状況取得処理
	void MapCreate(int nPlayer, bool bItem);	// マップテクスチャ生成処理
	bool m_abCreateMap[MAX_PLAYER];				// マップテクスチャ生成状態
	CMap1Texture * m_pMap1Texture;				// マップ1テクスチャのポインタ
	CMap2Texture * m_pMap2Texture;				// マップ2テクスチャのポインタ
};
#endif
