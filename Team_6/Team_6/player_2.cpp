//=============================================================================
// �v���C���[2 [player_2.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Nikaido Taichi
//=============================================================================
#include "manager.h"
#include "game.h"
#include "player_2.h"
#include "keyboard.h"
#include "joypad.h"
#include "resource_manager.h"
#include "ui_player2_item.h"
#include "manager.h"
#include "resource_manager.h"
#include "sound.h"
#include "jailer_key_guid_texture.h"
#include "pc_room_key_guid_texture.h"

#include "electrical_room_key_guid_texture.h"
#include "storage_key_guid_texture.h"
#include "baton_guid_texture.h"
#include "map_guid_texture.h"
#include "control_room_key_guid_texture.h"
#include "guid_bg.h"
#include "camera_game.h"
#include "bg_black_texture.h"
#include "caveatbar.h"
#include "renderer.h"

//=============================================================================
// �}�N����`
// Author : Nikaido Taichi
//=============================================================================

#define PRISON_POSITION (D3DXVECTOR3(-538.0f, 0.0f, -7089.0f))	//�Ɩ[�̈ʒu

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CPlayer2::CPlayer2(PRIORITY Priority)
{
	m_rotDest = ZeroVector3;
	m_bBlackTextureCreate = false;
	m_pItemGuidTexture = nullptr;
	m_pGuidBG = nullptr;
	m_pBlackTexture = nullptr;
	m_pCaveatBar = nullptr;
}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CPlayer2::~CPlayer2()
{
}

//=============================================================================
// ���������֐�
// Author : Nikaido Taichi
//=============================================================================
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

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CPlayer2::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �^�C�v�ݒ�
	SetType(PLAYER_2);

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
	// �v���C���[2��UI����
	SetUI(CPlayer2ItemUI::Create());

	//�v���C���[2�̌x���o�[����
	m_pCaveatBar = CCaveatBar::Create(D3DXVECTOR3(SCREEN_WIDTH - 300.0f, SCREEN_HEIGHT - 100.0f, 0), PLAYER_2);

	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayer2::Uninit(void)
{
	// �v���C���[�̏I�������֐��Ăяo��
	CPlayer::Uninit();
}

//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayer2::Update(void)
{
	// �v���C���[�̍X�V�����֐��Ăяo��
	CPlayer::Update();
	// �s���s�\��Ԏ擾
	bool bIncapacitated = GetbIncapacitated();
	// �S�[����Ԏ擾
	bool bGoal = GetbGoal();
	// �A�C�e�������e�N�X�`���̐������
	bool bItemGuidCreate = GetbGuidCreate();
	// �X�s�[�h�擾
	float fSpeed = GetSpeed();
	// �J�����p�x�擾
	float fAngle = ((CGame*)CManager::GetModePtr())->GetCamera(1)->GetHorizontal();

	// �����_���[�擾
	CRenderer *pRenderer = CManager::GetRenderer();

	// �Ď��J�����g�p��Ԏ擾
	bool bCameraUse = pRenderer->GetIsUseSecCamPlayer(PLAYER_2);

	// �����s���\��Ԃ̏ꍇ
	if (bIncapacitated == false)
	{
		if (m_bBlackTextureCreate == true)
		{
			if (m_pBlackTexture != nullptr)
			{
				m_pBlackTexture->Uninit();
				m_pBlackTexture = nullptr;
				m_bBlackTextureCreate = false;
			}
		}
		// �J�������g���Ă��Ȃ��ꍇ
		if (bCameraUse == false)
		{
			// �L�[�{�[�h�ړ�����
			InputMove(fSpeed, fAngle);
		}
	}
	// �����s���s�\��Ԃ̏ꍇ���̓S�[����Ԃ̏ꍇ
	if (bIncapacitated == true || bItemGuidCreate == true || bGoal == true)
	{
		// �ړ��ʂ�0�ɂ���
		SetMove(ZeroVector3);
		// �ҋ@���[�V�����Đ�
		SetMotion(MOTION_IDOL);
	}
	if (bIncapacitated == true)
	{
		if (m_bBlackTextureCreate == false)
		{
			if (m_pBlackTexture == nullptr)
			{
				m_pBlackTexture = CBlackTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT, 0.0f));
				m_bBlackTextureCreate = true;
			}
		}
	}
	// �����␳����
	UpdateRot();
	if (bItemGuidCreate == false && bCameraUse == false)
	{
		// �A�C�e���폜�����֐��Ăяo��
		ItemDelete(PLAYER_2);
	}

	// �����J������
	DoorOpen(PLAYER_2);

	//�x���o�[����
	if (m_pCaveatBar != nullptr)
	{
		m_pCaveatBar->Update();
	}

	// �J�����g�p����
	UseSecurity_Cam(PLAYER_2);

	// �_�N�g�A�C�e���󂯓n��
	Item_DuctPass(PLAYER_2);
}

