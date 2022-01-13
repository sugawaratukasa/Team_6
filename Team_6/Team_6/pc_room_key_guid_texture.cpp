//=============================================================================
//
// PC���̌������e�N�X�`�� [number.cpp]
// Author : ��K���@����
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "pc_room_key_guid_texture.h"
#include "texture.h"
#include "manager.h"
#include "resource_manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPCRoomKeyGuidTexture::CPCRoomKeyGuidTexture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPCRoomKeyGuidTexture::~CPCRoomKeyGuidTexture()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CPCRoomKeyGuidTexture * CPCRoomKeyGuidTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CPCRoomKeyGuidTexture�̃|�C���^
	CPCRoomKeyGuidTexture *pPCRoomKeyGuidTexture = nullptr;

	// nullcheck
	if (pPCRoomKeyGuidTexture == nullptr)
	{
		// �������m��
		pPCRoomKeyGuidTexture = new CPCRoomKeyGuidTexture;

		// !nullcheck
		if (pPCRoomKeyGuidTexture != nullptr)
		{
			// ����������
			pPCRoomKeyGuidTexture->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pPCRoomKeyGuidTexture;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CPCRoomKeyGuidTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[��2D�̏����������֐��Ăяo��
	CScene2D::Init(pos, size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PC_ROOM_KEY_GUID));
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CPCRoomKeyGuidTexture::Uninit(void)
{
	// �V�[��2D�̏I�������֐��Ăяo��
	CScene2D::Uninit();
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CPCRoomKeyGuidTexture::Update(void)
{
	// �V�[��2D�̍X�V�����֐��Ăяo��
	CScene2D::Update();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CPCRoomKeyGuidTexture::Draw(void)
{
	// �V�[��2D�̕`�揈���֐��Ăяo��
	CScene2D::Draw();
}
