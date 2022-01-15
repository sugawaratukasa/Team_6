#ifndef _CAMERA_ROOM_DOOR_H_
#define _CAMERA_ROOM_DOOR_H_
//=============================================================================
// �J�������̃h�A [camera_room_door.h]
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
class CCamera_Room_Door : public CDoor
{
public:
	CCamera_Room_Door(PRIORITY Priority = PRIORITY_MAP);							// �R���X�g���N�^
	~CCamera_Room_Door();															// �f�X�g���N�^
	static CCamera_Room_Door *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, SIDE side);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);									// ����������
	void Uninit(void);																// �I������
	void Update(void);																// �X�V����
	void Draw(void);																// �`�揈��
private:
};
#endif#pragma once
