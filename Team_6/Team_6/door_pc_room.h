#ifndef _DOOR_PC_ROOM_H_
#define _DOOR_PC_ROOM_H_
//=============================================================================
// PC���̔� [door_pc_room.h]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Nikaido Taichi
//=============================================================================
#include "object_door.h"

//=============================================================================
// �I�u�W�F�N�g�N���X
// Author : Nikaido Taichi
//=============================================================================
class CPCRoomDoor : public CDoor
{
public:
	CPCRoomDoor(PRIORITY Priority = PRIORITY_MODEL);				// �R���X�g���N�^
	~CPCRoomDoor();													// �f�X�g���N�^
	static CPCRoomDoor *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
private:
};
#endif