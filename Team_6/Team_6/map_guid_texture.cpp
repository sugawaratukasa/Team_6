//=============================================================================
//
// �}�b�v�����e�N�X�`�� [map_guid_texture.cpp]
// Author : ��K���@����
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "map_guid_texture.h"
#include "texture.h"
#include "manager.h"
#include "resource_manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMapGuidTexture::CMapGuidTexture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMapGuidTexture::~CMapGuidTexture()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CMapGuidTexture * CMapGuidTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CMapGuidTexture�̃|�C���^
	CMapGuidTexture *pMapGuidTexture = nullptr;

	// nullcheck
	if (pMapGuidTexture == nullptr)
	{
		// �������m��
		pMapGuidTexture = new CMapGuidTexture;

		// !nullcheck
		if (pMapGuidTexture != nullptr)
		{
			// ����������
			pMapGuidTexture->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pMapGuidTexture;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CMapGuidTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[��2D�̏����������֐��Ăяo��
	CScene2D::Init(pos, size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_MAP_GUID));
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CMapGuidTexture::Uninit(void)
{
	// �V�[��2D�̏I�������֐��Ăяo��
	CScene2D::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CMapGuidTexture::Update(void)
{
	// �V�[��2D�̍X�V�����֐��Ăяo��
	CScene2D::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CMapGuidTexture::Draw(void)
{
	// �V�[��2D�̕`�揈���֐��Ăяo��
	CScene2D::Draw();
}