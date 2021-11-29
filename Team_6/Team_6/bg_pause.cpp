#include "main.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "scene_2d.h"
#include "bg_pause.h"

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CPauseBG::CPauseBG(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CPauseBG::~CPauseBG()
{
}

//=============================================================================
// ���������֐�
// Author : Nikaido Taichi
//=============================================================================
CPauseBG * CPauseBG::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CPause�̃|�C���^
	CPauseBG *pPauseBG = nullptr;

	// nullcheck
	if (pPauseBG == nullptr)
	{
		// �������m��
		pPauseBG = new CPauseBG;

		// !nullcheck
		if (pPauseBG != nullptr)
		{
			// ����������
			pPauseBG->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pPauseBG;
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CPauseBG::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[��2D�̏����������֐��Ăяo��
	CScene2D::Init(pos, size);
	SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f));
	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CPauseBG::Uninit(void)
{
	// �V�[��2D�̏I�������֐��Ăяo��
	CScene2D::Uninit();
}

//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CPauseBG::Update(void)
{
	// �V�[��2D�̍X�V�����֐��Ăяo��
	CScene2D::Update();
}

//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CPauseBG::Draw(void)
{
	// �V�[��2D�̕`�揈���֐��Ăяo��
	CScene2D::Draw();
}
