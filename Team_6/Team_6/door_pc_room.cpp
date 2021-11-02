#include "door_pc_room.h"

CPCRoomDoor::CPCRoomDoor(PRIORITY Priority)
{
}

CPCRoomDoor::~CPCRoomDoor()
{
}

CPCRoomDoor * CPCRoomDoor::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CPCRoomKey�̃|�C���^
	CPCRoomDoor *pPCRoomDoor = nullptr;

	// nullcheck
	if (pPCRoomDoor == nullptr)
	{
		// �������m��
		pPCRoomDoor = new CPCRoomDoor;

		// !nullcheck
		if (pPCRoomDoor != nullptr)
		{
			// ����������
			pPCRoomDoor->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pPCRoomDoor;
}

HRESULT CPCRoomDoor::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �h�A�̏����������֐��Ăяo��
	CDoor::Init(pos, rot);
	// �^�C�v��ݒ肷��
	SetType(CDoor::DOOR_PC_ROOM);
	return S_OK;
}

void CPCRoomDoor::Uninit(void)
{
	// �h�A�̏I�������֐��Ăяo��
	CDoor::Uninit();
}

void CPCRoomDoor::Update(void)
{
	// �h�A�̍X�V�����֐��Ăяo��
	CDoor::Update();
}

void CPCRoomDoor::Draw(void)
{
	// �h�A�̕`�揈���֐��Ăяo��
	CDoor::Draw();
}
