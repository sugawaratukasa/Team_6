#ifndef _CAMERA_GAME_H_
#define _CAMERA_GAME_H_
//=============================================================================
//
// ゲームカメラクラスヘッダー [camera_game.h]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "camera.h"

//=============================================================================
// カメラクラス
//=============================================================================
class CCameraGame : public CCamera
{
public:
	CCameraGame();					// コンストラクタ
	~CCameraGame();					// デストラクタ

	HRESULT Init(void);					// 初期化処理
	void Update(void);					// 更新処理
	void NomalUpdate(D3DXVECTOR3 PlayerPos, D3DXVECTOR3 PlayerRot) override;
	static CCameraGame*Create(CCamera::SCREEN_ID id);	// クリエイト

	void SetCameraID(CCamera::SCREEN_ID id);

private:
	CCamera::SCREEN_ID m_id;
};
#endif 