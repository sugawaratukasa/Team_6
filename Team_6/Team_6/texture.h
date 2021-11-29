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
		TEXTURE_NUM_RANKING_BG,			// ランキング背景
		TEXTURE_NUM_RANKING_NUMBER,		// ランキングナンバー
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
