//=============================================================================
//
// �q�ɂ̌������e�N�X�`�� [storage_key_guid_texture.cpp]
// Author : ��K���@����
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "storage_key_guid_texture.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CStorageKeyGuidTexture::CStorageKeyGuidTexture(PRIORITY Priority) : CScene2D(Priority)
{
}


//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CStorageKeyGuidTexture::~CStorageKeyGuidTexture()
{
}


//=============================================================================
// ���������֐�
// Author : Nikaido Taichi
//=============================================================================
CStorageKeyGuidTexture * CStorageKeyGuidTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CPrisonKeyGuidTexture�̃|�C���^
	CStorageKeyGuidTexture *pStorageKeyGuidTexture = nullptr;

	// nullcheck
	if (pStorageKeyGuidTexture == nullptr)
	{
		// �������m��
		pStorageKeyGuidTexture = new CStorageKeyGuidTexture;

		// !nullcheck
		if (pStorageKeyGuidTexture != nullptr)
		{
			// ����������
			pStorageKeyGuidTexture->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pStorageKeyGuidTexture;
}


//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CStorageKeyGuidTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[��2D�̏����������֐��Ăяo��
	CScene2D::Init(pos, size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_STORAGE_KEY_GUID));
	return S_OK;
}


//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CStorageKeyGuidTexture::Uninit(void)
{
	// �V�[��2D�̕`�揈���֐��Ăяo��
	CScene2D::Uninit();
}


//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CStorageKeyGuidTexture::Update(void)
{
	// �V�[��2D�̍X�V�����֐��Ăяo��
	CScene2D::Update();
}


//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CStorageKeyGuidTexture::Draw(void)
{
	// �V�[��2D�̕`�揈���֐��Ăяo��
	CScene2D::Draw();
}
