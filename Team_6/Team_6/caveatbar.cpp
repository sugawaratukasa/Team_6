//=============================================================================
//
// �x���o�[ [caveat.cpp]
// Author : Oguma Akira
//
//=============================================================================

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_BER (20)
#define DEFAULT_SIZE (D3DXVECTOR3(0.0f, 100.0f, 0.0f))	//�摜�̑傫��
#define MAX_SIZE_X (500.0f)

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "caveatbar.h"
#include "keyboard.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"
#include "player.h"
#include "jailer.h"
#include "manager.h"
#include "mode_base.h"
#include "jailer_spot.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCaveatBar::CCaveatBar()
{
	m_fUp = 0;
	m_fVecLength = 0;
	m_nPlayerNum = 0;

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
	CScene2D::Init(pos, DEFAULT_SIZE);

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
	SizeMove(fVecLength);

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
// �e�N�X�`���T�C�Y�̓���
//=============================================================================
void CCaveatBar::SizeMove(const float fLength)
{
	//�����ɂ����Bar�̒�����ς���
	GetSize().x = fLength - MAX_SIZE_X;;
	SetSize(GetSize());

	if (GetSize().x > ZERO_INT)
	{
		GetSize().x = ZERO_FLOAT;
		SetSize(GetSize());
	}
}
