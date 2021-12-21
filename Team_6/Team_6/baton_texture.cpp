//=============================================================================
//
// �{�^���e�N�X�`�� [bg_pause.h]
// Author : ��K������
//
//=============================================================================
#include "main.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "scene_2d.h"
#include "baton_texture.h"

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CBatonTexture::CBatonTexture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CBatonTexture::~CBatonTexture()
{
}

//=============================================================================
// ���������֐�
// Author : Nikaido Taichi
//=============================================================================
CBatonTexture * CBatonTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CBatonTexture�̃|�C���^
	CBatonTexture *pBatonTexture = nullptr;

	// nullcheck
	if (pBatonTexture == nullptr)
	{
		// �������m��
		pBatonTexture = new CBatonTexture;

		// !nullcheck
		if (pBatonTexture != nullptr)
		{
			// ����������
			pBatonTexture->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pBatonTexture;
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CBatonTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[��2D�̏����������֐��Ăяo��
	CScene2D::Init(pos, size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_BATON));
	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CBatonTexture::Uninit(void)
{
	// �V�[��2D�̏I�������֐��Ăяo��
	CScene2D::Uninit();
}

//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CBatonTexture::Update(void)
{
	// �V�[��2D�̍X�V�����֐��Ăяo��
	CScene2D::Update();
}

//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CBatonTexture::Draw(void)
{
	// �V�[��2D�̕`�揈���֐��Ăяo��
	CScene2D::Draw();
}
