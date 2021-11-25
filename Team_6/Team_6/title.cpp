//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "title.h"
#include "renderer.h"
#include "input.h"
#include "scene_2d.h"
#include "fade.h"
#include "keyboard.h"
#include "texture.h"
#include "sound.h"
#include "joypad.h"
#include "resource_manager.h"
#include "camera.h"
#include "camera_title.h"
#include "light.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define LOGO_POS			(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 150.0f, 0.0f))
#define LOGO_SIZE			(D3DXVECTOR3(950.0f, 220.0f, 0.0f))
#define TITLE_PLAYER_POS	(D3DXVECTOR3(5000.0f, 0.0f, -20000.0f))
#define SHIP_PADDLE_ROTATE	(D3DXToRadian(1.0f))
#define KEYBORAD_MAX		(256)
// LightInfo
#define TITLE_LIGHT_VECDIR	(D3DXVECTOR3(-0.8f, -1.0f, 1.0f))

#define TRANSITION_WAIT_LENGTH	(90)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{
	m_pShip = nullptr;
	m_pObject2D.clear();
	m_pCamera = nullptr;
	m_pLight = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{
	// �I������
	Uninit();
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTitle::Init(void)
{
	// 3D�I�u�W�F�N�g����
	Create3DObject();

	// �J�E���^������
	m_nCountToMovie = 0;
	m_bCount = true;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTitle::Uninit(void)
{
	for (auto &object : m_pObject2D)
	{
		// �I������
		object->Uninit();
	}

	// �I�u�W�F�N�g�폜
	m_pObject2D.clear();

	// �J�����I������
	if (m_pCamera)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	// ���C�g�I������
	if (m_pLight)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	// �D�I������
	if (m_pShip)
	{
		m_pShip->Uninit();
		m_pShip = nullptr;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CTitle::Update(void)
{
	// �J�����X�V����
	if (m_pCamera)
	{
		m_pCamera->Update();
	}

	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();

	// �ǂ��̃L�[�ł���������l��
	for (int nCnt = ZERO_INT; nCnt <= KEYBORAD_MAX; nCnt++)
	{
		// �L�[�������ꂽ�����[�h�J�ڒ��łȂ��ꍇ
		if (pKey->GetTrigger(nCnt) && mode == CFade::FADE_MODE_NONE)
		{
			// ��ʑJ��
			ModeTransition(CManager::MODE_TYPE_GAME);
		}
	}
	// �R���g���[���̃{�^�����������ꍇ
	for (int nCnt = ZERO_INT; nCnt < CInputJoypad::JOY_BUTTON_MAX; nCnt++)
	{
		// �L�[�������ꂽ�����[�h�J�ڒ��łȂ��ꍇ
		if (CManager::GetJoypad()->GetJoystickTrigger(nCnt, 0) && mode == CFade::FADE_MODE_NONE)
		{
			// ��ʑJ��
			ModeTransition(CManager::MODE_TYPE_GAME);
		}
	}

	// ����J�n�܂ł̃J�E���^�[�����Z
	if (m_bCount)
	{
		m_nCountToMovie++;
	}
	if (m_nCountToMovie >= TRANSITION_WAIT_LENGTH)
	{
		m_nCountToMovie = 0;
		// ��ʑJ��
		ModeTransition(CManager::MODE_TYPE_MOVIE);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTitle::Draw(void)
{

}

//=============================================================================
// 2D�I�u�W�F�N�g����
//=============================================================================
void CTitle::Create2DObject(void)
{

}

//=============================================================================
// 3D�I�u�W�F�N�g����
//=============================================================================
void CTitle::Create3DObject(void)
{
	// �^�C�g���J�����̐���
	if (!m_pCamera)
	{
		m_pCamera = CCameraTitle::Create();
	}

	// ���C�g�̐���
	if (!m_pLight)
	{
		m_pLight = CLight::Create();
		m_pLight->SetVecDir(TITLE_LIGHT_VECDIR);
	}
}
//=============================================================================
// ���[�h�J��
//=============================================================================
void CTitle::ModeTransition(CManager::MODE_TYPE mode)
{
	// �J��
	CFade *pFade = CManager::GetFade();
	pFade->SetFade(mode);
	m_bCount = false;
	m_nCountToMovie = 0;
}