#ifndef _DOOR_WALL_COLLISION_H_
#define _DOOR_WALL_COLLISION_H_
//=============================================================================
// �h�A�̕ǂ̓����蔻��p�N���X [door_wall_collision.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// �h�A�̕ǂ̓����蔻��p�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CDoorWallCollision : public CObject
{
public:
	CDoorWallCollision(PRIORITY Priority = PRIORITY_MAP);					// �R���X�g���N�^
	~CDoorWallCollision();													// �f�X�g���N�^
	static CDoorWallCollision *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);							// ����������
	void Uninit(void);														// �I������
	void Update(void);														// �X�V����
	void Draw(void);														// �`�揈��
private:
};
#endif