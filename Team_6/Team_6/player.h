#ifndef _PLAYER_H_
#define _PLAYER_H_
//=============================================================================
//
// プレイヤークラスヘッダー [player.h]
// Author : Nikaido Taichi
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "character.h"
#include "model_anime.h"
#include "item_object.h"


//=============================================================================
// マクロ定義
//=============================================================================
#define ANGLE_45                (D3DXToRadian(45.0f))                    // 角度45
#define ANGLE_90                (D3DXToRadian(90.0f))                    // 角度90
#define ANGLE_135                (D3DXToRadian(135.0f))                  // 角度90
#define ANGLE_180                (D3DXToRadian(180.0f))                  // 角度180
#define ANGLE_270                (D3DXToRadian(270.0f))                  // 角度270
#define PLAYER_ROT_SPEED        (1.0f)                                   // キャラクターの回転する速度

#define INCAPACITATED_TIME		(1200)									 // 行動不能時間
#define MAX_PLAYER (2)													 // プレイヤーの最大数
#define MAX_ITEM (3)													 // プレイヤーが取得できるアイテムの最大数

//=============================================================================
// 前方宣言
//=============================================================================
class CItemGetUI;
class CItem;

class CPlayerItemUI;

//=============================================================================
// プレイヤークラス
//=============================================================================
class CPlayer : public CCharacter
{
public:
	//=============================================================================
	//　モーション状態の列挙型
	//=============================================================================
	enum MOTION_STATE
	{
		MOTION_NONE = -1,
		MOTION_IDOL,				// アイドルモーション
		MOTION_WALK,				// 歩行モーション
		MOTION_MAX					// モーション最大数
	};
	enum ITEM_GET_LIST
	{
		ITEM_NONE = -1,
		ITEM_KEY_STORAGE,			// 倉庫の鍵
		ITEM_KEY_JAILER_ROOM,		// 看守室の鍵
		ITEM_KEY_CONTROL_ROOM,		// 制御室の鍵
		ITEM_KEY_ELECTRICAL,		// 電源室の鍵
		ITEM_KEY_PC_ROOM,			// PC室の鍵
		ITEM_BATON,					// 警棒
		ITEM_MAP,					// マップ
		ITEM_MAX
	};
	enum TYPE
	{
		PLAYER_NONE = -1,
		PLAYER_1,
		PLAYER_2,
	};
	CPlayer(PRIORITY Priority = PRIORITY_CHARACTER);				// コンストラクタ
	~CPlayer();														// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// プレイヤーの制御
	void Draw(void);												// 描画処理
	void ItemEffectCreate(int ItemGetList);							// アイテム効果処理
	void ItemEffectUninit(void);									// アイテム効果削除処理
	void ItemDelete(int nPlayer);									// アイテム削除処理
	void MapCollision(void);										// マップとの当たり判定

	virtual void KeyboardMove(float fSpeed, float fAngle) = 0;		// キーボード移動処理
	virtual void PadMove(float fSpeed, float fAngle) = 0;			// ジョイパッド移動処理
	virtual void PrisonWarp(void) = 0;								// 独房ワープ処理
	virtual void SetbGuidCreate(CItemObject::ITEM_OBJECT_LIST Type) = 0;							// アイテム説明テクスチャ生成処理
	void DoorOpen(void);											// 扉を開く処理
	//=============================================================================
	//　Set関数
	//=============================================================================

	void SetAddbGetItem(int nItem, bool bGet);											// アイテムの取得状況を設定
	void SetSubbGetItem(int nItem, bool bGet);											// アイテムの取得状況を設定
	void SetUI(CPlayerItemUI * pUI) { m_pUI = pUI; }									// UI設定
	void SetbGoal(bool bGoal) { m_bGoal = bGoal; }										// ゴール状態設定
	void SetbIncapacitated(bool bIncapacitated) { m_bIncapacitated = bIncapacitated; }	// 行動不能状態設定
	void SetbItemGuidCreate(bool bGuid) { m_bGuidCreate = bGuid; }						// アイテム説明テクスチャの生成状態
	//=============================================================================
	//　Get関数
	//=============================================================================
	int GetItemCount(void) { return m_nItemCount; }								// アイテムの取得数所得関数
	bool GetbItem(int nItem) { return m_abGetItem[nItem]; }						// アイテムの取得状況取得関数
	bool GetbGoal(void) { return m_bGoal; }										// ゴール状態所得関数
	bool GetbIncapacitated(void) { return m_bIncapacitated; }					// 行動不能状態取得関数
	int GetIncapacitatedTimeCount(void) { return m_nIncapacitatedTimeCount; }	// 行動不能カウント取得
	bool GetbGuidCreate(void) { return m_bGuidCreate; }							// アイテム説明テクスチャの生成状態取得関数
	TYPE GetType(void) { return m_Type; }
private:

	int m_nItemCount;						// アイテムの所持数
	int m_nItemSortCount;					// アイテムソート用カウント
	int m_nIncapacitatedTimeCount;			// 行動不能時間カウント
	bool m_bGoal;							// ゴール状態
	bool m_bIncapacitated;					// 行動不能状態
	bool m_abGetItem[ITEM_MAX];				// アイテムを取得してるか
	bool m_bItempCreate[ITEM_MAX];			// アイテムポインタ生成したか
	bool m_bUICreate[ITEM_MAX];				// UI生成状態
	bool m_bGuidCreate;
	TYPE m_Type;
	CItemGetUI * m_pItemGetUI[ITEM_MAX];	// UIのポインタ
	CPlayerItemUI * m_pUI;					// UIポインタ
	CItem * m_pItem[3];						// アイテムポインタ
};
#endif
