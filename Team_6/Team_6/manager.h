#ifndef _MANAGER_H_
#define _MANAGER_H_
//=============================================================================
//
// マネージャー処理 [manager.h]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define GET_TEXTURE_PTR		(CManager::GetResourceManager()->GetTextureClass())	// テクスチャのポインタ
#define GET_SOUND_PTR		(CManager::GetResourceManager()->GetSoundClass())	// サウンドのポインタ
#define GET_XFILE_PTR		(CManager::GetResourceManager()->GetXfileClass())	// Xファイルのポインタ
#define GET_PLAYER_PTR		(CManager::GetModePtr()->GetPlayer())				// プレイヤーのポインタ
#define GET_CAMERA_PTR		(CManager::GetModePtr()->GetCamera())				// カメラのポインタ
#define GET_RENDERER_DEVICE	(CManager::GetRenderer()->GetDevice())				// デバイス取得
#define GET_MAP_PTR			(CManager::GetModePtr()->GetMap())					// マップのポインタ取得

//=============================================================================
//前方宣言
//=============================================================================
class CRenderer;
class CInputKeyboard;
class CFade;
class CInputJoypad;
class CScene;
class CResourceManager;
class CGame;
class CModeBase;
class CMovie;
class CParticle_Manager;
//=============================================================================
//マネージャークラス
//=============================================================================
class CManager
{
public:
	//=========================================================================
	//列挙型定義
	//=========================================================================
	enum MODE_TYPE
	{
		MODE_TYPE_NONE = 0,
		MODE_TYPE_TITLE,			// タイトルモード

		MODE_TYPE_TUTORIAL,			// チュートリアル
		MODE_TYPE_GAME,				// ゲームモード
		MODE_TYPE_RESULT,			// リザルト
		MODE_TYPE_CLEAR_TIME,		// クリアタイム
		MODE_TYPE_RANKING_RESULT,	// ランキング
		MODE_TYPE_RANKING_BOARD,	// ランキング
		MODE_TYPE_GAMEOVER,
		MODE_TYPE_MAX,
	};

	CManager();		// コンストラクタ
	~CManager();	// デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);		// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
	void LoadAll(void);												// 全てのロード処理

	// Set関数
	static void SetMode(MODE_TYPE mode);							// モードの設定

	// Get関数
	static MODE_TYPE GetMode(void);																// モードの情報
	static CRenderer *GetRenderer(void) { return m_pRenderer.get(); }							// レンダラー情報
	static CInputKeyboard *GetKeyboard(void) { return m_pInput.get(); }							// キーボード情報
	static CFade *GetFade(void) { return m_pFade.get(); }										// フェード情報
	static CInputJoypad *GetJoypad(void) { return m_pJoypad.get(); }							// ジョイパッドコントローラの情報
	static CScene *GetScene(void) { return m_pScene.get(); }									// シーン情報
	static CResourceManager *GetResourceManager(void) { return m_pResourceManager.get(); }		// リソースマネージャのポインタ
	static CMovie *GetMovie(void) { return m_pMovie.get(); }
	static CParticle_Manager *GetParticle_Manager(void) { return m_pParticle_Manager.get(); }	// パーティクルマネージャーのポインタ取得

	static CModeBase *GetModeBase(void);						// ゲームモードの情報
	static CModeBase *GetModePtr(void);							// ゲームの情報

private:


	static unique_ptr<CRenderer> m_pRenderer;					// レンダラークラスのポインタ
	static unique_ptr<CInputKeyboard> m_pInput;					// インプットクラスのポインタ
	static unique_ptr<CFade> m_pFade;							// フェードクラスのポインタ
	static unique_ptr<CInputJoypad> m_pJoypad;					// ジョイパッドコントローラのポインタ
	static unique_ptr<CScene> m_pScene;							// シーンのポインタ
	static unique_ptr<CResourceManager> m_pResourceManager;		// リソースマネージャのポインタ
	static unique_ptr<CModeBase> m_pModeBase;					// モードのポインタ
	static unique_ptr<CParticle_Manager> m_pParticle_Manager;	// パーティクルのポインタ
	static MODE_TYPE m_mode;									// モード
	static unique_ptr<CMovie> m_pMovie;
};
#endif