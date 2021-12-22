#include "main.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "scene_2d.h"
#include "map2_texture.h"
#include "sound.h"

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CMap2Texture::CMap2Texture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CMap2Texture::~CMap2Texture()
{
}

CMap2Texture * CMap2Texture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CMap2Texture�̃|�C���^
	CMap2Texture *pMap2Texture = nullptr;

	// nullcheck
	if (pMap2Texture == nullptr)
	{
		// �������m��
		pMap2Texture = new CMap2Texture;

		// !nullcheck
		if (pMap2Texture != nullptr)
		{
			// ����������
			pMap2Texture->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pMap2Texture;
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CMap2Texture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[��2D�̏����������֐��Ăяo��
	CScene2D::Init(pos, size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_MAP2));
	CSound * pSound = GET_SOUND_PTR;
	pSound->CSound::Play(CSound::SOUND_SE_OPEN_MAP);
	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CMap2Texture::Uninit(void)
{
	// �V�[��2D�̏I�������֐��Ăяo��
	CScene2D::Uninit();
}

//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CMap2Texture::Update(void)
{
	// �V�[��2D�̍X�V�����֐��Ăяo��
	CScene2D::Update();
}

//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CMap2Texture::Draw(void)
{
	// �V�[��2D�̕`�揈���֐��Ăяo��
	CScene2D::Draw();
}
