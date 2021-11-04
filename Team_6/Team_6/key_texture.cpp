#include "main.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "scene_2d.h"
#include "key_texture.h"

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CKeyTexture::CKeyTexture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CKeyTexture::~CKeyTexture()
{
}

CKeyTexture * CKeyTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CKeyTexture�̃|�C���^
	CKeyTexture *pKeyTexture = nullptr;

	// nullcheck
	if (pKeyTexture == nullptr)
	{
		// �������m��
		pKeyTexture = new CKeyTexture;

		// !nullcheck
		if (pKeyTexture != nullptr)
		{
			// ����������
			pKeyTexture->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pKeyTexture;
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CKeyTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[��2D�̏����������֐��Ăяo��
	CScene2D::Init(pos, size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_KEY));
	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CKeyTexture::Uninit(void)
{
	// �V�[��2D�̏I�������֐��Ăяo��
	CScene2D::Uninit();
}

//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CKeyTexture::Update(void)
{
	// �V�[��2D�̍X�V�����֐��Ăяo��
	CScene2D::Update();
}

//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CKeyTexture::Draw(void)
{
	// �V�[��2D�̕`�揈���֐��Ăяo��
	CScene2D::Draw();
}
