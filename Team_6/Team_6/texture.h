#ifndef _TEXTURE_H_
#define _TEXTURE_H_
//=============================================================================
//
// テクスチャの管理ヘッダー [texture.h]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"

//=============================================================================
//クラス宣言
//=============================================================================
class CTexture
{
public:
	// テクスチャの種類
	enum TEXTURE_TYPE_NUM
	{
		TEXTURE_TYPE_NUM_NONE = -1,		// 初期値
		TEXTURE_TYPE_NUM_NORMAL,		// 通常テクスチャ
		TEXTURE_TYPE_NUM_SEPARATE,		// 分割テクスチャ
		TEXTURE_TYPE_NUM_MAX			// 最大値
	};

	// テクスチャの番号の列挙型
	enum TEXTURE_TYPE
	{
		TEXTURE_NUM_NONE = -1,				// 初期値
		TEXTURE_NUM_FLOOR,					// 床
		TETXTURE_NUM_SCREENFRAME,			// 画面分割用
		TETXTURE_NUM_SCREENFRAME_SECCAM,// 監視カメラフレーム
		TETXTURE_NUM_SCREENFRAME_FUZZ,	// 砂嵐
		TEXTURE_NUM_TIMER_FRAME,			// タイマーフレーム
		TEXTURE_NUM_TIMER_GUAGE,			// タイマーゲージ
		TEXTURE_NUM_TIMER_STENCIL,			// タイマーステンシル用のテクスチャ
		TEXTURE_NUM_TIMER_NUMBER,			// タイマー用数字
		TEXTURE_NUM_UI_FLAME,				// UIフレーム	
		TEXTURE_NUM_BATON,					// 警棒
		TEXTURE_NUM_PC_ROOM_KEY,			// PC室の鍵
		TEXTURE_NUM_STORAGE_KEY,			// 倉庫の鍵
		TEXTURE_NUM_PRISON_KEY,				// 牢屋の鍵
		TEXTURE_NUM_JAILER_KEY,				// 看守の鍵
		TEXTURE_NUM_UI_MAP,					// マップ
		TEXTURE_NUM_BUTTON_START,			// スタートボタン
		TEXTURE_NUM_BUTTON_RANKING,			// ランキングボタン
		TEXTURE_NUM_BUTTON_EXIT,			// 終了ボタン
		TEXTURE_NUM_BUTTON_QUIT_GAME,		// ゲームに戻るボタン
		TEXTURE_NUM_BUTTON_BACK_TO_TITLE,	// タイトルに戻るボタン
		TEXTURE_NUM_BUTTON_GUID,			// ガイドボタン
		TEXTURE_NUM_TITLE_BG,				// タイトル背景
		TEXTURE_NUM_TITLE_LOGO,				// タイトルロゴ
		TEXTURE_NUM_SELECT_ITEM_FLAME,		// アイテム選択の枠
		TEXTURE_NUM_MAP,					// マップテクスチャ
		TEXTURE_NUM_Y,						// Y
		TEXTURE_NUM_RANKING_BG,				// ランキング背景
		TEXTURE_NUM_RANKING_NUMBER,			// ランキングナンバー
		TEXTURE_NUM_JAILER_KEY_GUID,
		TEXTURE_NUM_PC_ROOM_KEY_GUID,
		TEXTURE_NUM_ELECTRICAL_KEY_GUID,
		TEXTURE_NUM_STORAGE_KEY_GUID,
		TEXTURE_NUM_BATON_GUID,
		TEXTURE_NUM_MAP_GUID,
		TEXTURE_NUM_PAUSE_LOGO,
		TEXTURE_NUM_BLACK_FILL,				// 黒いテクスチャ
		TEXTURE_NUM_TEXTLOG01_TEST,       // ログテスト用
		TEXTURE_NUM_TEXTLOG02_TEST,       // ログテスト用
		TEXTURE_NUM_CONTROL_KEY,
		TEXTURE_NUM_CONTROL_KEY_GUID,
		TEXTURE_NUM_ELECTRICAL_KEY,
		TEXTURE_NUM_MAP1,
		TEXTURE_NUM_MAP2,
		TEXTURE_NUM_GUID_BG,
		TEXTURE_NUM_GAMEOVER,
		TEXTURE_LOG_P1_SHUTTER_DOWN,		// P1シャッタードアが開いた時のログ
		TEXTURE_LOG_P1_NOT_SHUTTER_DOWN,	// P1シャッタードアが開かない時のログ
		TEXTURE_LOG_P1_RESTRAINT,			// P1拘束された時のログ
		TEXTURE_LOG_P1_RESTRAINT_TO_MEMVER,	// P1仲間が拘束された時のログ
		TEXTURE_LOG_P1_OPEN_DOOR,			// P1ドアが開いたときのログ
		TEXTURE_LOG_P1_NOT_OPEN_DOOR,		// P1ドアが開かなかった時のログ
		TEXTURE_LOG_P1_OPEN_CELL_DOOR,		// P1独房のドアが開いた時のログ
		TEXTURE_LOG_P1_NOT_SWITCH_PUSH,		// P1スイッチを押せなかった時のログ
		TEXTURE_LOG_P2_SHUTTER_DOWN,		// P2シャッタードアが開いた時のログ
		TEXTURE_LOG_P2_NOT_SHUTTER_DOWN,	// P2シャッタードアが開かない時のログ
		TEXTURE_LOG_P2_RESTRAINT,			// P2拘束された時のログ
		TEXTURE_LOG_P2_RESTRAINT_TO_MEMVER,	// P2仲間が拘束された時のログ
		TEXTURE_LOG_P2_OPEN_DOOR,			// P2ドアが開いたときのログ
		TEXTURE_LOG_P2_NOT_OPEN_DOOR,		// P2ドアが開かなかった時のログ
		TEXTURE_LOG_P2_OPEN_CELL_DOOR,		// P2独房のドアが開いた時のログ
		TEXTURE_LOG_P2_NOT_SWITCH_PUSH,		// P2スイッチを押せなかった時のログ
		TEXTURE_NUM_FLOOR_2,
		TEXTURE_NUM_FLOOR_3,
		TEXTURE_NUM_FLOOR_4,
		TEXTURE_CLEAR_TIME_BG,

