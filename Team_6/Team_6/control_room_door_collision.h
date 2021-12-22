#ifndef _CONTROL_ROOM_DOOR_COLLISON_H_
#define _CONTROL_ROOM_DOOR_COLLISON_H_
//=============================================================================
// ���䎺�̔��� [control_room_door_collision.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "model.h"
#include "door_collision.h"
//=============================================================================
// �O���錾
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// ���䎺�̔���N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CControl_Room_Door_Collision : public CDoor_Collision
{
public:
	CControl_Room_Door_Collision(PRIORITY Priority = PRIORITY_OBJ_COLLISION);						// �R���X�g���N�^
	~CControl_Room_Door_Collision();																// �f�X�g���N�^

	static CControl_Room_Door_Collision *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CDoor *pDoor);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);											// ����������
	void Uninit(void);																		// �I������
	void Update(void);																		// �X�V����
	void Draw(void);																		// �`�揈��
private:
};
#endif