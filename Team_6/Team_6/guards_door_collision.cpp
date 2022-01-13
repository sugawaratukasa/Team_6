//=============================================================================
// �Ŏ玺�h�A�̔��� [guards_door_collision.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "guards_door_collision.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(150.0f,550.0f,150.0f))	// �T�C�Y
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CGuards_Door_Collision::CGuards_Door_Collision(PRIORITY Priority) : CDoor_Collision(Priority)
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CGuards_Door_Collision::~CGuards_Door_Collision()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CGuards_Door_Collision * CGuards_Door_Collision::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CDoor *pDoor)
{
	// CGuards_Door_Collision�̃|�C���^
	CGuards_Door_Collision *pPrison_Door_Collision = nullptr;

	// nullcheck
	if (pPrison_Door_Collision == nullptr)
	{
		// �������m��
		pPrison_Door_Collision = new CGuards_Door_Collision;

		// !nullcheck
		if (pPrison_Door_Collision != nullptr)
		{
			// ����������
			pPrison_Door_Collision->Init(pos, rot);

			// �|�C���^����
			pPrison_Door_Collision->SetpDoor(pDoor);
		}
	}
	// �|�C���^��Ԃ�
	return pPrison_Door_Collision;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CGuards_Door_Collision::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ����������
	CDoor_Collision::Init(pos, rot);

	// �^�C�v�ݒ�
	SetType(TYPE_JAILER_ROOM);

	// �T�C�Y�ݒ�
	SetSize(COLLISION_SIZE);
	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CGuards_Door_Collision::Uninit(void)
{
	// �I������
	CDoor_Collision::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CGuards_Door_Collision::Update(void)
{
	// �X�V����
	CDoor_Collision::Update();

	// CDoor�̃|�C���^�擾
	CDoor *pDoor = GetpDoor();

	// ���b�N��Ԑݒ�
	SetLock(pDoor->GetLock());
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CGuards_Door_Collision::Draw(void)
{
}
//=============================================================================
// �J�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CGuards_Door_Collision::Open(int nPlayer)
{
	// �J������
	CDoor_Collision::Open(nPlayer);

	// �e�N�X�`���擾
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

	// �v���C���[1�̏ꍇ
	if (nPlayer == PLAYER_1)
	{
		// �e�L�X�g���O����
		CTextLog::Create(CTexture::TEXTURE_LOG_P1_OPEN_DOOR);
	}
	// �v���C���[2�̏ꍇ
	if (nPlayer == PLAYER_2)
	{
		// �e�L�X�g���O����
		CTextLog::Create(CTexture::TEXTURE_LOG_P2_OPEN_DOOR);
	}
}
//=============================================================================
// �J���Ȃ������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CGuards_Door_Collision::NotOpen(int nPlayer)
{
	// �e�N�X�`���擾
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

	// �v���C���[1�̏ꍇ
	if (nPlayer == PLAYER_1)
	{
		// �e�L�X�g���O����
		CTextLog::Create(CTexture::TEXTURE_LOG_P1_NOT_OPEN_DOOR);
	}
	// �v���C���[2�̏ꍇ
	if (nPlayer == PLAYER_2)
	{
		// �e�L�X�g���O����
		CTextLog::Create(CTexture::TEXTURE_LOG_P2_NOT_OPEN_DOOR);
	}
}
