//=============================================================================
//
// �S���̌������e�N�X�`�� [number.cpp]
// Author : ��K���@����
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "prison_key_guid_texture.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CPrisonKeyGuidTexture::CPrisonKeyGuidTexture(PRIORITY Priority)
{
}


//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CPrisonKeyGuidTexture::~CPrisonKeyGuidTexture()
{
}


//=============================================================================
// ���������֐�
// Author : Nikaido Taichi
//=============================================================================
CPrisonKeyGuidTexture * CPrisonKeyGuidTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CPrisonKeyGuidTexture�̃|�C���^
	CPrisonKeyGuidTexture *pPrisonKeyGuidTexture = nullptr;

	// nullcheck
	if (pPrisonKeyGuidTexture == nullptr)
	{
		// �������m��
		pPrisonKeyGuidTexture = new CPrisonKeyGuidTexture;

		// !nullcheck
		if (pPrisonKeyGuidTexture != nullptr)
		{
			// ����������
			pPrisonKeyGuidTexture->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pPrisonKeyGuidTexture;
}


//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CPrisonKeyGuidTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[��2D�̏����������֐��Ăяo��
	CScene2D::Init(pos, size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PRISON_KEY_GUID));
	return S_OK;
}


//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CPrisonKeyGuidTexture::Uninit(void)
{
	// �V�[��2D�̕`�揈���֐��Ăяo��
	CScene2D::Uninit();
}


//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CPrisonKeyGuidTexture::Update(void)
{
	// �V�[��2D�̍X�V�����֐��Ăяo��
	CScene2D::Update();
}


//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CPrisonKeyGuidTexture::Draw(void)
{
	// �V�[��2D�̕`�揈���֐��Ăяo��
	CScene2D::Draw();
}
