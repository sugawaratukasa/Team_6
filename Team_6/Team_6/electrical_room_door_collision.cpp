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
#include "electrical_room_door_collision.h"
#include "map_spot.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(120.0f,450.0f,120.0f))	// �T�C�Y
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CElectrical_Room_Door_Collision::CElectrical_Room_Door_Collision(PRIORITY Priority) : CDoor_Collision(Priority)
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CElectrical_Room_Door_Collision::~CElectrical_Room_Door_Collision()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CElectrical_Room_Door_Collision * CElectrical_Room_Door_Collision::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CDoor *pDoor)
{
	// CElectrical_Room_Door_Collision�̃|�C���^
	CElectrical_Room_Door_Collision *pElectrical_Room_Door_Collision = nullptr;

	// nullcheck
	if (pElectrical_Room_Door_Collision == nullptr)
	{
		// �������m��
		pElectrical_Room_Door_Collision = new CElectrical_Room_Door_Collision;

		// !nullcheck
		if (pElectrical_Room_Door_Collision != nullptr)
		{
			// ����������
			pElectrical_Room_Door_Collision->Init(pos, rot);

			// �|�C���^����
			pElectrical_Room_Door_Collision->SetpDoor(pDoor);
		}
	}
	// �|�C���^��Ԃ�
	return pElectrical_Room_Door_Collision;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CElectrical_Room_Door_Collision::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ����������
	CDoor_Collision::Init(pos, rot);

	// �^�C�v�ݒ�
	SetType(TYPE_ELECTRICAL_ROOM);

	// �T�C�Y�ݒ�
	SetSize(COLLISION_SIZE);
	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CElectrical_Room_Door_Collision::Uninit(void)
{
	// �I������
	CDoor_Collision::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CElectrical_Room_Door_Collision::Update(void)
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
void CElectrical_Room_Door_Collision::Draw(void)
{
}
//=============================================================================
// �J�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CElectrical_Room_Door_Collision::Open(int nPlayer)
{
	// �J������
	CDoor_Collision::Open(nPlayer);

	// �e�N�X�`���擾
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

	// �h�A�擾
	CDoor *pDoor = GetpDoor();

	// �h�A�̃T�C�h�擾
	CDoor::SIDE side = pDoor->GetSide();

	// ���̏ꍇ
	if (side == CDoor::SIDE_LEFT)
	{
		// �����J��������ݒ�
		CMapSpot::SetIsOpenRoom(CMapSpot::MAP_AREA_LEFT, CMapSpot::ROOM_TYPE_POWER_ROOM);
	}
	// �E�̏ꍇ
	if (side == CDoor::SIDE_RIGHT)
	{
		// �����J��������ݒ�
		CMapSpot::SetIsOpenRoom(CMapSpot::MAP_AREA_RIGHT, CMapSpot::ROOM_TYPE_POWER_ROOM);
	}

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
void CElectrical_Room_Door_Collision::NotOpen(int nPlayer)
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