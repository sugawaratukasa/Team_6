#ifndef _PLAYER_H_
#define _PLAYER_H_
//=============================================================================
//
// プレイヤークラスヘッダー [player.h]
// Author : Sugawara Tsukasa
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
#define PLAYER_ROT_SPEED        (0.1f)                                   // キャラクターの回転する速度
#define PLAYER_SPEED            (50.0f)                                  // プレイヤーの移動量
#define INCAPACITATED_TIME		(1200)									 // 行動不能時間
#define MAX_PLAYER (2)
#define MAX_ITEM (3)

//=============================================================================
// 前方宣言
//=============================================================================
class CItem;
class CPlayerUI;

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
		MOTION_MAX					// モーション最大数
	};
	enum ITEM_GET_LIST
	{
		ITEM_NONE = -1,
		ITEM_KEY_PRISON,
		ITEM_KEY_STORAGE,
		ITEM_KEY_JAILER_ROOM,
		ITEM_KEY_PC_ROOM,
		ITEM_BATON,
		ITEM_MAP,
		ITEM_MAX
	};
	CPlayer(PRIORITY Priority = PRIORITY_CHARACTER);				// コンストラクタ
	~CPlayer();														// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// プレイヤーの制御
	void Draw(void);												// 描画処理
	bool GetbIncapacitated(void) { return m_bIncapacitated; }		// 行動不能状態取得処理
	virtual void KeyboardMove(float fSpeed, float fAngle) = 0;
	virtual void PadMove(float fSpeed, float fAngle) = 0;
	void MapCollision(void);										// マップとの当たり判定
	void ItemEffectCreate(int ItemGetList);
	void ItemEffectUninit(void);

	void ItemDelete(void);
	//=============================================================================
	//　Set関数
	//=============================================================================
	void SetAddbGetItem(int nItem, bool bGet);	//アイテムの取得状況を設定
	void SetSubbGetItem(int nItem, bool bGet);	//アイテムの取得状況を設定
	void SetUI(CPlayerUI * pUI) { m_pUI = pUI; }
	//=============================================================================
	//　Get関数
	//=============================================================================
	bool GetbItem(int nItem) { return m_abGetItem[nItem]; }		// アイテムの取得状況を取得
	int GetItemCount(void) { return m_nItemCount; }
private:
	int m_nItemCount;					// アイテムの所持数
	int m_nIncapacitatedTimeCount;		// 行動不能時間カウント
	bool m_bIncapacitated;				// 行動不能状態
	bool m_abGetItem[ITEM_MAX];			// アイテムを取得してるか
	bool m_bItempCreate[ITEM_MAX];		// アイテムポインタ生成したか


	int m_nItemSortCount;
	CItem * m_pItem[3];
	CPlayerUI * m_pUI;
	int m_test;
};
#endif
