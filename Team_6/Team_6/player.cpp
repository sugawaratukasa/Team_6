//=============================================================================
// �v���C���[ [player.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "player.h"
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "input.h"
#include "joypad.h"
#include "camera.h"
#include "game.h"
#include "sound.h"
#include "time.h"
#include "collision.h"
#include "fade.h"
#include "texture.h"
#include "resource_manager.h"
#include "motion.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define PLAYER_SPEED			(50.0f)									// �v���C���[�̈ړ���
#define STICK_SENSITIVITY		(50.0f)									// �X�e�B�b�N���x
#define PLAYER_ROT_SPEED		(0.1f)									// �L�����N�^�[�̉�]���鑬�x
#define SIZE					(D3DXVECTOR3 (1200.0f,1000.0f,1200.0f))	// �T�C�Y
#define STICK_INPUT_ZONE		(100)									// �X�e�B�b�N�̓��͔͈�
#define STICK_INPUT_ZONE_2		(1000)									// �X�e�B�b�N�̓��͔͈�
#define STICK_INPUT_ZERO		(0)										// �X�e�B�b�N�̓��͒l0
#define MIN_LIFE				(0)										// ���C�t�̍ŏ�
#define LIFE					(100)									// ���C�t
#define ANGLE_45				(D3DXToRadian(45.0f))					// �p�x45
#define ANGLE_90				(D3DXToRadian(90.0f))					// �p�x90
#define ANGLE_135				(D3DXToRadian(135.0f))					// �p�x90
#define ANGLE_180				(D3DXToRadian(180.0f))					// �p�x180
#define ANGLE_270				(D3DXToRadian(270.0f))					// �p�x270

//=============================================================================
// ���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer *pPlayer = new CPlayer;

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// ����������
		pPlayer->Init(pos, rot);
	}

	// CPlayer��Ԃ�
	return pPlayer;
}

//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer::CPlayer(PRIORITY Priority) : CCharacter(Priority)
{
	m_rotDest = ZeroVector3;
}

//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CXfile�擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f������
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_PLAYER);
	}

	// ����������
	CCharacter::Init(pos, rot);

	// ����
	m_rotDest = rot;

	// �T�C�Y�ݒ�
	SetSize(SIZE);

	// ���C�t�ݒ�
	SetLife(LIFE);

	// �X�s�[�h�ݒ�
	SetSpeed(PLAYER_SPEED);

	// �e
	SetUseShadow();

	// �e�̌���
	SetShadowRotCalculation();

	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::Uninit(void)
{
	CCharacter::Uninit();
}

//=============================================================================
// �X�V�֐������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::Update(void)
{
	// �X�V
	CCharacter::Update();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �Â��ʒu�ݒ�
	SetPosOld(pos);

	// �v���C���[�̏���
	PlayerControl();
}

//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::Draw(void)
{
	// �`��
	CCharacter::Draw();
}

//=============================================================================
// ��ԍX�V
// Author: Sugawara Tsukasa
//=============================================================================
void CPlayer::UpdateState(void)
{

}

//=============================================================================
// �v���C���[�̏���
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::PlayerControl()
{
	// �ړ�����
	Move();

	// �p�x�̍X�V����
	UpdateRot();
}

//=============================================================================
// �����X�V����
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::UpdateRot(void)
{
	// �����擾
	D3DXVECTOR3 rot = GetRot();

	// �������
	while (m_rotDest.y - rot.y > ANGLE_180)
	{
		m_rotDest.y -= D3DXToRadian(360);
	}

	while (m_rotDest.y - rot.y < -ANGLE_180)
	{
		m_rotDest.y += D3DXToRadian(360);
	}

	// ����
	rot += (m_rotDest - rot) * PLAYER_ROT_SPEED;

	// �����ݒ�
	SetRot(rot);
}

//=============================================================================
// �q�b�g�����֐�
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::Hit(int nDamage)
{
}

//=============================================================================
// ���S����
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::Death(void)
{
}

