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
CScreenFrame::CScreenFrame(PRIORITY Priority) : CScene(Priority)
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
HRESULT CScreenFrame::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	m_apTexture[FRAME_NORMAL] = pTexture->GetTexture(CTexture::TETXTURE_NUM_SCREENFRAME);
	m_apTexture[FRAME_SECCAM] = pTexture->GetTexture(CTexture::TETXTURE_NUM_SCREENFRAME_SECCAM);
	m_apTexture[FRAME_FUZZ]   = pTexture->GetTexture(CTexture::TETXTURE_NUM_SCREENFRAME_FUZZ);

	for (int nCount = 0; nCount < FRAME_MAX; nCount++)
	{
		m_pScene2D[nCount] = new CScene2D;
		m_pScene2D[nCount]->Init(D3DXVECTOR3(SCREEN_WIDTH / 4 + (SCREEN_WIDTH / 2.0f) * nCount, SCREEN_HEIGHT / 2, 0.0f),D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT, 0.0f));
		m_pScene2D[nCount]->BindTexture(m_apTexture[FRAME_NORMAL]);
		m_pScene2D[nCount]->SetIsDraw(false);
		m_nCountSec[nCount] = 0;
		m_bIsChanging[nCount] = false;
		m_bUseSecCamOld[nCount] = false;
	}

	m_bIsEnableCam = true;

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CScreenFrame::Update(void)
{
	for (int nCount = 0; nCount < FRAME_MAX; nCount++)
	{	
		bool bIsUseSecCamPlayer = CManager::GetRenderer()->GetIsUseSecCamPlayer(nCount);
		// �Ď��J�����Ƃ̐؂�ւ����N������
		if (m_bIsChanging[nCount])
		{
			// �Ď��J�������g�p���Ă��邩
			if (bIsUseSecCamPlayer)
			{
				// �������͂���Ŏw�肳�ꂽ�e�N�X�`���ɕύX
				ChangeCamera(nCount, m_apTexture[FRAME_SECCAM]);
			}
			else
			{
				// �������͂���Ŏw�肳�ꂽ�e�N�X�`���ɕύX
				ChangeCamera(nCount, m_apTexture[FRAME_NORMAL]);
			}
		}
		else
		{
			// 1�t���[���O�ƒ��g���Ⴄ�ꍇ
			if (m_bUseSecCamOld[nCount] != bIsUseSecCamPlayer)
			{
				// �؂�ւ����N����
				m_bIsChanging[nCount] = true;
			}
		}
		// �Ď��J�����g�p�󋵂�ۑ�
		m_bUseSecCamOld[nCount] = bIsUseSecCamPlayer;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScreenFrame::Draw(void)
{
	for (int nCount = 0; nCount < FRAME_MAX; nCount++)
	{
		m_pScene2D[nCount]->SetIsDraw(true);
		m_pScene2D[nCount]->Draw();
		m_pScene2D[nCount]->SetIsDraw(false);
	}
}

//=============================================================================
// �I������
//=============================================================================
void CScreenFrame::Uninit(void)
{
	for (int nCount = 0; nCount < FRAME_MAX; nCount++)
	{
		m_pScene2D[nCount]->Uninit();
		m_pScene2D[nCount] = NULL;
	}
	Release();
}

//=============================================================================
// �Ď��J�����؂�ւ�������
//=============================================================================
void CScreenFrame::ChangeCamera(int nFrameID, LPDIRECT3DTEXTURE9 pTex)
{
	m_nCountSec[nFrameID]++;
	m_pScene2D[nFrameID]->BindTexture(m_apTexture[FRAME_FUZZ]);

	// ��`�����t���[�����̊Ԃ���������`��
	if (m_nCountSec[nFrameID] >= FRAME_CHANGE_LENGTH && m_bIsEnableCam)
	{
		m_nCountSec[nFrameID] = 0;
		// �w�肳�ꂽ�e�N�X�`���ɕύX
		m_pScene2D[nFrameID]->BindTexture(pTex);
		m_bIsChanging[nFrameID] = false;
	}
}

//=============================================================================
// �C���X�^���X��������
//=============================================================================
CScreenFrame * CScreenFrame::Create(void)
{
	CScreenFrame *pFrame;
	pFrame = new CScreenFrame;
	pFrame->Init(ZeroVector3, ZeroVector3);

	return pFrame;
}
