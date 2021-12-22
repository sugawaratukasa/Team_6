//=============================================================================
//
// �d�C���̌������e�N�X�`�� [electrical_key_guid_texture.cpp]
// Author : ��K���@����
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "electrical_room_key_guid_texture.h"
#include "texture.h"
#include "manager.h"
#include "resource_manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CElectricalRoomKeyGuidTexture::CElectricalRoomKeyGuidTexture(PRIORITY Priority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CElectricalRoomKeyGuidTexture::~CElectricalRoomKeyGuidTexture()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CElectricalRoomKeyGuidTexture * CElectricalRoomKeyGuidTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CElectricalRoomKeyGuidTexture�̃|�C���^
	CElectricalRoomKeyGuidTexture *pElectricalRoomKeyGuidTexture = nullptr;

	// nullcheck
	if (pElectricalRoomKeyGuidTexture == nullptr)
	{
		// �������m��
		pElectricalRoomKeyGuidTexture = new CElectricalRoomKeyGuidTexture;

		// !nullcheck
		if (pElectricalRoomKeyGuidTexture != nullptr)
		{
			// ����������
			pElectricalRoomKeyGuidTexture->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pElectricalRoomKeyGuidTexture;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CElectricalRoomKeyGuidTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[��2D�̏����������֐��Ăяo��
	CScene2D::Init(pos, size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_ELECTRICAL_KEY_GUID));
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CElectricalRoomKeyGuidTexture::Uninit(void)
{
	// �V�[��2D�̏I�������֐��Ăяo��
	CScene2D::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CElectricalRoomKeyGuidTexture::Update(void)
{
	// �V�[��2D�̍X�V�����֐��Ăяo��
	CScene2D::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CElectricalRoomKeyGuidTexture::Draw(void)
{
	// �V�[��2D�̕`�揈���֐��Ăяo��
	CScene2D::Draw();
}
