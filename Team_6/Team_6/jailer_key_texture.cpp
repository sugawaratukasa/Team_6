//=============================================================================
//
// �Ŏ玺�̌��e�N�X�`���e�N�X�`�� [item_guid_prison_key.cpp]
// Author : ��K���@����
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "scene_2d.h"
#include "jailer_key_texture.h"

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CJailerKeyTexture::CJailerKeyTexture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CJailerKeyTexture::~CJailerKeyTexture()
{
}

//=============================================================================
// ���������֐�
// Author : Nikaido Taichi
//=============================================================================
CJailerKeyTexture * CJailerKeyTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CJailerKeyTexture�̃|�C���^
	CJailerKeyTexture *pJailerKey = nullptr;

	// nullcheck
	if (pJailerKey == nullptr)
	{
		// �������m��
		pJailerKey = new CJailerKeyTexture;

		// !nullcheck
		if (pJailerKey != nullptr)
		{
			// ����������
			pJailerKey->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pJailerKey;
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CJailerKeyTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[��2D�̏����������֐��Ăяo��
	CScene2D::Init(pos, size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_JAILER_KEY));
	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CJailerKeyTexture::Uninit(void)
{
	// �V�[��2D�̏I�������֐��Ăяo��
	CScene2D::Uninit();
}

//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CJailerKeyTexture::Update(void)
{
	// �V�[��2D�̍X�V�����֐��Ăяo��
	CScene2D::Update();
}

//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CJailerKeyTexture::Draw(void)
{
	// �V�[��2D�̕`�揈���֐��Ăяo��
	CScene2D::Draw();
}