//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayer2::Draw(void)
{
	// �v���C���[�̕`�揈���֐��Ăяo��
	CPlayer::Draw();
}

//=============================================================================
// �Ɩ[���[�v�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayer2::PrisonWarp(void)
{
	// �T�E���h�̃|�C���^���擾����
	CSound * pSound = GET_SOUND_PTR;
	// ���[�v��SE���Đ�����
	pSound->Play(CSound::SOUND_SE_OPEN_PRISON);
	// �s���s�\��Ԃɂ���
	SetbIncapacitated(true);
	// �Ɩ[�Ƀ��[�v������
	SetPos(PRISON_POSITION);
}

//=============================================================================
// �A�C�e�������e�N�X�`���̐���
// Author : Nikaido Taichi
//=============================================================================
void CPlayer2::SetbGuidCreate(CItemObject::ITEM_OBJECT_LIST Type)
{

	if (m_pItemGuidTexture == nullptr && m_pGuidBG == nullptr)
	{
		m_pGuidBG = CGuidBG::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 0.0f));
		switch (Type)
		{
		case CItemObject::ITEM_OBJECT_KEY_STORAGE:
			m_pItemGuidTexture = CStorageKeyGuidTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 0.0f));
			SetbItemGuidCreate(true);
			break;
		case CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM:
			m_pItemGuidTexture = CJailerKeyGuidTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 0.0f));
			SetbItemGuidCreate(true);
			break;

		case CItemObject::ITEM_OBJECT_KEY_CONTOROL_ROOM:
			m_pItemGuidTexture = CControlRoomKeyGuidTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 0.0f));
			SetbItemGuidCreate(true);
			break;

		case CItemObject::ITEM_OBJECT_KEY_ELECTRICAL_ROOM:
			m_pItemGuidTexture = CElectricalRoomKeyGuidTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 0.0f));
			SetbItemGuidCreate(true);
			break;

		case CItemObject::ITEM_OBJECT_KEY_PC_ROOM:
			m_pItemGuidTexture = CPCRoomKeyGuidTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 0.0f));
			SetbItemGuidCreate(true);
			break;
		case CItemObject::ITEM_OBJECT_BATON:
			m_pItemGuidTexture = CBatonGuidTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 0.0f));
			SetbItemGuidCreate(true);
			break;
		case CItemObject::ITEM_OBJECT_MAP:
			m_pItemGuidTexture = CMapGuidTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 0.0f));
			SetbItemGuidCreate(true);
			break;
		default:
			break;
		}
	}
}

