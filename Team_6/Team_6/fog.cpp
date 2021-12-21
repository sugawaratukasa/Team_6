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
// �O���[�o���ϐ��錾
//=======================================================================================
int g_nFogCount;
FOG_STATE g_FogState;
D3DXCOLOR g_col;
float g_fColRate;
bool g_bFadeIn;

//=======================================================================================
// �t�H�O������
//=======================================================================================
HRESULT InitFog(void)
{
	g_nFogCount = 0;
	g_FogState = FOG_NONE;
	g_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	g_fColRate = 0.0f;
	g_bFadeIn = true;
	return S_OK;
}

//=======================================================================================
// �v���C���[�t�H�O����������
//=======================================================================================
HRESULT InitPlayerFog(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �t�H�O�L����
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	// �t�H�O�J���[�ݒ�
	pDevice->SetRenderState(D3DRS_FOGCOLOR, g_col);
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
HRESULT InitSecCamFog(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �t�H�O�L����
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	// �t�H�O�J���[�ݒ�
	pDevice->SetRenderState(D3DRS_FOGCOLOR, g_col);
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
void SetFogState(FOG_STATE state)
{
	g_FogState = state;
}

//=======================================================================================
// �t�H�O�X�V����
//=======================================================================================
void UpdateFog(void)
{
	switch (g_FogState)
	{
	case FOG_NONE:
		g_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		break;
	case FOG_END:
		if (g_bFadeIn)
		{
			g_fColRate += 1.0f / FOG_FADE_LENGTH;
			if (g_fColRate >= 1.0f)
			{
				g_bFadeIn = false;
			}
		}
		else
		{
			g_fColRate -= 1.0f / FOG_FADE_LENGTH;
			if (g_fColRate <= 0.0f)
			{
				SetFogState(FOG_NONE);
				g_bFadeIn = true;
			}
		}

		g_col = D3DXCOLOR(0.0f + g_fColRate, 0.0f, 0.0f, 1.0f);
		break;
	case FOG_WARNING:
		if (g_bFadeIn)
		{
			g_fColRate += 1.0f / FOG_FADE_LENGTH;
			if (g_fColRate >= 1.0f)
			{
				g_bFadeIn = false;
			}
		}
		else
		{
			g_fColRate -= 1.0f / FOG_FADE_LENGTH;
			if (g_fColRate <= 0.0f)
			{
				g_bFadeIn = true;
			}
		}

		g_col = D3DXCOLOR(0.0f + g_fColRate, 0.0f, 0.0f, 1.0f);
		break;
	default:
		break;
	}
}
