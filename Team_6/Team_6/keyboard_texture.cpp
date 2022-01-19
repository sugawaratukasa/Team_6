#include "main.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "scene_2d.h"
#include "keyboard_texture.h"
#include "sound.h"

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CKeyboardTexture::CKeyboardTexture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CKeyboardTexture::~CKeyboardTexture()
{
}

CKeyboardTexture * CKeyboardTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CKeyboardTexture�̃|�C���^
	CKeyboardTexture *pKeyboardTexture = nullptr;

	// nullcheck
	if (pKeyboardTexture == nullptr)
	{
		// �������m��
		pKeyboardTexture = new CKeyboardTexture;

		// !nullcheck
		if (pKeyboardTexture != nullptr)
		{
			// ����������
			pKeyboardTexture->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pKeyboardTexture;
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CKeyboardTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[��2D�̏����������֐��Ăяo��
	CScene2D::Init(pos, size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_KEYBOARD_GUID));
	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CKeyboardTexture::Uninit(void)
{
	// �V�[��2D�̏I�������֐��Ăяo��
	CScene2D::Uninit();
}

//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CKeyboardTexture::Update(void)
{
	// �V�[��2D�̍X�V�����֐��Ăяo��
	CScene2D::Update();
}

//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CKeyboardTexture::Draw(void)
{
	// �V�[��2D�̕`�揈���֐��Ăяo��
	CScene2D::Draw();
}
