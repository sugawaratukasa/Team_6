#ifndef _PLAYER_2_H_
#define _PLAYER_2_H_
//=============================================================================
//
// プレイヤー1 [player_1.h]
// Author : Nikaido Taichi
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "player.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CPlayer2ItemUI;
class CScene2D;
class CGuidBG;
class CBlackTexture;
class CCaveatBar;

//=============================================================================
// プレイヤークラス
//=============================================================================
class CPlayer2 : public CPlayer
{
public:
	CPlayer2(PRIORITY Priority = PRIORITY_CHARACTER);				// コンストラクタ
	~CPlayer2();													// デストラクタ
	static CPlayer2*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		// クリエイト
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// プレイヤーの制御
	void Draw(void);												// 描画処理
	void PrisonWarp(void);											// 独房ワープ処理
	void SetbGuidCreate(CItemObject::ITEM_OBJECT_LIST Type);
private:
	void InputMove(float fSpeed, float fAngle);					// キーボード移動処理
	void UpdateRot(void);											// 向き更新処理
	bool m_bBlackTextureCreate;										// 黒背景のテクスチャ生成状態
	D3DXVECTOR3 m_rotDest;
	CScene2D * m_pItemGuidTexture;
	CGuidBG * m_pGuidBG;
	CBlackTexture * m_pBlackTexture;
	CCaveatBar * m_pCaveatBar;
};
#endif