//=============================================================================
//
// �J�����̏��� [camera.cpp]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "camera.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "player.h"
#include "joypad.h"
#include "motion.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define DISTANCE					(2200.0f)						// ���_�`�����_�̋���
#define PLAYER_HEIGHT				(600.0f)						// �����_�̍���

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
	//�e�����o�ϐ��̃N���A
	m_posV = ZeroVector3;
	m_posVDest = ZeroVector3;
	m_posR = ZeroVector3;
	m_posRDest = ZeroVector3;
	m_posU = ZeroVector3;
	m_rot = ZeroVector3;
	m_fDistance = 0.0f;
	m_fMove = 0.0f;
	m_id = SCREEN_NONE;
	m_bInterpolation = true;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCamera::Init(void)
{
	m_fMove = 5.0f;
	m_fDistance = DISTANCE;
	m_fVartical = CAMERA_DEFAULT_F��;
	m_fHorizontal = D3DXToRadian(0.0f);											// �����l�G�̂ق�������
	m_posR = D3DXVECTOR3(0.0f, PLAYER_HEIGHT, 0.0f);							// �����_�ݒ�
	m_posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);										// ������x�N�g��
	m_posV.x = m_posR.x + m_fDistance * sinf(m_fVartical) * sinf(m_fHorizontal);// �J�����ʒuX
	m_posV.y = m_posR.z + m_fDistance * cosf(m_fVartical);						// �J�����ʒuY
	m_posV.z = m_posR.y + m_fDistance * sinf(m_fVartical) * cosf(m_fHorizontal);// �J�����ʒuZ
	m_id = SCREEN_NONE;															// �X�N���[��ID�̏�����
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
void CCamera::Update(void)
{
	bool bUse = CManager::GetRenderer()->GetIsUseSecCam();

	// �Ď��J�������g���Ă���Ȃ�
	if (bUse)
	{
		m_posRDest.x = m_fDistance * sinf(m_fVartical) * sinf(m_fHorizontal);// �J�����ʒuX
		m_posRDest.y = m_fDistance * cosf(m_fVartical);						 // �J�����ʒuY
		m_posRDest.z = m_fDistance * sinf(m_fVartical) * cosf(m_fHorizontal);// �J�����ʒuZ

		if (m_bTarget)
		{
			m_posRDest += m_posVDest;
		}
	}
	else
	{
		m_posVDest.x = m_fDistance * sinf(m_fVartical) * sinf(m_fHorizontal);// �J�����ʒuX
		m_posVDest.y = m_fDistance * cosf(m_fVartical);						 // �J�����ʒuY
		m_posVDest.z = m_fDistance * sinf(m_fVartical) * cosf(m_fHorizontal);// �J�����ʒuZ

		if (m_bTarget)
		{
			m_posVDest += m_posRDest;
		}
	}

    // �J�����̈ʒu�ƒ����_���X�V
	if (m_bInterpolation)
	{
		m_posR += (m_posRDest - m_posR) * CAMERA_MOVE_RATE;
		m_posV += (m_posVDest - m_posV) * CAMERA_MOVE_RATE;
	}
	else
	{
		m_posR += (m_posRDest - m_posR);
		m_posV += (m_posVDest - m_posV);
	}
}

//=============================================================================
//�J�����N���X�̃Z�b�g����
//=============================================================================
void CCamera::SetCamera(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();


	//�X�N���[��ID�ʂɃv���W�F�N�V�����}�g���b�N�X�̍쐬
	if (m_id == SCREEN_NONE)
	{
		//�r���[�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxView);


		//�r���[�}�g���b�N�X�̍쐬
		D3DXMatrixLookAtLH(&m_mtxView,
			&m_posV,
			&m_posR,
			&m_posU);


		//�r���[�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);


		//�v���W�F�N�V�����}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxProjection);


		D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
			D3DXToRadian(45.0f),
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
			10.0f,
			200000.0f);


		//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_PROJECTION,
			&m_mtxProjection);
	}
	else
	{
		//�r���[�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_aMtxView[m_id]);

		//�r���[�}�g���b�N�X�̍쐬
		D3DXMatrixLookAtLH(&m_aMtxView[m_id],
			&m_posV,
			&m_posR,
			&m_posU);

		//�r���[�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_VIEW, &m_aMtxView[m_id]);

		//�v���W�F�N�V�����}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_aMtxProjection[m_id]);

		D3DXMatrixPerspectiveFovLH(&m_aMtxProjection[m_id],
			D3DXToRadian(45.0f),
			(float)(SCREEN_WIDTH / 2 )/ (float)SCREEN_HEIGHT,
			10.0f,
			200000.0f);

		//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_PROJECTION,
			&m_aMtxProjection[m_id]);
	}
}