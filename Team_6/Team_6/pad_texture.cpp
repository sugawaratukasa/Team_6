#include "main.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "scene_2d.h"
#include "pad_texture.h"
#include "sound.h"

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CPadTexture::CPadTexture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CPadTexture::~CPadTexture()
{
}

CPadTexture * CPadTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CPadTexture�̃|�C���^
	CPadTexture *pPadTexture = nullptr;

	// nullcheck
	if (pPadTexture == nullptr)
	{
		// �������m��
		pPadTexture = new CPadTexture;

		// !nullcheck
		if (pPadTexture != nullptr)
		{
			// ����������
			pPadTexture->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pPadTexture;
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CPadTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[��2D�̏����������֐��Ăяo��
	CScene2D::Init(pos, size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_PAD_GUID));
	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CPadTexture::Uninit(void)
{
	// �V�[��2D�̏I�������֐��Ăяo��
	CScene2D::Uninit();
}

//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CPadTexture::Update(void)
{
	// �V�[��2D�̍X�V�����֐��Ăяo��
	CScene2D::Update();
}

//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CPadTexture::Draw(void)
{
	// �V�[��2D�̕`�揈���֐��Ăяo��
	CScene2D::Draw();
}
