//=============================================================================
//
// �^�C�g�����S���� [logo.h]
// Author : ��{ ��
//
//=============================================================================

// ��d�C���N���[�h�h�~�p
#ifndef _SCREEN_FRAME_H_
#define _SCREEN_FRAME_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "scene_2d.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_FRAME_TEX 3
#define FRAME_NORMAL 0
#define FRAME_SECCAM 1
#define FRAME_FUZZ   2
#define FRAME_CHANGE_LENGTH 30
#define FRAME_MAX 2
#define FRAME_LEFT 0
#define FRAME_RIGHT 1

//*****************************************************************************
// �^�C�g�����S�N���X��`
//*****************************************************************************
class CScreenFrame :public CScene
{
public:
	CScreenFrame(PRIORITY Priority = PRIORITY_SCREENFRAME);
	~CScreenFrame();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Update(void);
	void Draw(void);
	void Uninit(void);
	void ChangeCamera(int nFrameID, LPDIRECT3DTEXTURE9 pTex);
	static CScreenFrame * Create(void);
private:
	static LPDIRECT3DTEXTURE9		m_apTexture[MAX_FRAME_TEX];	 // �e�N�X�`���ւ̃|�C���^
	CScene2D *m_pScene2D[FRAME_MAX];
	int m_nCountSec[FRAME_MAX];
	bool m_bIsChanging[FRAME_MAX];
	bool m_bUseSecCamOld[FRAME_MAX];
	bool m_bIsEnableCam;
};

#endif