//=======================================================================================
//
// UI�̘g�e�N�X�`�� [ui_flame_texture.cpp]
// Author : Sugawara Tsukasa
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h�t�@�C��
//=======================================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "resource_manager.h"
#include "texture.h"
#include "scene_2d.h"
#include "ui_flame_texture.h"

#define COLOR (D3DXCOLOR(1.0f,1.0f,1.0f,0.8f))

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CUIFlameTexture::CUIFlameTexture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CUIFlameTexture::~CUIFlameTexture()
{
}

CUIFlameTexture * CUIFlameTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CUIFlameTexture�̃|�C���^
	CUIFlameTexture *pUIFlameTexture = nullptr;

	// nullcheck
	if (pUIFlameTexture == nullptr)
	{
		// �������m��
		pUIFlameTexture = new CUIFlameTexture;

		// !nullcheck
		if (pUIFlameTexture != nullptr)
		{
			// ����������
			pUIFlameTexture->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pUIFlameTexture;
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CUIFlameTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[��2D�̏����������֐��Ăяo��
	CScene2D::Init(pos, size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_UI_FLAME));
	SetCol(COLOR);
	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CUIFlameTexture::Uninit(void)
{
	// �V�[��2D�̏I�������֐��Ăяo��
	CScene2D::Uninit();
}

//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CUIFlameTexture::Update(void)
{
	// �V�[��2D�̍X�V�����֐��Ăяo��
	CScene2D::Update();
}

//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CUIFlameTexture::Draw(void)
{
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 50);
	pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	// �V�[��2D�̕`�揈���֐��Ăяo��
	CScene2D::Draw();
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
