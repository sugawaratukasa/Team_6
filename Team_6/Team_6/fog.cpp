//=============================================================================
//
// �t�H�O�w�b�_�[ [fog.h]
// Author : Himiya Sho
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "fog.h"
#include "renderer.h"
#include "manager.h"
#include "scene3d.h"

//=======================================================================================
// �}�N����`
//=======================================================================================
#define FOG_START_PLAYER 1600.0f
#define FOG_START_SECCAM 1900.0f
#define FOG_END_PLAYER 2300.0f
#define FOG_END_SECCAM 2500.0f
#define FOG_FADE_LENGTH 60.0f

//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CFog::CFog()
{
	m_nFogCount = 0;
	m_FogState = FOG_NONE;
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_fColRate = 0.0f;
	m_bFadeIn = true;
}

//=======================================================================================
// �f�X�g���N�^
//=======================================================================================
CFog::~CFog()
{
}

//=======================================================================================
// �v���C���[�t�H�O����������
//=======================================================================================
HRESULT CFog::InitPlayerFog(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �t�H�O�L����
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	// �t�H�O�J���[�ݒ�
	pDevice->SetRenderState(D3DRS_FOGCOLOR, m_col);
	// �o�[�e�b�N�X�t�H�O(���`����)���g�p
	pDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR);
	// �͈̓x�[�X�̃t�H�O���g�p
	pDevice->SetRenderState(D3DRS_RANGEFOGENABLE, TRUE);

	float fStart = FOG_START_PLAYER;
	float fEnd = FOG_END_PLAYER;
	// �t�H�O�͈͐ݒ�
	pDevice->SetRenderState(D3DRS_FOGSTART, *((LPDWORD)(&fStart)));
	pDevice->SetRenderState(D3DRS_FOGEND, *((LPDWORD)(&fEnd)));

	return S_OK;
}

//=======================================================================================
// �Ď��J�����t�H�O����������
//=======================================================================================
HRESULT CFog::InitSecCamFog(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �t�H�O�L����
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	// �t�H�O�J���[�ݒ�
	pDevice->SetRenderState(D3DRS_FOGCOLOR, m_col);
	// �o�[�e�b�N�X�t�H�O(���`����)���g�p
	pDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR);
	// �͈̓x�[�X�̃t�H�O���g�p
	pDevice->SetRenderState(D3DRS_RANGEFOGENABLE, TRUE);

	float fStart = FOG_START_SECCAM;
	float fEnd = FOG_END_SECCAM;
	// �t�H�O�͈͐ݒ�
	pDevice->SetRenderState(D3DRS_FOGSTART, *((LPDWORD)(&fStart)));
	pDevice->SetRenderState(D3DRS_FOGEND, *((LPDWORD)(&fEnd)));

	return S_OK;
}

//=======================================================================================
// �t�H�O�X�e�[�g�ύX�֐�
//=======================================================================================
void CFog::SetFogState(FOG_STATE state)
{
	m_FogState = state;
}

//=======================================================================================
// �t�H�O�X�V����
//=======================================================================================
void CFog::UpdateFog(void)
{
	switch (m_FogState)
	{
	case FOG_NONE:
		m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		break;
	case FOG_END:
		if (m_bFadeIn)
		{
			m_fColRate += 1.0f / FOG_FADE_LENGTH;
			if (m_fColRate >= 1.0f)
			{
				m_bFadeIn = false;
			}
		}
		else
		{
			m_fColRate -= 1.0f / FOG_FADE_LENGTH;
			if (m_fColRate <= 0.0f)
			{
				SetFogState(FOG_NONE);
				m_bFadeIn = true;
			}
		}

		m_col = D3DXCOLOR(0.0f + m_fColRate, 0.0f, 0.0f, 1.0f);
		break;
	case FOG_WARNING:
		if (m_bFadeIn)
		{
			m_fColRate += 1.0f / FOG_FADE_LENGTH;
			if (m_fColRate >= 1.0f)
			{
				m_bFadeIn = false;
			}
		}
		else
		{
			m_fColRate -= 1.0f / FOG_FADE_LENGTH;
			if (m_fColRate <= 0.0f)
			{
				m_bFadeIn = true;
			}
		}

		m_col = D3DXCOLOR(0.0f + m_fColRate, 0.0f, 0.0f, 1.0f);
		break;
	default:
		break;
	}
}
