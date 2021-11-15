//=============================================================================
//
// �J�����̏��� [camera.cpp]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "camera_game.h"
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
#define CAMERA_DEFAULT_F��			(D3DXToRadian(75.0f))			// �J�����̃�Default�l
#define DISTANCE					(2200.0f)						// ���_�`�����_�̋���
#define DISTANCE_FAR_UP				(35.0f)							// �J�����������l
#define FAR_DISTANCE				(3000.0f)						// ���߂̃J����
#define PLAYER_HEIGHT				(600.0f)						// �����_�̍���
#define CAMERA_MIN_F��				(D3DXToRadian(10.0f))			// �J�����̍ŏ��p
#define CAMERA_MAX_F��				(D3DXToRadian(170.0f))			// �J�����̍ő�p
#define CAMERA_MIN_HIGHT			(2.0f)							// �J�����̍Œፂ�x
#define STICK_SENSITIVITY			(100.0f)						// �X�e�B�b�N���x
#define STICK_INPUT_CONVERSION		(D3DXToRadian(2.0f))			// �X�e�B�b�N���͕ω���
#define HEIGHT_DIVIDE				(1.5f)							// ������

//=============================================================================
// �C���X�^���X����
//=============================================================================
CCameraGame * CCameraGame::Create(CCamera::SCREEN_ID id)
{
	// �������m��
	CCameraGame *pCamera = new CCameraGame;

	// ����������
	pCamera->Init();

	pCamera->SetCameraID(id);
	pCamera->SetScreenID(id);

	return pCamera;
}

//=============================================================================
// �J����ID�ݒ�
//=============================================================================
void CCameraGame::SetCameraID(CCamera::SCREEN_ID id)
{
	m_id = id;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCameraGame::CCameraGame()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCameraGame::~CCameraGame()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCameraGame::Init(void)
{
	// ����������
	CCamera::Init();
	m_id = CCamera::SCREEN_NONE;
	SetTarget(true);

	m_nCamNum = 0;

	// ��������
	m_aSecCamPos[0] = D3DXVECTOR3(1000.0f, 0.0f, -1000.0f);
	m_aSecCamPos[1] = D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f);
	m_aSecCamPos[2] = D3DXVECTOR3(-1000.0f, 0.0f, 1000.0f);
	m_aSecCamPos[3] = D3DXVECTOR3(1000.0f, 0.0f, 1000.0f);

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CCameraGame::Update(void)
{
	//�L�[�{�[�h�N���X���̎擾
	CInputKeyboard *pKeyInput = CManager::GetKeyboard();
	// �W���C�p�b�h�̎擾
	DIJOYSTATE js = CInputJoypad::GetStick(0);

	bool bUse = CManager::GetRenderer()->GetIsUseSecCam();

	if (bUse)
	{
		SetIsInterpolation(false);

		if (pKeyInput->GetTrigger(DIK_1))
		{
			m_nCamNum--;
			if (m_nCamNum < 0)
			{
				m_nCamNum = SECURITY_CAM_MAX - 1;
			}
		}
		if (pKeyInput->GetTrigger(DIK_2))
		{
			m_nCamNum++;
			if (m_nCamNum >= SECURITY_CAM_MAX)
			{
				m_nCamNum = 0;
			}
		}

		SetScreenID(CCamera::SCREEN_NONE);
		SetTargetPos(m_aSecCamPos[m_nCamNum]);
	}
	else
	{
		SetIsInterpolation(true);
		m_nCamNum = 0;
		SetScreenID(m_id);
	}

	CCamera::Update();
	CCamera::SetCamera();
}

//=============================================================================
// �ʏ��Ԃ̍X�V����
//=============================================================================
void CCameraGame::NomalUpdate(D3DXVECTOR3 PlayerPos, D3DXVECTOR3 PlayerRot)
{
	//�L�[�{�[�h�N���X���̎擾
	CInputKeyboard *pKeyInput = CManager::GetKeyboard();

	// �W���C�p�b�h�̎擾
	DIJOYSTATE js = CInputJoypad::GetStick(0);

	// �p�x�̎擾
	float fAngle3 = atan2f((float)js.lX, -(float)js.lY);	// �R���g���[���̊p�x
	float fAngle2 = atan2f(-(float)js.lX, (float)js.lY);	// �R���g���[���̊p�x

	// �J�������W
	D3DXVECTOR3 VDest = ZeroVector3;

	// �O��̌����擾
	D3DXVECTOR3 posRDest = GetposRDest();

	// �����擾
	float fDistance = GetDistance();

	// ���E����p�x�擾
	float fHorizontal = GetHorizontal();

	// �㉺����p�x�擾
	float fVartical = GetVartical();

	//���_�i�J�������W�j�̍�����
	if (pKeyInput->GetPress(DIK_LEFT) || js.lZ > STICK_SENSITIVITY)
	{
		// ���Z
		fHorizontal += STICK_INPUT_CONVERSION;
	}
	//���_�i�J�������W�j�̉E����
	if (pKeyInput->GetPress(DIK_RIGHT) || js.lZ < -STICK_SENSITIVITY)
	{
		// ���Z
		fHorizontal -= STICK_INPUT_CONVERSION;
	}
	//���_�i�J�������W�j�̏����
	if (pKeyInput->GetPress(DIK_UP) || js.lRz > STICK_SENSITIVITY && fVartical >= CAMERA_MIN_F��)
	{
		// ���Z
		fVartical -= STICK_INPUT_CONVERSION;
	}
	//���_�i�J�������W�j�̉�����
	if (pKeyInput->GetPress(DIK_DOWN) || js.lRz < -STICK_SENSITIVITY && fVartical <= CAMERA_MAX_F��)
	{
		// ���Z
		fVartical += STICK_INPUT_CONVERSION;
	}

	// �J�����̈ʒu�ݒ�
	VDest.x = PlayerPos.x + fDistance * sinf(fVartical) * sinf(fHorizontal);	// �J�����ʒuX�ݒ�
	VDest.y = PlayerPos.y + PLAYER_HEIGHT + fDistance * cosf(fVartical);		// �J�����ʒuY�ݒ�
	VDest.z = PlayerPos.z + fDistance * sinf(fVartical) * cosf(fHorizontal);	// �J�����ʒuZ�ݒ�

	posRDest = D3DXVECTOR3(PlayerPos.x, PlayerPos.y + PLAYER_HEIGHT, PlayerPos.z);	//�����_�ݒ�

	//�J����POSY�̉���
	if (VDest.y <= CAMERA_MIN_HIGHT)
	{
		VDest.y = CAMERA_MIN_HIGHT;	//���E�l�ɖ߂�
	}

	//�ݒ�l�̔��f
	GetposV() += (VDest - GetposV())*0.1f;
	GetposR() += (posRDest - GetposR())*0.9f;

	// ����p�x�ݒ�
	SetHorizontal(fHorizontal);
	SetVartical(fVartical);
}

//=============================================================================
// �J�����̈ʒu�C��
//=============================================================================
void CCameraGame::ModifyCamera(CGame::CAMERA_ID id)
{
	// �v���C���[�̃|�C���^
	CPlayer *pPlayer;
	CModeBase *pMode = CManager::GetModePtr();

	// �ʒu�C��
	pPlayer = ((CGame*)pMode)->GetPlayer(id);
	SetTargetPos(pPlayer->GetPos());
	CCamera::Update();
	CCamera::SetCamera();
}
