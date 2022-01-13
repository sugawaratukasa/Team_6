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

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCaveatBar::CCaveatBar()
{
	m_fUp = 0;
	m_fVecLength = 0;
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
CCaveatBar *CCaveatBar::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
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
			pCaveat->Init(pos, size);	// ����������
		}
	}
	// �|�C���^��Ԃ�
	return pCaveat;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CCaveatBar::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);

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
	// �L�[�{�[�h�擾
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	for (int nCntPlayer = ZERO_INT; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		////�v���C���[���̎擾
		CPlayer *pPlayer = CManager::GetModePtr()->GetPlayer(nCntPlayer);
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
		float fPlayerVec = ((PlayerPos.x * PlayerPos.x) + (PlayerPos.z * PlayerPos.z));
		for (int nCntPlayer = ZERO_INT; nCntPlayer < MAX_PLAYER; nCntPlayer++)
		{
			if (m_fUp >= 10.0f)
			{
				m_fUp = 0.0;
				GetSize().x = 0.0f;
				SetSize(GetSize());
			}
			else if (pKeyboard->GetPress(DIK_NUMPADENTER))
			{
				m_fUp += 0.1;
				//�o�[�̃T�C�Y�ύX
				GetSize().x += m_fUp;
				SetSize(GetSize());
			}
		}
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
