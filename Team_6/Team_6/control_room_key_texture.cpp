//=============================================================================
//
// ���䎺�̌��e�N�X�`�� [control_room_key.cpp]
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
#include "control_room_key_texture.h"

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CControlKeyTexture::CControlKeyTexture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CControlKeyTexture::~CControlKeyTexture()
{
}

//=============================================================================
// ���������֐�
// Author : Nikaido Taichi
//=============================================================================
CControlKeyTexture * CControlKeyTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CControlKeyTexture�̃|�C���^
	CControlKeyTexture *pControlKeyTexture = nullptr;

	// nullcheck
	if (pControlKeyTexture == nullptr)
	{
		// �������m��
		pControlKeyTexture = new CControlKeyTexture;

		// !nullcheck
		if (pControlKeyTexture != nullptr)
		{
			// ����������
			pControlKeyTexture->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pControlKeyTexture;
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CControlKeyTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[��2D�̏����������֐��Ăяo��
	CScene2D::Init(pos, size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_CONTROL_KEY));
	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CControlKeyTexture::Uninit(void)
{
	// �V�[��2D�̏I�������֐��Ăяo��
	CScene2D::Uninit();
}

//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CControlKeyTexture::Update(void)
{
	// �V�[��2D�̍X�V�����֐��Ăяo��
	CScene2D::Update();
}

//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CControlKeyTexture::Draw(void)
{
	// �V�[��2D�̕`�揈���֐��Ăяo��
	CScene2D::Draw();
}
