#ifndef _CAMERA_SECURITY_H_
#define _CAMERA_SECURITY_H_
//=============================================================================
//
// 監視カメラ情報管理処理 [Camera_Security.cpp]
// Author : 樋宮 匠
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "game.h"
#include "jailer_view.h"
#include "scene.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define SECCAM_ANGLE_MAX D3DXToRadian(45)
#define SECCAM_RETURN_LENGTH	60

//=============================================================================
// カメラクラス
//=============================================================================
class CCameraSecurity : public CScene
{
public:
	CCameraSecurity();					// コンストラクタ
	~CCameraSecurity();					// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// 初期化処理
	void Update(void);					// 更新処理
	void Draw(void);
	void Uninit(void);
	void SearchPlayer(void);
	static CCameraSecurity*Create(D3DXVECTOR3 pos, float fDir);	// クリエイト

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	float GetAngle(void) { return m_fAngle; }
	CCameraSecurity * GetTop(void) { return m_pTop; }
	CCameraSecurity * GetNext(void) { return m_pNext; }
	CCameraSecurity * GetPrev(void) { return m_pPrev; }
	CCameraSecurity * GetBottom(void) { return m_pBot; }

private:
	D3DXVECTOR3 m_pos;
	float		m_fDir;
	float		m_fAngle;
	float		m_fAngleMoveRate;
	int			m_nCamReturnCount;
	CJailerView	*m_pView;
	static CCameraSecurity *m_pTop;
	static CCameraSecurity *m_pCur;
	static CCameraSecurity *m_pBot;
	CCameraSecurity *m_pPrev;
	CCameraSecurity *m_pNext;
};
#endif 