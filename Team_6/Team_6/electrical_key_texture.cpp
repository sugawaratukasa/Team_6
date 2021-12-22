#include "main.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "scene_2d.h"
#include "electrical_key_texture.h"

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CElectricalKeyTexture::CElectricalKeyTexture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CElectricalKeyTexture::~CElectricalKeyTexture()
{
}

//=============================================================================
// ���������֐�
// Author : Nikaido Taichi
//=============================================================================
CElectricalKeyTexture * CElectricalKeyTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CElectricalKeyTexture�̃|�C���^
	CElectricalKeyTexture *pPrisonKey = nullptr;

	// nullcheck
	if (pPrisonKey == nullptr)
	{
		// �������m��
		pPrisonKey = new CElectricalKeyTexture;

		// !nullcheck
		if (pPrisonKey != nullptr)
		{
			// ����������
			pPrisonKey->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pPrisonKey;
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CElectricalKeyTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[��2D�̏����������֐��Ăяo��
	CScene2D::Init(pos, size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_ELECTRICAL_KEY));
	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CElectricalKeyTexture::Uninit(void)
{
	// �V�[��2D�̏I�������֐��Ăяo��
	CScene2D::Uninit();
}

//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CElectricalKeyTexture::Update(void)
{
	// �V�[��2D�̍X�V�����֐��Ăяo��
	CScene2D::Update();
}

//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CElectricalKeyTexture::Draw(void)
{
	// �V�[��2D�̕`�揈���֐��Ăяo��
	CScene2D::Draw();
}
