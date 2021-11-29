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
#include "player_ui_manager.h"
#include "map.h"
#include "object_wall.h"
#include "object_prison_door_left.h"
#include "object_prison_door_right.h"
#include "object_prison_wall.h"
//=======================================================================================
// �}�N����`
//=======================================================================================
#define FLOOR_SIZE	(D3DXVECTOR3(10000.0f,0.0f,10000.0f))	// ���̃T�C�Y
#define OBJECT_POS	(D3DXVECTOR3(1000.0f,0.0f,5000.0f))

#define PLAYER1_POS (D3DXVECTOR3(300.0f,0.0f,0.0f))
#define PLAYER2_POS (D3DXVECTOR3(-300.0f,0.0f,0.0f))

#define BATON_POS (D3DXVECTOR3(300.0f,0.0f,600.0f))
#define JAILER_ROOM_KEY_POS (D3DXVECTOR3(100.0f,0.0f,1500.0f))
#define MAP_POS (D3DXVECTOR3(-300.0f,0.0f,-600.0f))
#define PC_ROOM_KEY_POS (D3DXVECTOR3(600.0f,0.0f,300.0f))
#define PRISON_KEY_POS (D3DXVECTOR3(-600.0f,0.0f,-300.0f))
#define STORAGE_KEY_POS (D3DXVECTOR3(150.0f,0.0f,600.0f))

//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CGame::CGame()
{

	memset(&m_pCamera, 0, sizeof(m_pCamera));
	m_pLight = nullptr;
	m_pPlayerUIManager = nullptr;	// �v���C���[UI�}�l�[�W���[�̃|�C���^

	memset(m_apPlayer, NULL, sizeof(m_apPlayer));
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

	// �}�b�v����
	CMap::Create();

	// UI�̐���
	CScreenFrame::Create();
	CTimer::Create();
	m_pPlayerUIManager = CPlayerUIManager::Create();

	//�Ŏ�̐���
	CJailer::Create(ZeroVector3, ZeroVector3);

	//CJailer::Create(ZeroVector3, ZeroVector3);

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

	if (m_pPlayerUIManager != nullptr)
	{
		m_pPlayerUIManager->Uninit();
		delete m_pPlayerUIManager;
		m_pPlayerUIManager = nullptr;
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
	if (m_pPlayerUIManager != nullptr)
	{
		m_pPlayerUIManager->Update();
	}
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
	}
}

//=======================================================================================
// �A�C�e���̐���
//=======================================================================================
void CGame::CreateItem(void)
{
	CBatonObject::Create(BATON_POS, ZeroVector3);
	CJailerKeyObject::Create(JAILER_ROOM_KEY_POS, ZeroVector3);
	CMapObject::Create(MAP_POS, ZeroVector3);
	CPCRoomKeyObject::Create(PC_ROOM_KEY_POS, ZeroVector3);
	CPrisonKeyObject::Create(PRISON_KEY_POS, ZeroVector3);
	CStorageKeyObject::Create(STORAGE_KEY_POS, ZeroVector3);
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
