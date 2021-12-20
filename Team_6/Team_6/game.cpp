//=======================================================================================
//
// �Q�[������ [game.cpp]
// Author : Sugawara Tsukasa
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h
//=======================================================================================
#include "game.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "player_1.h"
#include "player_2.h"
#include "joypad.h"
#include "time.h"
#include "sound.h"
#include "keyboard.h"
#include "resource_manager.h"
#include "library.h"
#include "debug_proc.h"
#include "camera_game.h"
#include "floor.h"
#include "fade.h"
#include "object.h"
#include "Screenframe.h"
#include "Timer.h"
#include "jailer.h"
#include "item_object_baton.h"
#include "item_object_jailer_room_key.h"
#include "item_object_map.h"
#include "item_object_pc_room_key.h"
#include "item_object_prison_key.h"
#include "item_object_storage_key.h"
#include "map.h"
#include "object_wall.h"
#include "object_prison_door_left.h"
#include "object_prison_door_right.h"
#include "object_prison_wall.h"
#include "pause_button_manager.h"
#include "player1_ui.h"
#include "lever.h"
#include "particle_emitter.h"

//=======================================================================================
// �}�N����`
//=======================================================================================
#define FLOOR_SIZE	(D3DXVECTOR3(10000.0f,0.0f,10000.0f))	// ���̃T�C�Y
#define OBJECT_POS	(D3DXVECTOR3(1000.0f,0.0f,5000.0f))

#define PLAYER1_POS (D3DXVECTOR3(5768.0f,0.0f,-14056.0f))
#define PLAYER2_POS (D3DXVECTOR3(-1350.0f,0.0f,-250.0f))
#define MAP_POS1 (D3DXVECTOR3(5768.0f,0.0f,-12888.0f))
#define MAP_POS2 (D3DXVECTOR3(-1312.0f,0.0f,-5348.0f))
#define PRISON_KEY_POS1 (D3DXVECTOR3(2460.0f,0.0f,-9729.0f))
#define PRISON_KEY_POS2 (D3DXVECTOR3(-1050.0f,0.0f,-9027.0f))
#define STORAGE_KEY_POS1 (D3DXVECTOR3(2881.0f,0.0f,-9729.0f))
#define STORAGE_KEY_POS2 (D3DXVECTOR3(1943.0f,0.0f,-2438.0f))
#define PC_ROOM_KEY_POS1 (D3DXVECTOR3(4528.0f,0.0f,-4735.0f))
#define PC_ROOM_KEY_POS2 (D3DXVECTOR3(1930.0f,0.0f,-1880.0f))
#define JAILER_ROOM_KEY_POS1 (D3DXVECTOR3(4495.0f,0.0f,-2724.0f))
#define JAILER_ROOM_KEY_POS2 (D3DXVECTOR3(-1350.0f,0.0f,1000.0f))
#define BATON_POS1 (D3DXVECTOR3(5330.0f,0.0f,289.0f))
#define BATON_POS2 (D3DXVECTOR3(-547.0f,0.0f,-5331.0f))
#define POS	(D3DXVECTOR3(0.0f,50.0f,0.0f))


//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CGame::CGame()
{
	memset(&m_pCamera, 0, sizeof(m_pCamera));
	m_pLight = nullptr;
	memset(m_apPlayer, NULL, sizeof(m_apPlayer));
	m_pPauseButtonManager = nullptr;
	m_pFont = nullptr;
}

//=======================================================================================
// �f�X�g���N�^
//=======================================================================================
CGame::~CGame()
{
	// �I������
	Uninit();
}

//=======================================================================================
// ����������
//=======================================================================================
HRESULT CGame::Init(void)
{
	// �J�����N���X�̃N���G�C�g

	m_pCamera[ID_PLAYER_01] = CCameraGame::Create(CCamera::SCREEN_LEFT);
	m_pCamera[ID_PLAYER_02] = CCameraGame::Create(CCamera::SCREEN_RIGHT);

	//���C�g�N���X�̐���
	m_pLight = new CLight;

	// ���C�g�̏���������
	if (m_pLight != nullptr)
	{
		if (FAILED(m_pLight->Init()))
		{
			return -1;
		}
	}
	// �v���C���[�̐���
	CreatePlayer();
	// �A�C�e���̐���
	CreateItem();
	// ����
	CreateGround();
	//
	// �Ď��J�����̐���
	CreateSecCam();

	// �}�b�v����	
	CMap::Create();

	// UI�̐���
	CScreenFrame::Create();
	CTimer::Create();

	//�Ŏ�̐���
	CJailer::Create(ZeroVector3, ZeroVector3);
	/*CJailer::Create(ZeroVector3, ZeroVector3);
	CJailer::Create(ZeroVector3, ZeroVector3);
	CJailer::Create(ZeroVector3, ZeroVector3);*/

	CParticle_Emitter::Create(ZeroVector3, CParticle_Manager::TYPE_ITEM_RAINBOW);
	return S_OK;
}
//=======================================================================================
// �I������
//=======================================================================================
void CGame::Uninit(void)
{
	for (int nCount = 0; nCount < ID_PLAYER_MAX; nCount++)
	{
		if (m_pCamera[nCount] != nullptr)
		{
			//�J�����N���X�̏I�������Ăяo��
			m_pCamera[nCount]->Uninit();

			//�������̔j��
			delete m_pCamera[nCount];

			//�������̃N���A
			m_pCamera[nCount] = nullptr;
		}
	}

	// ���C�g�̏I������
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}



	for (int nCount = 0; nCount < 2; nCount++)
	{

		if (m_apPlayer[nCount] != NULL)
		{
			m_apPlayer[nCount]->Uninit();
			m_apPlayer[nCount] = nullptr;
		}
	}

	// �f�o�b�O���\���p�t�H���g�̔j��
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
}

