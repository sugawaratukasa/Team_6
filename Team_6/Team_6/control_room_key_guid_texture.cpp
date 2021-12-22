//=============================================================================
//
// ���䎺�̌������e�N�X�`�� [control_room_key_guid_texture.cpp]
// Author : ��K���@����
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "scene_2d.h"
#include "control_room_key_guid_texture.h"

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CControlRoomKeyGuidTexture::CControlRoomKeyGuidTexture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CControlRoomKeyGuidTexture::~CControlRoomKeyGuidTexture()
{
}

//=============================================================================
// ���������֐�
// Author : Nikaido Taichi
//=============================================================================
CControlRoomKeyGuidTexture * CControlRoomKeyGuidTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CControlRoomKeyGuidTexture�̃|�C���^
	CControlRoomKeyGuidTexture *pControlRoomKeyGuidTexture = nullptr;

	// nullcheck
	if (pControlRoomKeyGuidTexture == nullptr)
	{
		// �������m��
		pControlRoomKeyGuidTexture = new CControlRoomKeyGuidTexture;

		// !nullcheck
		if (pControlRoomKeyGuidTexture != nullptr)
		{
			// ����������
			pControlRoomKeyGuidTexture->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pControlRoomKeyGuidTexture;
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CControlRoomKeyGuidTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[��2D�̏����������֐��Ăяo��
	CScene2D::Init(pos, size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_CONTROL_KEY_GUID));
	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CControlRoomKeyGuidTexture::Uninit(void)
{
	// �V�[��2D�̏I�������֐��Ăяo��
	CScene2D::Uninit();
}

//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CControlRoomKeyGuidTexture::Update(void)
{
	// �V�[��2D�̍X�V�����֐��Ăяo��
	CScene2D::Update();
}

//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CControlRoomKeyGuidTexture::Draw(void)
{
	// �V�[��2D�̕`�揈���֐��Ăяo��
	CScene2D::Draw();
}
