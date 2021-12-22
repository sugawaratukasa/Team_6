#ifndef _JAILER_DOOR_
#define _JAILER_DOOR_
//=============================================================================
// �Ŏ�̔� [jailer_door.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "object_door.h"

//=============================================================================
// �Ŏ�̔��N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CJailer_Door : public CDoor
{
public:
	CJailer_Door(PRIORITY Priority = PRIORITY_MAP);				// �R���X�g���N�^
	~CJailer_Door();													// �f�X�g���N�^
	static CJailer_Door *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
private:
};
#endif