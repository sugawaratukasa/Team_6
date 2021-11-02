#include "manager.h"
#include "game.h"
#include "camera.h"
#include "joypad.h"
#include "keyboard.h"
#include "player.h"
#include "player_2.h"
#include "resource_manager.h"

CPlayer2::CPlayer2(PRIORITY Priority)
{
}

CPlayer2::~CPlayer2()
{
}

CPlayer2 * CPlayer2::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CPlayer2�̃|�C���^
	CPlayer2 *pPlayer2 = nullptr;

	// nullcheck
	if (pPlayer2 == nullptr)
	{
		// �������m��
		pPlayer2 = new CPlayer2;

		// !nullcheck
		if (pPlayer2 != nullptr)
		{
			// ����������
			pPlayer2->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pPlayer2;
}

HRESULT CPlayer2::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CXfile�擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f������
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_PLAYER2);
	}
	// �v���C���[�̏����������֐��Ăяo��
	CPlayer::Init(pos, rot);
	return S_OK;
}

void CPlayer2::Uninit(void)
{
	// �v���C���[�̏I�������֐��Ăяo��
	CPlayer::Uninit();
}

void CPlayer2::Update(void)
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
}

void CPlayer2::Draw(void)
{
	// �v���C���[�̕`�揈���֐��Ăяo��
	CPlayer::Draw();
}

void CPlayer2::KeyboardMove(float fSpeed, float fAngle)
{
	// �L�[�{�[�h�擾
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// �ړ���
	D3DXVECTOR3 move = ZeroVector3;

	// �����擾
	D3DXVECTOR3 rot = GetRot();

	// �O�Ɉړ�
	if (pKeyboard->GetPress(DIK_UP))
	{
		// �ړ��ʁE�p�x�̐ݒ�
		move.x = -sinf(fAngle)*fSpeed;
		move.z = -cosf(fAngle)*fSpeed;
		m_rotDest.y = fAngle;
	}
	// ���Ɉړ�
	if (pKeyboard->GetPress(DIK_DOWN))
	{
		// �ړ��ʁE�p�x�̐ݒ�
		move.x = sinf((fAngle))*fSpeed;
		move.z = cosf((fAngle))*fSpeed;
		m_rotDest.y = fAngle - ANGLE_180;
	}
	// ���Ɉړ�
	if (pKeyboard->GetPress(DIK_LEFT))
	{
		// �ړ��ʁE�p�x�̐ݒ�
		move.x = sinf(fAngle + ANGLE_90)*fSpeed;
		move.z = cosf(fAngle + ANGLE_90)*fSpeed;
		m_rotDest.y = fAngle - ANGLE_90;
	}
	// �E�Ɉړ�
	if (pKeyboard->GetPress(DIK_RIGHT))
	{
		// �ړ��ʁE�p�x�̐ݒ�
		move.x = sinf(fAngle - ANGLE_90)*fSpeed;
		move.z = cosf(fAngle - ANGLE_90)*fSpeed;
		m_rotDest.y = fAngle + ANGLE_90;
	}
	// �O�Ɉړ�
	if (pKeyboard->GetPress(DIK_UP) && pKeyboard->GetPress(DIK_LEFT))
	{
		// �ړ��ʁE�p�x�̐ݒ�
		move.x = -sinf(fAngle - ANGLE_45)*fSpeed;
		move.z = -cosf(fAngle - ANGLE_45)*fSpeed;
		m_rotDest.y = fAngle - ANGLE_45;
	}
	// �O�Ɉړ�
	if (pKeyboard->GetPress(DIK_UP) && pKeyboard->GetPress(DIK_RIGHT))
	{
		// �ړ��ʁE�p�x�̐ݒ�
		move.x = -sinf(fAngle + ANGLE_45)*fSpeed;
		move.z = -cosf(fAngle + ANGLE_45)*fSpeed;
		m_rotDest.y = fAngle + ANGLE_45;
	}
	// �O�Ɉړ�
	if (pKeyboard->GetPress(DIK_DOWN) && pKeyboard->GetPress(DIK_LEFT))
	{
		// �ړ��ʁE�p�x�̐ݒ�
		move.x = -sinf(fAngle - ANGLE_135)*fSpeed;
		move.z = -cosf(fAngle - ANGLE_135)*fSpeed;
		m_rotDest.y = fAngle - ANGLE_135;
	}
	// �O�Ɉړ�
	if (pKeyboard->GetPress(DIK_DOWN) && pKeyboard->GetPress(DIK_RIGHT))
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
void CPlayer2::PadMove(float fSpeed, float fAngle)
{
	// �p�b�h�擾
	LPDIRECTINPUTDEVICE8 P1_PAD = CInputJoypad::GetController(1);

	// !nullcheck 
	if (P1_PAD != nullptr)
	{
		// �X�e�B�b�N�擾
		DIJOYSTATE js = CInputJoypad::GetStick(1);

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
void CPlayer2::UpdateRot(void)
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
