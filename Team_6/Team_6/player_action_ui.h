#ifndef _PLAYER_ACTION_UI_H_
#define _PLAYER_ACTION_UI_H_
//=============================================================================
// プレイヤー行動UI [player_action_ui_1.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "player.h"
#include "scene_2d.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// 前方宣言
// Author : Sugawara Tsukasa
//=============================================================================
class CScene2D;
//=============================================================================
// ゴールの扉クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CPlayer_Action_UI
{
public:
	// プレイヤータイプの列挙型
	enum PLAYER_TYPE
	{
		PLYER_TYPE_NONE = -1,
		PLYER_TYPE_1,
		PLYER_TYPE_2
	};
	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_X,
		TYPE_A,
		TYPE_MAX
	};

	CPlayer_Action_UI();								// コンストラクタ
	~CPlayer_Action_UI();								// デストラクタ
	static CPlayer_Action_UI *Create(int player_type);	// 生成処理
	HRESULT Init(void);									// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理
	void UI_Create_Management(void);					// UI生成管理
	//=============================================================================
	// Set関数
	//=============================================================================
	void SetInteract(bool bCameraInteract);	//{ m_bInteract = bCameraInteract; }
	void SetbItemGet(bool bItemGet);		//{ m_bItemGet = bItemGet; }
private:
	CScene2D *m_apScene2D[TYPE_MAX];	// 2Dのポインタ
	bool m_bInteract;				// カメラにインタラクトできるかの判定
	bool m_bItemGet;					// アイテムを拾う事ができるかの判定
	int m_nPlayer_Type;					// プレイヤータイプ
};
#endif