//=============================================================================
// �L�[�{�[�h�ړ������֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayer2::InputMove(float fSpeed, float fAngle)
{
	// �L�[�{�[�h�擾
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	CInputJoypad * pJoypad = CManager::GetJoypad();
	// �p�b�h�擾
	LPDIRECTINPUTDEVICE8 P2_PAD = CInputJoypad::GetController(PLAYER_2);
	// �ړ���
	D3DXVECTOR3 move = ZeroVector3;
	// �A�C�e�������e�N�X�`���̐������
	bool bItemGuidCreate = GetbGuidCreate();
	// �����擾
	D3DXVECTOR3 rot = GetRot();
	if (bItemGuidCreate == false)
	{
		// �O�Ɉړ�
		if (pKeyboard->GetPress(DIK_UP))
		{
			// �ړ��ʁE�p�x�̐ݒ�
			move.x = -sinf(fAngle)*fSpeed;
			move.z = -cosf(fAngle)*fSpeed;
			m_rotDest.y = fAngle;
			// ���s���[�V�����Đ�
			SetMotion(MOTION_WALK);
		}
		// ���Ɉړ�
		if (pKeyboard->GetPress(DIK_DOWN))
		{
			// �ړ��ʁE�p�x�̐ݒ�
			move.x = sinf((fAngle))*fSpeed;
			move.z = cosf((fAngle))*fSpeed;
			m_rotDest.y = fAngle - ANGLE_180;
			// ���s���[�V�����Đ�
			SetMotion(MOTION_WALK);
		}
		// ���Ɉړ�
		if (pKeyboard->GetPress(DIK_LEFT))
		{
			// �ړ��ʁE�p�x�̐ݒ�
			move.x = sinf(fAngle + ANGLE_90)*fSpeed;
			move.z = cosf(fAngle + ANGLE_90)*fSpeed;
			m_rotDest.y = fAngle - ANGLE_90;
			// ���s���[�V�����Đ�
			SetMotion(MOTION_WALK);
		}
		// �E�Ɉړ�
		if (pKeyboard->GetPress(DIK_RIGHT))
		{
			// �ړ��ʁE�p�x�̐ݒ�
			move.x = sinf(fAngle - ANGLE_90)*fSpeed;
			move.z = cosf(fAngle - ANGLE_90)*fSpeed;
			m_rotDest.y = fAngle + ANGLE_90;
			SetMotion(MOTION_WALK);
		}
		// �O�Ɉړ�
		if (pKeyboard->GetPress(DIK_UP) && pKeyboard->GetPress(DIK_LEFT))
		{
			// �ړ��ʁE�p�x�̐ݒ�
			move.x = -sinf(fAngle - ANGLE_45)*fSpeed;
			move.z = -cosf(fAngle - ANGLE_45)*fSpeed;
			m_rotDest.y = fAngle - ANGLE_45;
			// ���s���[�V�����Đ�
			SetMotion(MOTION_WALK);
		}
		// �O�Ɉړ�
		if (pKeyboard->GetPress(DIK_UP) && pKeyboard->GetPress(DIK_RIGHT))
		{
			// �ړ��ʁE�p�x�̐ݒ�
			move.x = -sinf(fAngle + ANGLE_45)*fSpeed;
			move.z = -cosf(fAngle + ANGLE_45)*fSpeed;
			m_rotDest.y = fAngle + ANGLE_45;
			// ���s���[�V�����Đ�
			SetMotion(MOTION_WALK);
		}
		// �O�Ɉړ�
		if (pKeyboard->GetPress(DIK_DOWN) && pKeyboard->GetPress(DIK_LEFT))
		{
			// �ړ��ʁE�p�x�̐ݒ�
			move.x = -sinf(fAngle - ANGLE_135)*fSpeed;
			move.z = -cosf(fAngle - ANGLE_135)*fSpeed;
			m_rotDest.y = fAngle - ANGLE_135;
			// ���s���[�V�����Đ�
			SetMotion(MOTION_WALK);
		}
		// �O�Ɉړ�
		if (pKeyboard->GetPress(DIK_DOWN) && pKeyboard->GetPress(DIK_RIGHT))
		{
			// �ړ��ʁE�p�x�̐ݒ�
			move.x = -sinf(fAngle + ANGLE_135)*fSpeed;
			move.z = -cosf(fAngle + ANGLE_135)*fSpeed;
			m_rotDest.y = fAngle + ANGLE_135;
			// ���s���[�V�����Đ�
			SetMotion(MOTION_WALK);
		}
		// !nullcheck 
		if (P2_PAD != nullptr)
		{
			// �X�e�B�b�N�擾
			DIJOYSTATE js = CInputJoypad::GetStick(PLAYER_2);
			// ���͂���Ă���ꍇ
			if ((js.lX != ZERO_FLOAT || js.lY != ZERO_FLOAT))
			{
				// �R���g���[���̊p�x
				float fAngle3 = atan2f((float)js.lX, -(float)js.lY);
				float fAngle2 = atan2f(-(float)js.lX, (float)js.lY);
				// ���s���[�V�����Đ�
				SetMotion(MOTION_WALK);
				// �ړ��ʐݒ�
				move.x = sinf(fAngle + (fAngle2))* fSpeed;
				move.z = cosf(fAngle + (fAngle2))* fSpeed;

				// �p�x�̐ݒ�
				m_rotDest.y = fAngle + (fAngle3);
			}
		}
	}
	else
	{
		if (pKeyboard->GetTrigger(DIK_NUMPADENTER) || pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_X, 1))
		{

			if (m_pItemGuidTexture != nullptr)
			{
				m_pItemGuidTexture->Uninit();
				m_pItemGuidTexture = nullptr;
			}
			if (m_pGuidBG != nullptr)
			{
				m_pGuidBG->Uninit();
				m_pGuidBG = nullptr;
			}
			SetbItemGuidCreate(false);
		}
	}
	if (move == ZeroVector3)
	{
		// �A�C�h�����[�V�����Đ�
		SetMotion(MOTION_IDOL);
	}
	// �ړ��ʐݒ�
	SetMove(move);
}

//=============================================================================
// �����X�V����
// Author : Nikaido Taichi
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
