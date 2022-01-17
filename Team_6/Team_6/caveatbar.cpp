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
	CCaveatBar *pCaveat = nullptr;

	// nullcheck
	if (pCaveat == nullptr)
	{	
		pCaveat = new CCaveatBar;// �������m��

		// !nullcheck
		if (pCaveat != nullptr)
		{
			pCaveat->m_nPlayerNum = nPlayer;
			pCaveat->Init(pos);	// ����������
		}
	}
	// �|�C���^��Ԃ�
	return pCaveat;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CCaveatBar::Init(D3DXVECTOR3 pos)
{
	CScene2D::Init(pos, DEF_SIZE);

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
	//�䗦�̌��E�l�܂�
	if (fLength >= MAX_BAR_RATIO)
	{
		//�ϐ��錾
		m_fBarNow = MAX_BAR_RATIO / fLength * MAX_SIZE_X;
		GetSize().x = m_fBarNow;
		BarColor();
	}
}

//=============================================================================
// �o�[�̐F�ω�
//=============================================================================
void CCaveatBar::BarColor(void)
{
	D3DXCOLOR color = GetColor();
	color.b = ZERO_FLOAT;	//�͎g��Ȃ�
	//��
	if (m_fBarNow < MAX_SIZE_X / 3 && ZERO_FLOAT <= color.a)
	{
		
		color.a -= INCDEC_COLOR_BAR;
		color.g = MAX_COLOR_BAR;
		color.r = ZERO_FLOAT;
	}	
	//���F
	else if (m_fBarNow < MAX_SIZE_X / 1.5f && color.a >= MAX_COLOR_BAR)
	{
		color.a += INCDEC_COLOR_BAR;
		color.g = MAX_COLOR_BAR;
		color.r = MAX_COLOR_BAR;
	}
	//��
	else
	{
		color.a += INCDEC_COLOR_BAR;
		color.r = MAX_COLOR_BAR;
		color.g = ZERO_FLOAT;
	}

	SetColor(color);
}
