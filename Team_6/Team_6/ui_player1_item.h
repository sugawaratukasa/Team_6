#ifndef _UI_PLAYER1_ITEM_H_
#define _UI_PLAYER1_ITEM_H_
//=============================================================================
//
// プレイヤー1のアイテムUI [ui_player1_item.h]
// Author : Nikaido Taichi
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "ui_player_item.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// 前方宣言
//=============================================================================
class CScene2D;
class CSelectItemFlame;

//=============================================================================
// プレイヤークラス
//=============================================================================
class CPlayer1ItemUI :public CPlayerItemUI
{
public:
	CPlayer1ItemUI();											// コンストラクタ
	~CPlayer1ItemUI();											// デストラクタ
	static CPlayer1ItemUI * Create(void);
	HRESULT Init(void);											// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// プレイヤーの制御
private:
	void PlayerItemGet(void);									// 入力処理
	void ItemGetGuideUICreate(void);							// UI生成処理
	int m_nItemTextureCount;									// アイテムテクスチャ生成数
	int m_nSelectCount;											// アイテム選択のカウント
	CSelectItemFlame * m_pSelectItemFlame;						// アイテム選択枠のポインタ
	CScene2D * m_apItemTexture[CItemObject::ITEM_OBJECT_MAX];	// アイテムテクスチャのポインタ
};
#endif