		TEXTURE_NUM_CAVEATBAR,	//警告バー
		TEXTURE_NUM_CAVEAT,	//警告マーク


		TEXTURE_EMOTION_QUESTION,
		TEXTURE_EMOTION_ANGER,
		TEXTURE_NUM_MAX
	};

	// アニメーションを行うテクスチャの列挙型
	enum SEPARATE_TEX_TYPE
	{
		SEPARATE_TEX_NONE = -1,			// 初期値
		SEPARATE_TEX_NUM,
		SEPARATE_TEX_MAX				// 最大値
	};

	// アニメーションを行うテクスチャの構造体情報
	struct SEPARATE_TEX_INFO
	{
		LPDIRECT3DTEXTURE9 pSeparateTexture;		// 分割テクスチャへのポインタ
		SEPARATE_TEX_TYPE type;						// テクスチャの種類
		D3DXVECTOR2 m_TexInfo;						// テクスチャの分割数、速さ
		bool bLoop;									// ループするか
	};

	CTexture();		// コンストラクタ
	~CTexture();	// デストラクタ

	static CTexture *Create(void);											// インスタンス生成
	HRESULT SetTextureName(void);											// 初期化処理
	void LoadAll(void);														// 全てのロード
	void UnLoadAll(void);													// 全てのアンロード

																			// 通常テクスチャ
	HRESULT NormalTexLoad(void);											// テクスチャロード
	void NormalTexUnLoad(void);												// テクスチャアンロード
	LPDIRECT3DTEXTURE9 GetTexture(TEXTURE_TYPE Tex_Type);					// テクスチャの情報

																			// 分割テクスチャ
	HRESULT SeparateTexLoad(void);											// 分割テクスチャロード
	void SeparateTexUnLoad(void);											// 分割テクスチャアンロード
	LPDIRECT3DTEXTURE9 GetSeparateTexture(SEPARATE_TEX_TYPE SepaTex_Type);	// 分割テクスチャ情報
	D3DXVECTOR2 GetSparateTexInfo(SEPARATE_TEX_TYPE SepaTex_Type);			// 分割テクスチャ　UVの枚数取得
	bool GetSparateTexLoop(SEPARATE_TEX_TYPE SepaTex_Type);					// ループするか

private:
	LPDIRECT3DTEXTURE9 m_apTexture[TEXTURE_NUM_MAX];						// テクスチャのポインタ
	SEPARATE_TEX_INFO m_apSeparateTexture[SEPARATE_TEX_MAX] =
	{
	};

	vector<string> m_aTexFileName[TEXTURE_TYPE_NUM_MAX];					// テクスチャの名前
};
#endif
