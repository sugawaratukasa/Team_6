//=============================================================================
//
// ��ʕ���UI���� [screenframe.cpp]
// Author : ��{ ��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "Screenframe.h"
#include "renderer.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9 CScreenFrame::m_apTexture[MAX_FRAME_TEX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScreenFrame::CScreenFrame(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScreenFrame::~CScreenFrame()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScreenFrame::Init(void)
{
	CScene2D::Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	m_apTexture[FRAME_NORMAL] = pTexture->GetTexture(CTexture::TETXTURE_NUM_SCREENFRAME);
	m_apTexture[FRAME_SECCAM] = pTexture->GetTexture(CTexture::TETXTURE_NUM_SCREENFRAME_SECCAM);
	m_apTexture[FRAME_FUZZ]   = pTexture->GetTexture(CTexture::TETXTURE_NUM_SCREENFRAME_FUZZ);
	BindTexture(m_apTexture[FRAME_NORMAL]);

	m_nCountSec = 0;
	m_bIsChanging = false;
	m_bUseSecCamOld = false;

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CScreenFrame::Update(void)
{
	bool bIsUseSecCam = CManager::GetRenderer()->GetIsUseSecCam();

	if (m_bIsChanging)
	{
		if (bIsUseSecCam)
		{
			ChangeCamera(m_apTexture[FRAME_SECCAM]);
		}
		else
		{
			ChangeCamera(m_apTexture[FRAME_NORMAL]);
		}
	}
	else
	{
		if (m_bUseSecCamOld != bIsUseSecCam)
		{
			m_bIsChanging = true;
		}
		else
		{
			if (bIsUseSecCam)
			{
				BindTexture(m_apTexture[FRAME_SECCAM]);
			}
			else
			{
				BindTexture(m_apTexture[FRAME_NORMAL]);
			}
		}
	}

	m_bUseSecCamOld = bIsUseSecCam;

	CScene2D::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScreenFrame::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �I������
//=============================================================================
void CScreenFrame::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �Ď��J�����؂�ւ�������
//=============================================================================
void CScreenFrame::ChangeCamera(LPDIRECT3DTEXTURE9 pTex)
{
	m_nCountSec++;
	BindTexture(m_apTexture[FRAME_FUZZ]);

	if (m_nCountSec >= FRAME_CHANGE_LENGTH)
	{
		m_nCountSec = 0;
		BindTexture(pTex);
		m_bIsChanging = false;
	}
}

//=============================================================================
// �C���X�^���X��������
//=============================================================================
CScreenFrame * CScreenFrame::Create(void)
{
	CScreenFrame *pFrame;
	pFrame = new CScreenFrame;
	pFrame->Init();

	return pFrame;
}
