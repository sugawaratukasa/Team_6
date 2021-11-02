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
// �^�C�g�����S�N���X��`
//*****************************************************************************
class CScreenFrame :public CScene2D
{
public:
	CScreenFrame();
	~CScreenFrame();
	HRESULT Init(void);
	void Update(void);
	void Draw(void);
	void Uninit(void);
	static CScreenFrame * Create(void);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture;	 // �e�N�X�`���ւ̃|�C���^
};

#endif