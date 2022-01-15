#ifndef _SECURITY_CAMERA_COLLISON_H_
#define _SECURITY_CAMERA_COLLISON_H_
//=============================================================================
// 監視カメラの判定 [security_camera_collision.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "model.h"
//=============================================================================
// 前方宣言
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// ドアの判定クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CSecurity_Camera_Collision : public CModel
{
public:

	CSecurity_Camera_Collision(PRIORITY Priority = PRIORITY_SECURITY_CAM_COL);			// コンストラクタ
	virtual ~CSecurity_Camera_Collision();											// デストラクタ

	static CSecurity_Camera_Collision *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);							// 初期化処理
	virtual void Uninit(void);														// 終了処理
	virtual void Update(void);														// 更新処理
	virtual void Draw(void);														// 描画処理

	void CameraUse(int nPlayer);													// カメラ使用
	//===========================
	// SetGet関数
	//===========================
private:

};
#endif