//=============================================================================
// �ړ�����
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::Move(void)
{	
	// �X�s�[�h�擾
	float fSpeed = GetSpeed();

	// �J�����p�x�擾
	float fAngle = GET_CAMERA_PTR->GetHorizontal();

	// �L�[�{�[�h�ړ�����
	KeyboardMove(fSpeed, fAngle);

	// �p�b�h�ړ�
	PadMove(fSpeed, fAngle);
}
//=============================================================================
// �L�[�{�[�h�ړ������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::KeyboardMove(float fSpeed, float fAngle)
{
	// �L�[�{�[�h�擾
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// �ړ���
	D3DXVECTOR3 move = ZeroVector3;

	// �����擾
	D3DXVECTOR3 rot = GetRot();

	// �O�Ɉړ�
	if (pKeyboard->GetPress(DIK_W))
	{
		// �ړ��ʁE�p�x�̐ݒ�
		move.x = -sinf(fAngle)*fSpeed;
		move.z = -cosf(fAngle)*fSpeed;
		m_rotDest.y = fAngle;
	}
	// ���Ɉړ�
	if (pKeyboard->GetPress(DIK_S))
	{
		// �ړ��ʁE�p�x�̐ݒ�
		move.x = sinf((fAngle))*fSpeed;
		move.z = cosf((fAngle))*fSpeed;
		m_rotDest.y = fAngle - ANGLE_180;
	}
	// ���Ɉړ�
	if (pKeyboard->GetPress(DIK_A))
	{
		// �ړ��ʁE�p�x�̐ݒ�
		move.x = sinf(fAngle + ANGLE_90)*fSpeed;
		move.z = cosf(fAngle + ANGLE_90)*fSpeed;
		m_rotDest.y = fAngle - ANGLE_90;
	}
	// �E�Ɉړ�
	if (pKeyboard->GetPress(DIK_D))
	{
		// �ړ��ʁE�p�x�̐ݒ�
		move.x = sinf(fAngle - ANGLE_90)*fSpeed;
		move.z = cosf(fAngle - ANGLE_90)*fSpeed;
		m_rotDest.y = fAngle + ANGLE_90;
	}
	// �O�Ɉړ�
	if (pKeyboard->GetPress(DIK_W)&& pKeyboard->GetPress(DIK_A))
	{
		// �ړ��ʁE�p�x�̐ݒ�
		move.x = -sinf(fAngle - ANGLE_45)*fSpeed;
		move.z = -cosf(fAngle - ANGLE_45)*fSpeed;
		m_rotDest.y = fAngle - ANGLE_45;
	}
	// �O�Ɉړ�
	if (pKeyboard->GetPress(DIK_W) && pKeyboard->GetPress(DIK_D))
	{
		// �ړ��ʁE�p�x�̐ݒ�
		move.x = -sinf(fAngle + ANGLE_45)*fSpeed;
		move.z = -cosf(fAngle + ANGLE_45)*fSpeed;
		m_rotDest.y = fAngle + ANGLE_45;
	}
	// �O�Ɉړ�
	if (pKeyboard->GetPress(DIK_S) && pKeyboard->GetPress(DIK_A))
	{
		// �ړ��ʁE�p�x�̐ݒ�
		move.x = -sinf(fAngle - ANGLE_135)*fSpeed;
		move.z = -cosf(fAngle - ANGLE_135)*fSpeed;
		m_rotDest.y = fAngle - ANGLE_135;
	}
	// �O�Ɉړ�
	if (pKeyboard->GetPress(DIK_S) && pKeyboard->GetPress(DIK_D))
	{
		// �ړ��ʁE�p�x�̐ݒ�
		move.x = -sinf(fAngle + ANGLE_135)*fSpeed;
		move.z = -cosf(fAngle + ANGLE_135)*fSpeed;
		m_rotDest.y = fAngle + ANGLE_135;
	}
	// �ړ��ʐݒ�
	SetMove(move);
}
//=============================================================================
// �p�b�h�ړ������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::PadMove(float fSpeed, float fAngle)
{
	// �p�b�h�擾
	LPDIRECTINPUTDEVICE8 P1_PAD = CInputJoypad::GetController(0);

	// !nullcheck 
	if (P1_PAD != nullptr)
	{
		// �X�e�B�b�N�擾
		DIJOYSTATE js = CInputJoypad::GetStick(0);

		// �ړ���
		D3DXVECTOR3 move = ZeroVector3;

		// ���͂���Ă���ꍇ
		if ((js.lX != ZERO_FLOAT || js.lY != ZERO_FLOAT))
		{
			// �R���g���[���̊p�x
			float fAngle3 = atan2f((float)js.lX, -(float)js.lY);
			float fAngle2 = atan2f(-(float)js.lX, (float)js.lY);

			// �ړ��ʐݒ�
			move.x = sinf(fAngle + (fAngle2))* fSpeed;
			move.z = cosf(fAngle + (fAngle2))* fSpeed;

			// �p�x�̐ݒ�
			m_rotDest.y = fAngle + (fAngle3);
		}
		else
		{
			// �ړ���0
			move = ZeroVector3;
		}

		// �ړ��ʐݒ�
		SetMove(move);
	}
}
//=============================================================================
// �U�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::Attack(void)
{
}
