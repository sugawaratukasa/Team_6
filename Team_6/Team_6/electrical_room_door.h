#ifndef _ELETRICAL_ROOM_DOOR_H_
#define _ELETRICAL_ROOM_DOOR_H_
//=============================================================================
// �d�C���̃h�A [electrical_room_door.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "object_door.h"

//=============================================================================
// �h�A�p�̕ǃN���X
// Author : Sugawara Tsukasa
//=============================================================================
class CEletrical_Room_Door : public CDoor
{
public:
	CEletrical_Room_Door(PRIORITY Priority = PRIORITY_MAP);				// �R���X�g���N�^
	~CEletrical_Room_Door();													// �f�X�g���N�^
	static CEletrical_Room_Door *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
private:
};
#endif