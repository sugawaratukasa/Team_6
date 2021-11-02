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
#include "player.h"
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

//=======================================================================================
// �}�N����`
//=======================================================================================
#define FLOOR_SIZE	(D3DXVECTOR3(10000.0f,0.0f,10000.0f))	// ���̃T�C�Y
#define OBJECT_POS	(D3DXVECTOR3(1000.0f,0.0f,5000.0f))
//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CGame::CGame()
{
	memset(&m_pCamera, 0, sizeof(m_pCamera));
	m_pLight = nullptr;
	m_pPlayer = nullptr;
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

	// ����
	CreateGround();

	// UI�̐���
	CScreenFrame::Create();
	CTimer::Create();

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

	// �v���C���[�̏I������
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		m_pPlayer = nullptr;
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
	// �v���C���[�̈ʒu�`��
	//DrawPlayerPos();

	for (int nCount = 0; nCount < ID_PLAYER_MAX; nCount++)
	{
		if (m_pCamera[nCount] != nullptr)
		{
			//�J�����N���X�̍X�V����
			m_pCamera[nCount]->Update();
		}
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
	if (m_pPlayer == nullptr)
	{
		//m_pPlayer = CPlayer::Create(ZeroVector3, ZeroVector3);
	}
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
	// ������
	CFloor::Create(ZeroVector3, FLOOR_SIZE);

	CObject::Create(OBJECT_POS, ZeroVector3);
}

//=======================================================================================
// �v���C���[�̏��
// Author : SugawaraTsukasa
//=======================================================================================
void CGame::DrawPlayerPos(void)
{
	// �v���C���[�̈ʒu�擾
	D3DXVECTOR3 PlayerPos = m_pPlayer->GetPos();

	// ��������
	CDebugProc::Print("POS:X%.1f Y%.1f Z%.1f", PlayerPos.x, PlayerPos.y, PlayerPos.z);
}