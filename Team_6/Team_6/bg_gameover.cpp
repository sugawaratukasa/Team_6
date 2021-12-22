//=============================================================================
//
// �Q�[���I�[�o�[�w�i [bg_gameover.h]
// Author : ��K������
//
//=============================================================================
#include "main.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "scene_2d.h"
#include "bg_gameover.h"

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CGameOverBG::CGameOverBG(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CGameOverBG::~CGameOverBG()
{
}

//=============================================================================
// ���������֐�
// Author : Nikaido Taichi
//=============================================================================
CGameOverBG * CGameOverBG::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CGameOverBG�̃|�C���^
	CGameOverBG *pGameOverBG = nullptr;

	// nullcheck
	if (pGameOverBG == nullptr)
	{
		// �������m��
		pGameOverBG = new CGameOverBG;

		// !nullcheck
		if (pGameOverBG != nullptr)
		{
			// ����������
			pGameOverBG->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pGameOverBG;
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CGameOverBG::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[��2D�̏����������֐��Ăяo��
	CScene2D::Init(pos, size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_GAMEOVER));
	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CGameOverBG::Uninit(void)
{
	// �V�[��2D�̏I�������֐��Ăяo��
	CScene2D::Uninit();
}

//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CGameOverBG::Update(void)
{
	// �V�[��2D�̍X�V�����֐��Ăяo��
	CScene2D::Update();
}

//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CGameOverBG::Draw(void)
{
	// �V�[��2D�̕`�揈���֐��Ăяo��
	CScene2D::Draw();
}
