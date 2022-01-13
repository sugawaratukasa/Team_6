#ifndef _CONTROL_ROOM_DOOR_
#define _CONTROL_ROOM_DOOR_
//=============================================================================
// ���䎺�̔� [control_room_door.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "object_door.h"

//=============================================================================
// ���䎺�̔��N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CControl_Room_Door : public CDoor
{
public:
	CControl_Room_Door(PRIORITY Priority = PRIORITY_MODEL);				// �R���X�g���N�^
	~CControl_Room_Door();													// �f�X�g���N�^
	static CControl_Room_Door *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
private:
};
#endif