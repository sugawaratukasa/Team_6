//=============================================================================
//
// �Ɩ[�̌��̐����e�N�X�`�� [item_guid_prison_key.cpp]
// Author : ��K���@����
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "item_guid_prison_key.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "prison_key_texture.h"
#include "keyboard.h"
#include "joypad.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPrisonKeyGuid::CPrisonKeyGuid(PRIORITY Priority)
{
	m_pPrisonKeyTexture = nullptr;	// �Ŏ玺�̌��e�N�X�`���̃|�C���^
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPrisonKeyGuid::~CPrisonKeyGuid()
{
}

//=============================================================================
// ���������֐�
//=============================================================================
CPrisonKeyGuid * CPrisonKeyGuid::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CJailerKeyTexture�̃|�C���^
	CPrisonKeyGuid *pPrisonKeyGuid = nullptr;

	// nullcheck
	if (pPrisonKeyGuid == nullptr)
	{
		// �������m��
		pPrisonKeyGuid = new CPrisonKeyGuid;

		// !nullcheck
		if (pPrisonKeyGuid != nullptr)
		{
			// ����������
			pPrisonKeyGuid->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pPrisonKeyGuid;
}

//=============================================================================
// �����������֐�
//=============================================================================
HRESULT CPrisonKeyGuid::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �V�[��2D�̏����������֐��Ăяo��
	CScene2D::Init(pos, size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_JAILER_KEY));
	//�@�Ŏ玺�̌��e�N�X�`���̃|�C���^��nullptr�`�F�b�N
	if (m_pPrisonKeyTexture == nullptr)
	{
		// �Ŏ玺�̌��e�N�X�`���𐶐�����
		m_pPrisonKeyTexture = CPrisonKeyTexture::Create(ZeroVector3, ZeroVector3);
	}
	return S_OK;
}

//=============================================================================
// �I�������֐�
//=============================================================================
void CPrisonKeyGuid::Uninit(void)
{
	// �V�[��2D�̏I�������֐�
	CScene2D::Uninit();
	//�@�Ŏ玺�̌��e�N�X�`���̃|�C���^��nullptr�`�F�b�N
	if (m_pPrisonKeyTexture != nullptr)
	{
		//�@�Ŏ玺�̌��e�N�X�`���̏I�������֐�
		m_pPrisonKeyTexture->Uninit();
		// �Ŏ玺�̌��e�N�X�`���̃|�C���^������������
		m_pPrisonKeyTexture = nullptr;
	}
}

//=============================================================================
// �X�V�����֐�
//=============================================================================
void CPrisonKeyGuid::Update(void)
{
	// �V�[��2D�̍X�V�����֐�
	CScene2D::Update();
	//�@�Ŏ玺�̌��e�N�X�`���̃|�C���^��nullptr�`�F�b�N
	if (m_pPrisonKeyTexture != nullptr)
	{
		//�@�Ŏ玺�̌��e�N�X�`���̍X�V�����֐�
		m_pPrisonKeyTexture->Update();
	}
	// ���͏���
	Input();
}

//=============================================================================
// �`�揈���֐�
//=============================================================================
void CPrisonKeyGuid::Draw(void)
{
	// �V�[��2D�̕`�揈���֐�
	CScene2D::Draw();
	//�@�Ŏ玺�̌��e�N�X�`���̃|�C���^��nullptr�`�F�b�N
	if (m_pPrisonKeyTexture != nullptr)
	{
		// �Ŏ玺�̌��e�N�X�`���̕`�揈���֐�
		m_pPrisonKeyTexture->Draw();
	}
}

//=============================================================================
// ���͏����֐�
//=============================================================================
void CPrisonKeyGuid::Input(void)
{
	// �L�[�{�[�h�擾
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	// �p�b�h�擾
	CInputJoypad * pJoypad = CManager::GetJoypad();
	// ����ENTER�L�[�����͂��ꂽ��
	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		//�@�I�������֐�
		Uninit();
	}
}
