#ifndef _STORAGE_DOOR_
#define _STORAGE_DOOR_
//=============================================================================
// �q�ɂ̔� [storage_door.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "object_door.h"

//=============================================================================
// �q�ɂ̔��N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CStorage_Door : public CDoor
{
public:
	CStorage_Door(PRIORITY Priority = PRIORITY_MAP);				// �R���X�g���N�^
	~CStorage_Door();													// �f�X�g���N�^
	static CStorage_Door *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
private:
};
#endif
