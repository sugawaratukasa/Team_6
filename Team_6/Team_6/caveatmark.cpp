//=============================================================================
//
// �x���}�[�N [caveatmark.cpp]
// Author : Oguma Akira
//
//=============================================================================

//=============================================================================
// �}�N����`
//=============================================================================
#define DEF_SIZE (D3DXVECTOR3(50.0f, 50.0f, 0.0f))	//�e�N�X�`���̃f�t�H���g�T�C�Y
#define MAX_SIZE_X (540.0f)	//���̍ő�T�C�Y
#define MAX_BAR_RATIO (540.0f)	//�o�[�̍ő�䗦
#define INCDEC_COLOR_BAR (0.1f)	//�F�̑����l
#define SIZE_RATIO (MAX_SIZE_X / 4)	//�e�N�X�`���̊����ł̑傫��
#define MAX_COLOR_BAR (1.0f)	//�F�̍ő�l
#define MAX_FLASH_BAR (30)	//�_�ł̕b��

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "caveatmark.h"
#include "texture.h"
#include "resource_manager.h"
#include "manager.h"
#include "mode_base.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCaveatMark::CCaveatMark()
{
	m_state = NONE_STATE;
	m_nFrameCnt = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCaveatMark::~CCaveatMark()
{

}

//=============================================================================
// ����
//=============================================================================
CCaveatMark *CCaveatMark::Create(D3DXVECTOR3 pos)
{
	// CCaveatBar�̃|�C���^
	CCaveatMark *pCaveat = nullptr;

	// nullcheck
	if (pCaveat == nullptr)
	{
		pCaveat = new CCaveatMark;// �������m��

		// !nullcheck
		if (pCaveat != nullptr)
		{
			pCaveat->Init(pos);	// ����������
		}
	}
	// �|�C���^��Ԃ�
	return pCaveat;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CCaveatMark::Init(D3DXVECTOR3 pos)
{
	CScene2D::Init(pos, DEF_SIZE);

	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_CAVEAT));

	//�F�̐ݒ�
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================================================
// �X�V
//=============================================================================
void CCaveatMark::Update(void)
{
	CScene2D::Update();

	//�ԂɂȂ����ꍇ(Update�̏��ł��������Ȃ����߂����ł��)
	if (m_state == FLASH_STATE)
	{
		FlashCaveat(30);
	}
}

//=============================================================================
// �I��
//=============================================================================
void CCaveatMark::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �`��
//=============================================================================
void CCaveatMark::Drow(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �F�̏�ԕω�
//=============================================================================
void CCaveatMark::ColorState(State state)
{
	m_state = state;
	switch (state)
	{
	case CCaveatMark::FADEIN_STATE:
		if (0.0f < GetColor().a)
		{
			GetColor().a -= 0.1f;
		}
		break;

		//�ʏ�
	case CCaveatMark::NORMAL_STATE:
		//�F�̐ݒ�
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;

	default:
		break;
	}
}
//====================================================================
// �x���}�[�N�̓_��
//====================================================================
void CCaveatMark::FlashCaveat(int nFlashFlame)
{
		m_nFrameCnt++;
		if (m_nFrameCnt < nFlashFlame/2)
		{
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else if (m_nFrameCnt > nFlashFlame/2)
		{
			SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		}
		if (m_nFrameCnt == nFlashFlame)
		{
			m_nFrameCnt = 0;
		}
}


