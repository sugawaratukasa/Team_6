//=============================================================================
//
// �^�C�g���w�i [bg_pause.h]
// Author : ��K������
//
//=============================================================================
#include "main.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "scene_2d.h"
#include "bg_title.h"

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CTitleBG::CTitleBG(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CTitleBG::~CTitleBG()
{
}

//=============================================================================
// ���������֐�
// Author : Nikaido Taichi
//=============================================================================
CTitleBG * CTitleBG::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CKeyTexture�̃|�C���^
	CTitleBG *pTitleBG = nullptr;

	// nullcheck
	if (pTitleBG == nullptr)
	{
		// �������m��
		pTitleBG = new CTitleBG;

		// !nullcheck
		if (pTitleBG != nullptr)
		{
			// ����������
			pTitleBG->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pTitleBG;
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CTitleBG::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[��2D�̏����������֐��Ăяo��
	CScene2D::Init(pos, size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_TITLE_BG));
	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CTitleBG::Uninit(void)
{
	// �V�[��2D�̏I�������֐��Ăяo��
	CScene2D::Uninit();
}

//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CTitleBG::Update(void)
{
	// �V�[��2D�̍X�V�����֐��Ăяo��
	CScene2D::Update();
}

//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CTitleBG::Draw(void)
{
	// �V�[��2D�̕`�揈���֐��Ăяo��
	CScene2D::Draw();
}