//=======================================================================================
// �X�V����
//=======================================================================================
void CGame::Update(void)
{
	for (int nCount = 0; nCount < ID_PLAYER_MAX; nCount++)
	{

		if (m_pCamera[nCount] != nullptr)
		{
			//�J�����N���X�̍X�V����
			m_pCamera[nCount]->Update();
		}
	}
	// �|�[�Y���͏���
	PauseInput();
	// �Q�[���̐ݒ�
	SetGame();
}

//=======================================================================================
// �`�揈��
//=======================================================================================
void CGame::Draw(void)
{
}

//=======================================================================================
// �Q�[���̐ݒ�
//=======================================================================================
void CGame::SetGame(void)
{
}

//=======================================================================================
// �v���C���[�̐���
//=======================================================================================
void CGame::CreatePlayer(void)
{
	// �v���C���[�̐���

	if (m_apPlayer[0] == nullptr)
	{
		m_apPlayer[0] = CPlayer1::Create(PLAYER1_POS, ZeroVector3);
	}
	// �v���C���[�̐���
	if (m_apPlayer[1] == nullptr)
	{
		m_apPlayer[1] = CPlayer2::Create(PLAYER2_POS, ZeroVector3);
		CStorageKeyObject::Create(PLAYER2_POS, ZeroVector3);
	}
}

//=======================================================================================
// �A�C�e���̐���
//=======================================================================================
void CGame::CreateItem(void)
{
	CMapObject::Create(MAP_POS1, ZeroVector3);
	CPrisonKeyObject::Create(PRISON_KEY_POS1, ZeroVector3);
	CStorageKeyObject::Create(STORAGE_KEY_POS1, ZeroVector3);
	CPCRoomKeyObject::Create(PC_ROOM_KEY_POS1, ZeroVector3);
	CJailerKeyObject::Create(JAILER_ROOM_KEY_POS1, ZeroVector3);
	CBatonObject::Create(BATON_POS1, ZeroVector3);

	CJailerKeyObject::Create(JAILER_ROOM_KEY_POS2, ZeroVector3);
	CStorageKeyObject::Create(STORAGE_KEY_POS2, ZeroVector3);
	CPCRoomKeyObject::Create(PC_ROOM_KEY_POS2, ZeroVector3);
	CPrisonKeyObject::Create(PRISON_KEY_POS2, ZeroVector3);
	CMapObject::Create(MAP_POS2, ZeroVector3);
	CBatonObject::Create(BATON_POS2, ZeroVector3);
}

//=======================================================================================
// �}�b�v�̐���
//=======================================================================================
void CGame::CreateMap(void)
{
	// �n�ʂ̐���
	CreateGround();
}

//=======================================================================================
// �n�ʂ̐���
//=======================================================================================
void CGame::CreateGround(void)
{
	
}


//=======================================================================================
// �|�[�Y���͏���
//=======================================================================================
void CGame::PauseInput(void)
{
	// �L�[�{�[�h�擾
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	if (m_pPauseButtonManager == nullptr)
	{
		if (pKeyboard->GetTrigger(DIK_ESCAPE))
		{
			m_pPauseButtonManager = CPauseButtonManager::Create();
		}
	}
	else
	{
		m_pPauseButtonManager->Update();
		if (pKeyboard->GetTrigger(DIK_ESCAPE))
		{
			CScene::SetPause(false);
		}
		if (CScene::GetPause() == false)
		{
			m_pPauseButtonManager->Uninit();
			m_pPauseButtonManager = nullptr;
		}
	}
}

//=======================================================================================
// �Ď��J�����̐���
//=======================================================================================
void CGame::CreateSecCam(void)
{
	m_pCamera[0]->CreateSecCam(D3DXVECTOR3(-1600.0f, 275.0f, -794.0f), 90.0f);
	m_pCamera[0]->CreateSecCam(D3DXVECTOR3(1000.0f, 275.0f, 0.0f), 0.0f);
	m_pCamera[0]->CreateSecCam(D3DXVECTOR3(-1000.0f, 275.0f, 0.0f), 0.0f);
	m_pCamera[0]->CreateSecCam(D3DXVECTOR3(0.0f, 275.0f, 1000.0f), 0.0f);
	m_pCamera[0]->CreateSecCam(D3DXVECTOR3(0.0f, 275.0f, -1000.0f), 0.0f);
}