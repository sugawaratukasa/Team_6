#ifndef _GAME_H_
#define _GAME_H_
//=======================================================================================
//
// ゲームの処理 [game.h]
// Author : Sugawara Tsukasa
//
//=======================================================================================

//=======================================================================================
// インクルードファイル
//=======================================================================================
#include "mode_base.h"

//=======================================================================================
// マクロ定義
//=======================================================================================

//=======================================================================================
// 前方宣言
//=======================================================================================
class CCamera;
class CCameraGame;
class CLight;
class CMeshField;
class CBg;
class CPlayer;
class CMap;
class CBoss_Shark;

//=======================================================================================
// ゲームクラス
//=======================================================================================
class CGame : public CModeBase
{
public:
	enum ENEMY_OBSTACLE_TYPE
	{
		ENEMY_OBSTACLE_TYPE_MIN = 0,
		ENEMY_OBSTACLE_TYPE_SHIP,
		ENEMY_OBSTACLE_TYPE_SCAFFOLDING,
		ENEMY_OBSTACLE_TYPE_TORPEDO,
		ENEMY_OBSTACLE_TYPE_ROCK,
		ENEMY_OBSTACLE_TYPE_MAX
	};
	//=============================================================================
	//　敵生成ファイル情報の構造体
	//=============================================================================
	struct ENEMY_FILE_DATA
	{
		D3DXVECTOR3 Pos;		// 位置のオフセット情報
		D3DXVECTOR3 Rot;		// 向きのオフセット情報
		ENEMY_OBSTACLE_TYPE Type;		// 種類情報
	};

	CGame();		// コンストラクタ
	~CGame();		// デストラクタ

	HRESULT Init(void);								// 初期化処理
	void Uninit(void);								// 終了処理
	void Update(void);								// 更新処理
	void Draw(void);								// 描画処理
	void SetGame(void);								// ゲームの設定

	void CreatePlayer(void);						// プレイヤーの生成	
	void CreateMap(void);							// マップの生成	
	void CreateGround(void);						// 地面の生成
	void DrawPlayerPos(void);						// プレイヤーの位置書き込み

	// Get関数
	CCamera *GetCamera(void) { return (CCamera*)m_pCamera; }	// カメラのポインタ情報
	CLight *GetLight(void) { return m_pLight; }			// ライトのポインタ情報
	CPlayer *GetPlayer(void) { return m_pPlayer; }			// プレイヤーのポインタ情報

private:
	// ポインタ
	CCameraGame *m_pCamera;					// カメラのポインタ	
	CLight *m_pLight;						// ライトのポインタ
	CPlayer *m_pPlayer;						// プレイヤーのポインタ

	LPD3DXFONT m_pFont;						// デバック用フォント
};
#endif