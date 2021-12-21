//=============================================================================
//
// �|�[�Y���S�e�N�X�`�� [pause_logo_texture.cpp]
// Author : ��K���@����
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "pause_logo_texture.h"
#include "texture.h"
#include "manager.h"
#include "resource_manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPauseLogoTexture::CPauseLogoTexture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPauseLogoTexture::~CPauseLogoTexture()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CPauseLogoTexture * CPauseLogoTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CPauseLogoTexture�̃|�C���^
	CPauseLogoTexture *pPauseLogoTexture = nullptr;

	// nullcheck
	if (pPauseLogoTexture == nullptr)
	{
		// �������m��
		pPauseLogoTexture = new CPauseLogoTexture;

		// !nullcheck
		if (pPauseLogoTexture != nullptr)
		{
			// ����������
			pPauseLogoTexture->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pPauseLogoTexture;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CPauseLogoTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[��2D�̏����������֐��Ăяo��
	CScene2D::Init(pos, size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PAUSE_LOGO));
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CPauseLogoTexture::Uninit(void)
{
	// �V�[��2D�̏I�������֐��Ăяo��
	CScene2D::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CPauseLogoTexture::Update(void)
{
	// �V�[��2D�̍X�V�����֐��Ăяo��
	CScene2D::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CPauseLogoTexture::Draw(void)
{
	// �V�[��2D�̕`�揈���֐��Ăяo��
	CScene2D::Draw();
}
