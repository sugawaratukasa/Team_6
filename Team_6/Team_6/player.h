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
	CPlayer(PRIORITY Priority = PRIORITY_CHARACTER);				// コンストラクタ
	~CPlayer();														// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// プレイヤーの制御
	void Draw(void);												// 描画処理
	bool GetbIncapacitated(void) { return m_bIncapacitated; }		// 行動不能状態取得処理
	virtual void KeyboardMove(float fSpeed, float fAngle) = 0;
	virtual void PadMove(float fSpeed, float fAngle) = 0;
	//=============================================================================
	//　Set関数
	//=============================================================================
	void SetItem(CItemObject::ITEM_OBJECT_LIST ItemList, CItemObject * pItem) { m_apItem[ItemList] = pItem;}	// アイテム設定処理
private:
	CItemObject *  m_apItem[CItemObject::ITEM_OBJECT_MAX];	// アイテムのポインタ
	int m_nItemCount;										// アイテムの所持数
	int m_nIncapacitatedTimeCount;							// 行動不能時間カウント
	bool m_bIncapacitated;									// 行動不能状態
};
#endif
