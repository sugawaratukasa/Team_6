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
#include "player.h"

//=======================================================================================
// マクロ定義
//=======================================================================================
#define CAM_HORIZONTAL_ANGLE		(D3DXToRadian(0))
#define CAM_VARTICAL_ANGLE			(D3DXToRadian(70))

//=======================================================================================
// 前方宣言
//=======================================================================================
class CCamera;
class CCameraGame;
class CLight;
class CPlayer;
class CPauseButtonManager;
class CPlayer1UI;

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

	enum CAMERA_ID
	{
		ID_PLAYER_01 = 0,
		ID_PLAYER_02,
		ID_PLAYER_MAX
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
	void CreateItem(void);							// プレイヤーの生成	
	void CreateMap(void);							// マップの生成	
	void CreateGround(void);						// 地面の生成
	void CreateSecCam(void);						// 監視カメラの生成
	void CreateJailer(void);						// 看守の作成

	// Get関数
	CCameraGame *GetCamera(CAMERA_ID id) { return m_pCamera[id]; }	// カメラのポインタ情報
	CLight *GetLight(void) { return m_pLight; }			// ライトのポインタ情報
	CPlayer * GetPlayer(int nPlayer) { return m_apPlayer[nPlayer]; }
private:
	void PauseInput(void);
	// ポインタ
	CCameraGame *m_pCamera[ID_PLAYER_MAX];		// カメラのポインタ	
	CLight *m_pLight;							// ライトのポインタ
	CPlayer *m_apPlayer[MAX_PLAYER];			// プレイヤーのポインタ
	CPauseButtonManager *m_pPauseButtonManager;	// ポーズボタンマネージャーのポインタ
	LPD3DXFONT m_pFont;							// デバック用フォント
};
#endif