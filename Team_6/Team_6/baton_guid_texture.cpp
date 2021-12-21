//=============================================================================
//
// �x�_�����e�N�X�`�� [baton_guid_texture.cpp]
// Author : ��K���@����
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "baton_guid_texture.h"
#include "texture.h"
#include "manager.h"
#include "resource_manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBatonGuidTexture::CBatonGuidTexture(PRIORITY Priority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBatonGuidTexture::~CBatonGuidTexture()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CBatonGuidTexture * CBatonGuidTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CBatonGuidTexture�̃|�C���^
	CBatonGuidTexture *pBatonGuidTexture = nullptr;

	// nullcheck
	if (pBatonGuidTexture == nullptr)
	{
		// �������m��
		pBatonGuidTexture = new CBatonGuidTexture;

		// !nullcheck
		if (pBatonGuidTexture != nullptr)
		{
			// ����������
			pBatonGuidTexture->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pBatonGuidTexture;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CBatonGuidTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[��2D�̏����������֐��Ăяo��
	CScene2D::Init(pos, size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_BATON_GUID));
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CBatonGuidTexture::Uninit(void)
{
	// �V�[��2D�̏I�������֐��Ăяo��
	CScene2D::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CBatonGuidTexture::Update(void)
{
	// �V�[��2D�̍X�V�����֐��Ăяo��
	CScene2D::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CBatonGuidTexture::Draw(void)
{
	// �V�[��2D�̕`�揈���֐��Ăяo��
	CScene2D::Draw();
}
