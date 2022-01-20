//=============================================================================
// �v���C���[�s��UI [player_action_ui_1.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "player_action_ui.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"
#include "resource_manager.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define PLAYER1_POS_1	(D3DXVECTOR3(SCREEN_WIDTH / 4.0f,SCREEN_HEIGHT / 2.0f + 100.0f,0.0f))
#define PLAYER1_POS_2	(D3DXVECTOR3(SCREEN_WIDTH / 4.0f,SCREEN_HEIGHT / 2.0f + 150,0.0f))
#define PLAYER2_POS_1	(D3DXVECTOR3(SCREEN_WIDTH / 1.3f,SCREEN_HEIGHT / 2.0f + 100.0f,0.0f))
#define PLAYER2_POS_2	(D3DXVECTOR3(SCREEN_WIDTH / 1.3f,SCREEN_HEIGHT / 2.0f + 150.0f,0.0f))
#define SIZE_2D	(D3DXVECTOR3(361.0f, 87.0f,0.0f))
#define COL		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer_Action_UI::CPlayer_Action_UI()
{
	memset(m_apScene2D, NULL, sizeof(m_apScene2D));
	m_nPlayer_Type		= PLYER_TYPE_NONE;
	m_bInteract			= false;
	m_bItemGet			= false;
}
//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer_Action_UI::~CPlayer_Action_UI()
{
}
//=============================================================================
// ���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer_Action_UI * CPlayer_Action_UI::Create(int player_type)
{
	// CPlayer_Action_UI�̃|�C���^
	CPlayer_Action_UI *pPlayer_Action_UI = nullptr;

	// nullcheck
	if (pPlayer_Action_UI == nullptr)
	{
		// �������m��
		pPlayer_Action_UI = new CPlayer_Action_UI;

		// !nullcheck
		if (pPlayer_Action_UI != nullptr)
		{
			// �^�C�v���
			pPlayer_Action_UI->m_nPlayer_Type = player_type;

			// ����������
			pPlayer_Action_UI->Init();
		}
	}
	// �|�C���^��Ԃ�
	return pPlayer_Action_UI;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CPlayer_Action_UI::Init(void)
{
	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer_Action_UI::Uninit(void)
{
	// �ő吔�J��Ԃ�
	for (int nCnt = ZERO_INT; nCnt < TYPE_MAX; nCnt++)
	{
		// !nullcheck
		if (m_apScene2D[nCnt] != nullptr)
		{
			m_apScene2D[nCnt]->Uninit();
			m_apScene2D[nCnt] = nullptr;
		}
	}
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer_Action_UI::Update(void)
{
	// UI�����Ǘ�����
	UI_Create_Management();
}
//=============================================================================
// UI�����Ǘ������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer_Action_UI::UI_Create_Management(void)
{
	// �A�C�e�����擾�ł���ꍇ
	if (m_bItemGet == true)
	{
		// nullptr�̏ꍇ
		if (m_apScene2D[TYPE_X] == nullptr)
		{
			// player1�̏ꍇ
			if (m_nPlayer_Type == PLYER_TYPE_1)
			{
				// UI����
				m_apScene2D[TYPE_X] = CScene2D::Create(PLAYER1_POS_1, SIZE_2D);
			}
			// player2�̏ꍇ
			if (m_nPlayer_Type == PLYER_TYPE_2)
			{
				// UI����
				m_apScene2D[TYPE_X] = CScene2D::Create(PLAYER2_POS_1, SIZE_2D);
			}
				// �e�N�X�`���̐ݒ�
				CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
				m_apScene2D[TYPE_X]->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_PICKUP));

				// �F�ݒ�
				m_apScene2D[TYPE_X]->SetCol(COL);
			
		}
	}
	// �J�������g�p�ł���ꍇ
	if (m_bInteract == true)
	{
		// nullptr�̏ꍇ
		if (m_apScene2D[TYPE_A] == nullptr)
		{
			// player1�̏ꍇ
			if (m_nPlayer_Type == PLYER_TYPE_1)
			{
				// UI����
				m_apScene2D[TYPE_A] = CScene2D::Create(PLAYER1_POS_1, SIZE_2D);
			}
			// player2�̏ꍇ
			if (m_nPlayer_Type == PLYER_TYPE_2)
			{
				// UI����
				m_apScene2D[TYPE_A] = CScene2D::Create(PLAYER2_POS_1, SIZE_2D);
			}
			// !nullcheck
			if (m_apScene2D[TYPE_A] != nullptr)
			{
				// �e�N�X�`���̐ݒ�
				CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
				m_apScene2D[TYPE_A]->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_INTERACT));

				// �F�ݒ�
				m_apScene2D[TYPE_A]->SetCol(COL);
			}
		}
	}
	// �J�����A�h�A�A�_�N�g��false�̏ꍇ
	if (m_bInteract == false)
	{
		// nullptr�łȂ��ꍇ
		if (m_apScene2D[TYPE_A] != nullptr)
		{
			// �I��
			m_apScene2D[TYPE_A]->Uninit();

			// nullptr���
			m_apScene2D[TYPE_A] = nullptr;
		}
	}
	// �A�C�e����false�̏ꍇ
	if (m_bItemGet == false)
	{
		// nullptr�łȂ��ꍇ
		if (m_apScene2D[TYPE_X] != nullptr)
		{
			// �I��
			m_apScene2D[TYPE_X]->Uninit();

			// nullptr���
			m_apScene2D[TYPE_X] = nullptr;
		}
	}
	// �A�C�e���ƃC���^���N�g�̔��肪����ꍇ
	if (m_bItemGet == true && m_bInteract == true)
	{
		// X,A��nullptr�̏ꍇ
		if (m_apScene2D[TYPE_A] != nullptr && m_apScene2D[TYPE_X] != nullptr)
		{
			// player1�̏ꍇ
			if (m_nPlayer_Type == PLYER_TYPE_1)
			{
				// UI����
				m_apScene2D[TYPE_X]->SetPosition(PLAYER1_POS_1);
				m_apScene2D[TYPE_X]->SetVertex();

				// UI����
				m_apScene2D[TYPE_A]->SetPosition(PLAYER1_POS_2);
				m_apScene2D[TYPE_A]->SetVertex();
			}
			// player2�̏ꍇ
			if (m_nPlayer_Type == PLYER_TYPE_2)
			{
				// UI����
				m_apScene2D[TYPE_X]->SetPosition(PLAYER2_POS_1);
				m_apScene2D[TYPE_X]->SetVertex();

				// UI����
				m_apScene2D[TYPE_A]->SetPosition(PLAYER2_POS_2);
				m_apScene2D[TYPE_A]->SetVertex();
			}
		}
	}
}

void CPlayer_Action_UI::SetInteract(bool bCameraInteract)
{
	m_bInteract = bCameraInteract;
}

void CPlayer_Action_UI::SetbItemGet(bool bItemGet)
{
	m_bItemGet = bItemGet;
}
