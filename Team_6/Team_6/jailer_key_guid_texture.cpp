//=============================================================================
//
// �Ŏ玺�̌������e�N�X�`�� [jailer_key_guid_texture.cpp]
// Author : ��K���@����
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "jailer_key_guid_texture.h"
#include "texture.h"
#include "manager.h"
#include "resource_manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CJailerKeyGuidTexture::CJailerKeyGuidTexture(PRIORITY Priority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CJailerKeyGuidTexture::~CJailerKeyGuidTexture()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CJailerKeyGuidTexture * CJailerKeyGuidTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CJailerKeyGuidTexture�̃|�C���^
	CJailerKeyGuidTexture *pJailerKeyGuidTexture = nullptr;

	// nullcheck
	if (pJailerKeyGuidTexture == nullptr)
	{
		// �������m��
		pJailerKeyGuidTexture = new CJailerKeyGuidTexture;

		// !nullcheck
		if (pJailerKeyGuidTexture != nullptr)
		{
			// ����������
			pJailerKeyGuidTexture->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pJailerKeyGuidTexture;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CJailerKeyGuidTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[��2D�̏����������֐��Ăяo��
	CScene2D::Init(pos, size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_JAILER_KEY_GUID));
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CJailerKeyGuidTexture::Uninit(void)
{
	// �V�[��2D�̏I�������֐��Ăяo��
	CScene2D::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CJailerKeyGuidTexture::Update(void)
{
	// �V�[��2D�̍X�V�����֐��Ăяo��
	CScene2D::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CJailerKeyGuidTexture::Draw(void)
{
	// �V�[��2D�̕`�揈���֐��Ăяo��
	CScene2D::Draw();
}
