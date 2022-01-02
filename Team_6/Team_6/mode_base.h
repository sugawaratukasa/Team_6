#ifndef _MODE_BASE_H_
#define _MODE_BASE_H_
//==============================================================================
//
// モードの基底クラス  [mode_base.h]
// Author : Sugawara Tsukasa
//
//==============================================================================

//==============================================================================
// インクルード
//==============================================================================
#include "main.h"
#include "player.h"
#include "jailer.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CLight;
class CCamera;
class CPlayer;
class CJailer;
//==============================================================================
// クラス定義
//==============================================================================
class CModeBase
{
public:
	CModeBase();				// コンストラクタ
	virtual ~CModeBase() {};	// デストラクタ

	virtual HRESULT Init(void) = 0;		// 初期化
	virtual void Update(void) = 0;		// 更新
	virtual void Draw(void) = 0;		// 描画

										// Get関数
	virtual CCamera* GetCamera(void) { return m_pCamera; }				// カメラのポインタ
	virtual CLight* GetLight(void) { return m_pLight; }					// ライトのポインタ
	virtual CPlayer* GetPlayer(int nPlayer) { return m_apPlayer[nPlayer]; }	// プレイヤーのポインタ
	virtual CJailer* GetJailer(void) { return m_pJailer; }					// ライトのポインタ

private:
	CCamera *m_pCamera;		// カメラのポインタ
	CLight *m_pLight;		// ライトのポインタ
	CPlayer *m_apPlayer[MAX_PLAYER];		// プレイヤーのポインタ
	CJailer *m_pJailer;		// 看守のポインタ
};

#endif