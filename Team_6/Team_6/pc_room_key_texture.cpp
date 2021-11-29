#include "main.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "scene_2d.h"
#include "pc_room_key_texture.h"

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CPCRoomKeyTexture::CPCRoomKeyTexture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CPCRoomKeyTexture::~CPCRoomKeyTexture()
{
}

//=============================================================================
// ���������֐�
// Author : Nikaido Taichi
//=============================================================================
CPCRoomKeyTexture * CPCRoomKeyTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CPCRoomKeyTexture�̃|�C���^
	CPCRoomKeyTexture *pPCRoomKey = nullptr;

	// nullcheck
	if (pPCRoomKey == nullptr)
	{
		// �������m��
		pPCRoomKey = new CPCRoomKeyTexture;

		// !nullcheck
		if (pPCRoomKey != nullptr)
		{
			// ����������
			pPCRoomKey->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pPCRoomKey;
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CPCRoomKeyTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[��2D�̏����������֐��Ăяo��
	CScene2D::Init(pos, size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PC_ROOM_KEY));
	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CPCRoomKeyTexture::Uninit(void)
{
	// �V�[��2D�̏I�������֐��Ăяo��
	CScene2D::Uninit();
}

//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CPCRoomKeyTexture::Update(void)
{
	// �V�[��2D�̍X�V�����֐��Ăяo��
	CScene2D::Update();
}

//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CPCRoomKeyTexture::Draw(void)
{
	// �V�[��2D�̕`�揈���֐��Ăяo��
	CScene2D::Draw();
}
