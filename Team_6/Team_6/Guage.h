//=============================================================================
//
// �^�C�g�����S���� [logo.h]
// Author : ��{ ��
//
//=============================================================================

// ��d�C���N���[�h�h�~�p
#ifndef _GUAGE_H_
#define _GUAGE_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TIMER_TEX_NUM 2

//*****************************************************************************
// �^�C�g�����S�N���X��`
//*****************************************************************************
class CGauge
{
public:
	CGauge();
	~CGauge();
	HRESULT Init(void);
	void Update(void);
	void DrawStencil(void);
	void Draw(void);
	void Uninit(void);
	void CalcTime(void);
	void OnTimerOver(void);
	void SetIsStencil(bool bIsStencil) { m_bIsStencil = bIsStencil; }
	void SetAngle(float fAngle) { m_fAngle = fAngle; }
	int GetTime(void);
private:
	static LPDIRECT3DTEXTURE9		m_apTexture[TIMER_TEX_NUM];
	D3DXMATRIX			    m_mtxWorld;		// ���[���h�}�g���b�N�X
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;		// ���_�o�b�t�@�[
	D3DXVECTOR3				m_pos;			// ���W
	D3DXVECTOR3				m_rot;			// ��]
	D3DXVECTOR3				m_scale;		// �g�嗦
	D3DXCOLOR				m_col;
	float					m_fHeight;		// ����
	float					m_fWidth;		// ��
	float					m_fAngle;		// �p�x
	float					m_fRatio;       // �^�C�}�[�̊���
	int						m_nTime;
	int						m_nRemainTime;  // �c�莞��
	int						m_nElapsedTime;	// �o�ߎ���
	bool					m_bIsStencil;	// �X�e���V���`�撆���ǂ���
	bool					m_bTimer;		// �^�C�}�[�p
};

#endif