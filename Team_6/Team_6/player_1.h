#ifndef _PLAYER_1_H_
#define _PLAYER_1_H_
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

//=============================================================================
// プレイヤークラス
//=============================================================================
class CPlayer1 : public CPlayer
{
public:
	CPlayer1(PRIORITY Priority = PRIORITY_CHARACTER);									// コンストラクタ
	~CPlayer1();																		// デストラクタ
	static CPlayer1*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);							// クリエイト
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);										// 初期化処理
	void Uninit(void);																	// 終了処理
	void Update(void);																	// プレイヤーの制御
	void Draw(void);																	// 描画処理
private:
	void KeyboardMove(float fSpeed, float fAngle);
	void PadMove(float fSpeed, float fAngle);
	void UpdateRot(void);
	D3DXVECTOR3 m_rotDest;
};
#endif