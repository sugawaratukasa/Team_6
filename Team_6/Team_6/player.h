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

	static CPlayer*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		// クリエイト

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
	void UpdateState(void);											// プレイヤーの状態
	void PlayerControl(void);										// プレイヤーの制御
	void UpdateRot(void);											// 角度の更新処理

	void Hit(int nDamage);											// ヒット処理関数
	void Death(void)override;										// 死亡関数
	void Move(void)override;										// 移動処理
	void KeyboardMove(float fSpeed,float fAngle);	// キーボード移動
	void PadMove(float fSpeed, float fAngle);		// パッド移動
	void Attack(void)override;										// 攻撃処理

private:
	D3DXVECTOR3 m_rotDest;							// 回転(目標値)
};
#endif