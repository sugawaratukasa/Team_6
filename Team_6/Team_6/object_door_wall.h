#ifndef _OBJECT_DOOR_WALL_H_
#define _OBJECT_DOOR_WALL_H_
//=============================================================================
// �h�A�̕� [object_door_wall.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// �h�A�p�̕ǃN���X
// Author : Sugawara Tsukasa
//=============================================================================
class CDoor_Wall : public CObject
{
public:
	CDoor_Wall(PRIORITY Priority = PRIORITY_MODEL);				// �R���X�g���N�^
	~CDoor_Wall();												// �f�X�g���N�^
	static CDoor_Wall*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void Draw(void);										// �`�揈��
private:
};
#endif