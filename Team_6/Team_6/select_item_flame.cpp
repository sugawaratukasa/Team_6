//=============================================================================
//
// �I�����Ă�A�C�e���̘g [select_item_flame.cpp]
// Author : ��K���@����
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "select_item_flame.h"
#include "texture.h"
#include "manager.h"
#include "resource_manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSelectItemFlame::CSelectItemFlame(PRIORITY Priority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSelectItemFlame::~CSelectItemFlame()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CSelectItemFlame * CSelectItemFlame::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CSelectItemFlame�̃|�C���^
	CSelectItemFlame *pSelectItemFlame = nullptr;

	// nullcheck
	if (pSelectItemFlame == nullptr)
	{
		// �������m��
		pSelectItemFlame = new CSelectItemFlame;

		// !nullcheck
		if (pSelectItemFlame != nullptr)
		{
			// ����������
			pSelectItemFlame->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pSelectItemFlame;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CSelectItemFlame::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[��2D�̏����������֐�
	CScene2D::Init(pos, size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_SELECT_ITEM_FLAME));
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CSelectItemFlame::Uninit(void)
{
	// �V�[��2D�̏I�������֐�
	CScene2D::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CSelectItemFlame::Update(void)
{
	// �V�[��2D�̍X�V�����֐�
	CScene2D::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CSelectItemFlame::Draw(void)
{
	// �V�[��2D�̕`�揈���֐�
	CScene2D::Draw();
}
