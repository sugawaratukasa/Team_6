#ifndef _PARTICLE_MANAGER_H_
#define _PARTICLE_MANAGER_H_

//===============================================================================
// パーティクルマネージャー[particle_manager.h]
// Author: Sugawara Tsukasa
//===============================================================================
//===============================================================================
// インクルードファイル
// Author : SugawaraTsukasa
//===============================================================================
#include "main.h"
//===============================================================================
// パーティクルマネージャークラス
// Author : SugawaraTsukasa
//===============================================================================
class CParticle_Manager
{
public:
	// カラーRGB
	struct COL_RGB
	{
		int nR;
		int nG;
		int nB;
	};
	// 情報の構造体
	struct INFO
	{
		bool bAlpha_Blend;			// 加算合成を行うか
		bool bLife;					// ライフを使用するか
		bool bRandomPos;			// 位置をランダムにするか
		bool bRandomSize;			// ランダムサイズ
		bool bAddScale;				// 拡大率を加算するか
		bool bSubColor;				// 色減算を行うか
		bool bRotRandom;			// 向きランダム
		bool bTexRandom;			// テクスチャランダム
		bool bColorRandom;			// 色ランダム
		D3DXVECTOR3 Random_pos;		// 位置ランダム
		D3DXVECTOR3 size;			// サイズ
		D3DXVECTOR3 move;			// 移動量
		D3DXVECTOR3 Angle;			// 角度
		D3DXVECTOR3 AddAngle;		// xyzの角度加算
		D3DXCOLOR color;			// 色
		D3DXCOLOR SubColor;			// 色減算量
		COL_RGB RGB;				// 色ランダム用
		int nCreateCnt;				// 生成カウント
		int nCreateTotalCnt;		// 生成の総数
		int nAlpha;					// 描画する透明度
		int nLife;					// ライフ数
		int nTexNum;				// テクスチャナンバー
		int nMinTex_RandomNum;		// テクスチャナンバー
		int nMaxTex_RandomNum;		// テクスチャナンバー
		float fAngle;				// 角度
		float fAddAngle;			// 角度の加算量
		float fRandom_Min_Size;		// ランダムサイズの最小値
		float fRandom_Max_Size;		// ランダムサイズの最大値
		float fAddScale;			// 拡大率の加算量
	};
	// 種類
	enum TYPE
	{
		TYPE_NONE = -1,		// 最小
		TYPE_ITEM_SILVER,	// アイテムエフェクトシルバー
		TYPE_ITEM_GOLD,		// アイテムエフェクトゴールド
		TYPE_ITEM_RAINBOW,	// アイテムエフェクトレインボー
		TYPE_MAX			// 最大
	};

	CParticle_Manager();					// コンストラクタ
	~CParticle_Manager();					// デストラクタ

	void Init(void);						// 初期化処理
	void LoadAll(void);						// 全読み込み
	HRESULT Load_Info(void);				// 情報読み込み
	HRESULT LoadTextureName(void);			// テクスチャパス読み込み処理
	HRESULT LoadTexture(void);				// テクスチャ読み込み
	void UnloadTexture(void);				// テクスチャ破棄

//===============================================================
// Get関数
//===============================================================
	LPDIRECT3DTEXTURE9 GetTexture(int nTexNum) { return m_apTexture.at(nTexNum); }
	INFO GetInfo(int nInfoNum) { return m_aInfo[nInfoNum]; }

private:
	INFO m_aInfo[TYPE_MAX];					// INFOの配列変数
	vector <string> m_aInfoTextName;		// テキストパス用変数
	vector<LPDIRECT3DTEXTURE9> m_apTexture;	// LPDIRECT3DTEXTURE9のvector型変数
	vector<string> m_aTextureName;			// テクスチャのパス読み込み
};
#endif
