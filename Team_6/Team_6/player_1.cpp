//=============================================================================
// �v���C���[1 [player_1.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Nikaido Taichi
//=============================================================================
#include "manager.h"
#include "game.h"
#include "player_1.h"
#include "keyboard.h"
#include "joypad.h"
#include "resource_manager.h"
#include "player1_ui.h"

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CPlayer1::CPlayer1(PRIORITY Priority)
{
	m_rotDest = ZeroVector3;
}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CPlayer1::~CPlayer1()
{
}

//=============================================================================
// ���������֐�
// Author : Nikaido Taichi
//=============================================================================
CPlayer1 * CPlayer1::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CPlayer1�̃|�C���^
	CPlayer1 *pPlayer1 = nullptr;

	// nullcheck
	if (pPlayer1 == nullptr)
	{
		// �������m��
		pPlayer1 = new CPlayer1;

		// !nullcheck
		if (pPlayer1 != nullptr)
		{
			// ����������
			pPlayer1->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pPlayer1;
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CPlayer1::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CXfile�擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f������
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_PLAYER1);
	}
	// �v���C���[�̏����������֐��Ăяo��
	CPlayer::Init(pos, rot);
	// �X�s�[�h�ݒ�
	SetSpeed(PLAYER_SPEED);
	// �v���C���[1��UI����
	SetUI(CPlayer1UI::Create());
	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayer1::Uninit(void)
{
	// �v���C���[�̏I�������֐��Ăяo��
	CPlayer::Uninit();
}

//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayer1::Update(void)
{
	// �v���C���[�̍X�V�����֐��Ăяo��
	CPlayer::Update();
	// �s���s�\��Ԏ擾
	bool bIncapacitated = GetbIncapacitated();
	// �S�[����Ԏ擾
	bool bGoal = GetbGoal();
	// �X�s�[�h�擾
	float fSpeed = GetSpeed();
	// �J�����p�x�擾
	float fAngle = CAM_HORIZONTAL_ANGLE;
	// �����s���\��Ԃ̏ꍇ
	if (bIncapacitated == false)
	{
		// �L�[�{�[�h�ړ�����
		KeyboardMove(fSpeed, fAngle);
		// �p�b�h�ړ�
		PadMove(fSpeed, fAngle);
	}
	// �����s���s�\��Ԃ̏ꍇ���̓S�[����Ԃ̏ꍇ
	if(bIncapacitated == true || bGoal == true)
	{
		// �ړ��ʂ�0�ɂ���
		SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	UpdateRot();
	// �A�C�e���폜�����֐��Ăяo��
	ItemDelete(0);
}

//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayer1::Draw(void)
{
	// �v���C���[�̕`�揈���֐��Ăяo��
	CPlayer::Draw();
}

//=============================================================================
// �Ɩ[���[�v�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayer1::PrisonWarp(void)
{
	// �s���s�\��Ԏ擾
	bool bIncapacitated = GetbIncapacitated();
	// �s���s�\��Ԃɂ���
	bIncapacitated = true;
	SetbIncapacitated(bIncapacitated);
	// �Ɩ[�Ƀ��[�v������
	SetPos(D3DXVECTOR3(5760.0f, 0.0f, -5900.0f));
}

//=============================================================================
// �L�[�{�[�h�ړ������֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayer1::KeyboardMove(float fSpeed, float fAngle)
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
		SetMotion(1);
	}
	// ���Ɉړ�
	if (pKeyboard->GetPress(DIK_S))
	{
		// �ړ��ʁE�p�x�̐ݒ�
		move.x = sinf((fAngle))*fSpeed;
		move.z = cosf((fAngle))*fSpeed;
		m_rotDest.y = fAngle - ANGLE_180;
		SetMotion(1);
	}
	// ���Ɉړ�
	if (pKeyboard->GetPress(DIK_A))
	{
		// �ړ��ʁE�p�x�̐ݒ�
		move.x = sinf(fAngle + ANGLE_90)*fSpeed;
		move.z = cosf(fAngle + ANGLE_90)*fSpeed;
		m_rotDest.y = fAngle - ANGLE_90;
		SetMotion(1);
	}
	// �E�Ɉړ�
	if (pKeyboard->GetPress(DIK_D))
	{
		// �ړ��ʁE�p�x�̐ݒ�
		move.x = sinf(fAngle - ANGLE_90)*fSpeed;
		move.z = cosf(fAngle - ANGLE_90)*fSpeed;
		m_rotDest.y = fAngle + ANGLE_90;
		SetMotion(1);
	}
	// �O�Ɉړ�
	if (pKeyboard->GetPress(DIK_W) && pKeyboard->GetPress(DIK_A))
	{
		// �ړ��ʁE�p�x�̐ݒ�
		move.x = -sinf(fAngle - ANGLE_45)*fSpeed;
		move.z = -cosf(fAngle - ANGLE_45)*fSpeed;
		m_rotDest.y = fAngle - ANGLE_45;
		SetMotion(1);
	}
	// �O�Ɉړ�
	if (pKeyboard->GetPress(DIK_W) && pKeyboard->GetPress(DIK_D))
	{
		// �ړ��ʁE�p�x�̐ݒ�
		move.x = -sinf(fAngle + ANGLE_45)*fSpeed;
		move.z = -cosf(fAngle + ANGLE_45)*fSpeed;
		m_rotDest.y = fAngle + ANGLE_45;
		SetMotion(1);
	}
	// �O�Ɉړ�
	if (pKeyboard->GetPress(DIK_S) && pKeyboard->GetPress(DIK_A))
	{
		// �ړ��ʁE�p�x�̐ݒ�
		move.x = -sinf(fAngle - ANGLE_135)*fSpeed;
		move.z = -cosf(fAngle - ANGLE_135)*fSpeed;
		m_rotDest.y = fAngle - ANGLE_135;
		SetMotion(1);
	}
	// �O�Ɉړ�
	if (pKeyboard->GetPress(DIK_S) && pKeyboard->GetPress(DIK_D))
	{
		// �ړ��ʁE�p�x�̐ݒ�
		move.x = -sinf(fAngle + ANGLE_135)*fSpeed;
		move.z = -cosf(fAngle + ANGLE_135)*fSpeed;
		m_rotDest.y = fAngle + ANGLE_135;
		SetMotion(1);
	}
	if (move == ZeroVector3)
	{
		SetMotion(0);
	}
	// �ړ��ʐݒ�
	SetMove(move);
}

//=============================================================================
// �p�b�h�ړ������֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayer1::PadMove(float fSpeed, float fAngle)
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
// �����X�V����
// Author : Nikaido Taichi
//=============================================================================
void CPlayer1::UpdateRot(void)
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