#include "bg_black_texture.h"
#include "texture.h"
#include "manager.h"
#include "resource_manager.h"

CBlackTexture::CBlackTexture(PRIORITY Priority) : CScene2D(Priority)
{
}

CBlackTexture::~CBlackTexture()
{
}

CBlackTexture * CBlackTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CBlackTexture�̃|�C���^
	CBlackTexture *pBlackTexture = nullptr;

	// nullcheck
	if (pBlackTexture == nullptr)
	{
		// �������m��
		pBlackTexture = new CBlackTexture;

		// !nullcheck
		if (pBlackTexture != nullptr)
		{
			// ����������
			pBlackTexture->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pBlackTexture;
}

HRESULT CBlackTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[��2D�̏����������֐��Ăяo��
	CScene2D::Init(pos, size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_IMPRISONMENT));
	return S_OK;
}

void CBlackTexture::Uninit(void)
{
	// �V�[��2D�̏I�������֐��Ăяo��
	CScene2D::Uninit();
}

void CBlackTexture::Update(void)
{
	// �V�[��2D�̍X�V�����֐��Ăяo��
	CScene2D::Update();
}

void CBlackTexture::Draw(void)
{
	// �V�[��2D�̕`�揈���֐��Ăяo��
	CScene2D::Draw();
}
