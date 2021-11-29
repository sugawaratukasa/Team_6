#ifndef _OBJECT_PRISON_DOOR_RIGHT_H_
#define _OBJECT_PRISON_DOOR_RIGHT_H_
//=============================================================================
// �S���h�A�N���X [object_prison_door_right.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// �S���ǃN���X
// Author : Sugawara Tsukasa
//=============================================================================
class CPrison_Door_Right : public CObject
{
public:
	CPrison_Door_Right(PRIORITY Priority = PRIORITY_MAP);				// �R���X�g���N�^
	~CPrison_Door_Right();												// �f�X�g���N�^
	static CPrison_Door_Right*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);						// ����������
	void Uninit(void);													// �I������
	void Update(void);													// �X�V����
	void Draw(void);													// �`�揈��
private:
};
#endif