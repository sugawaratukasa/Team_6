#ifndef _GUARDS_DOOR_
#define _GUARDS_DOOR_
//=============================================================================
// �Ŏ�̔� [guards_door.h]
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
class CGuards_Door : public CDoor
{
public:
	CGuards_Door(PRIORITY Priority = PRIORITY_MODEL);				// �R���X�g���N�^
	~CGuards_Door();													// �f�X�g���N�^
	static CGuards_Door *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
private:
};
#endif