//=============================================================================
//
// �x���o�[ [caveat.cpp]
// Author : Oguma Akira
//
//=============================================================================

//=============================================================================
// �}�N����`
//=============================================================================
#define DEF_SIZE (D3DXVECTOR3(0.0f, 100.0f, 0.0f))	//�e�N�X�`���̃f�t�H���g�T�C�Y
#define MAX_SIZE_X (540.0f)	//���̍ő�T�C�Y
#define MAX_BAR_RATIO (540.0f)	//�o�[�̍ő�䗦
#define INCDEC_COLOR_BAR (0.1f)	//�F�̑����l
#define SIZE_RATIO (MAX_SIZE_X / 4)	//�e�N�X�`���̊����ł̑傫��
#define MAX_COLOR_BAR (1.0f)	//�F�̍ő�l

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "caveatbar.h"
#include "caveatmark.h"
#include "texture.h"
#include "resource_manager.h"
#include "manager.h"
#include "mode_base.h"
#include "jailer_spot.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCaveatBar::CCaveatBar()
{
	m_fBarNow = ZERO_FLOAT;
	m_nPlayerNum = ZERO_INT;
	m_pCaveat = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCaveatBar::~CCaveatBar()
{

}

//=============================================================================
// ����
//=============================================================================
CCaveatBar *CCaveatBar::Create(D3DXVECTOR3 pos, const int nPlayer)
{
	// CCaveatBar�̃|�C���^
	CCaveatBar *pCaveatBar = nullptr;

	// nullcheck
	if (pCaveatBar == nullptr)
	{	
		pCaveatBar = new CCaveatBar;// �������m��

		// !nullcheck
		if (pCaveatBar != nullptr)
		{
			pCaveatBar->m_nPlayerNum = nPlayer;
			pCaveatBar->Init(pos);	// ����������
		}
	}
	// �|�C���^��Ԃ�
	return pCaveatBar;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CCaveatBar::Init(D3DXVECTOR3 pos)
{
	CScene2D::Init(pos, DEF_SIZE);
	//�x���}�[�N�̐���
	m_pCaveat = CCaveatMark::Create(D3DXVECTOR3(pos.x, pos.y - 50, pos.z));
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_CAVEATBAR));
	return S_OK;
}

//=============================================================================
// �X�V
//=============================================================================
void CCaveatBar::Update(void)
{
	//�x�N�g���̒���
	float fVecLength = VecLength();
	BarMove(fVecLength);

	//�x���}�[�N�̍X�V
	if (m_pCaveat!=nullptr)
	{
		m_pCaveat->Update();
	}
	CScene2D::Update();
}

//=============================================================================
// �I��
//=============================================================================
void CCaveatBar::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �`��
//=============================================================================
void CCaveatBar::Drow(void)
{
	CScene2D::Draw();
}


//=============================================================================
// �x�N�g���̒���
//=============================================================================
float CCaveatBar::VecLength(void)
{
	//�e�v���C���[���̎擾
	CPlayer *pPlayer = CManager::GetModePtr()->GetPlayer(m_nPlayerNum);
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

	float fLength = 1000000.0f;	//����

	//�e�Ŏ�̏��擾
	for (int nCntJalier = ZERO_INT; nCntJalier < MAX_JAILER; nCntJalier++)
	{
		//�Ŏ���̎擾
		CJailer *pJalier = CManager::GetModePtr()->GetJailer(nCntJalier);

		//�e�Ŏ�̋��鑤�Ɗe�v���C���[�����鑤����v���Ȃ��ꍇ
		if (pJalier->GetJailerSpot()->GetArea() != m_nPlayerNum)
		{
			continue;
		}

		D3DXVECTOR3 JalierPos = pJalier->GetPos();
		D3DXVECTOR3 distance = JalierPos - PlayerPos;
		float fdistance = D3DXVec3Length(&distance);	//�����擾

		//�e�Ŏ�ƃv���C���[�Ƃ̒�����r
		if (fdistance < fLength)
		{
			fLength = fdistance;
		}
	}
	return fLength;
}

//=============================================================================
//�o�[�̓���
//=============================================================================
void CCaveatBar::BarMove(const float fLength)
{
	//�ϐ��錾
	m_fBarNow = MAX_BAR_RATIO / fLength * MAX_SIZE_X;

	if (m_fBarNow < MAX_BAR_RATIO)
	{
		GetSize().x = m_fBarNow ;
		BarColor();
	}
}

//=============================================================================
// �o�[�̐F�ω�
//=============================================================================
void CCaveatBar::BarColor(void)
{
	D3DXCOLOR color = GetColor();
	//��
	if (m_fBarNow < MAX_SIZE_X / 3)
	{
		m_pCaveat->ColorState(CCaveatMark::FADEIN_STATE);
		if (ZERO_FLOAT < color.a)
		{
			color.a -= INCDEC_COLOR_BAR;
		}
		color = D3DXCOLOR(ZERO_FLOAT, MAX_COLOR_BAR, ZERO_FLOAT, color.a);

	}	
	//���F
	else if (m_fBarNow < MAX_SIZE_X / 1.5f)
	{
		m_pCaveat->ColorState(CCaveatMark::NORMAL_STATE);
		if (color.a < MAX_COLOR_BAR)
		{
			color.a += INCDEC_COLOR_BAR;
		}
		color = D3DXCOLOR(MAX_COLOR_BAR, MAX_COLOR_BAR, ZERO_FLOAT, color.a);
	}
	//��
	else
	{
		m_pCaveat->ColorState(CCaveatMark::FLASH_STATE);
		if (color.a < MAX_COLOR_BAR)
		{
			color.a += INCDEC_COLOR_BAR;
		}
		color = D3DXCOLOR(MAX_COLOR_BAR, ZERO_FLOAT, ZERO_FLOAT, color.a);
	}
	SetColor(color);
}
