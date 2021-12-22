#ifndef _PRISON_DOOR_LEFT_H_
#define _PRISON_DOOR_LEFT_H_
//=============================================================================
// �S���̔� [object_prison_door_right.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "object_door.h"

//=============================================================================
// �S���̔��N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CPrison_Door_Left : public CDoor
{
public:
	CPrison_Door_Left(PRIORITY Priority = PRIORITY_MODEL);				// �R���X�g���N�^
	~CPrison_Door_Left();													// �f�X�g���N�^
	static CPrison_Door_Left *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
	void Open(void);												// �J������
	void Close(void);												// ���鏈��
private:
};
#endif