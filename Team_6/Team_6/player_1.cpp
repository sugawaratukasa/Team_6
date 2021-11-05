#include "manager.h"
#include "game.h"
#include "camera.h"
#include "player_1.h"
#include "keyboard.h"
#include "joypad.h"
#include "resource_manager.h"

CPlayer1::CPlayer1(PRIORITY Priority)
{
	m_rotDest = ZeroVector3;
}

CPlayer1::~CPlayer1()
{
}

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
	return S_OK;
}

void CPlayer1::Uninit(void)
{
	// �v���C���[�̏I�������֐��Ăяo��
	CPlayer::Uninit();
}

void CPlayer1::Update(void)
{
	// �v���C���[�̍X�V�����֐��Ăяo��
	CPlayer::Update();
	//�s���s�\��Ԏ擾
	bool bIncapacitated = GetbIncapacitated();
	// �X�s�[�h�擾
	float fSpeed = GetSpeed();
	// �J�����p�x�擾
	float fAngle = GET_CAMERA_PTR->GetHorizontal();
	// �����s���\��Ԃ̏ꍇ
	if (bIncapacitated == false)
	{
		// �L�[�{�[�h�ړ�����
		KeyboardMove(fSpeed, fAngle);
		// �p�b�h�ړ�
		PadMove(fSpeed, fAngle);
	}
	else
	{
		SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	// �}�b�v�Ƃ̓����蔻��
	MapCollision();
}

void CPlayer1::Draw(void)
{
	// �v���C���[�̕`�揈���֐��Ăяo��
	CPlayer::Draw();
}

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
	if (pKeyboard->GetPress(DIK_W) && pKeyboard->GetPress(DIK_A))
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
// Author : Sugawara Tsukasa
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