#include "main.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "scene_2d.h"
#include "map1_texture.h"
#include "sound.h"

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CMap1Texture::CMap1Texture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CMap1Texture::~CMap1Texture()
{
}

CMap1Texture * CMap1Texture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CMap1Texture�̃|�C���^
	CMap1Texture *pMap1Texture = nullptr;

	// nullcheck
	if (pMap1Texture == nullptr)
	{
		// �������m��
		pMap1Texture = new CMap1Texture;

		// !nullcheck
		if (pMap1Texture != nullptr)
		{
			// ����������
			pMap1Texture->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pMap1Texture;
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CMap1Texture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[��2D�̏����������֐��Ăяo��
	CScene2D::Init(pos, size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_MAP1));
	CSound * pSound = GET_SOUND_PTR;
	pSound->CSound::Play(CSound::SOUND_SE_OPEN_MAP);
	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CMap1Texture::Uninit(void)
{
	// �V�[��2D�̏I�������֐��Ăяo��
	CScene2D::Uninit();
}

//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CMap1Texture::Update(void)
{
	// �V�[��2D�̍X�V�����֐��Ăяo��
	CScene2D::Update();
}

//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CMap1Texture::Draw(void)
{
	// �V�[��2D�̕`�揈���֐��Ăяo��
	CScene2D::Draw();
}
