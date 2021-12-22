#ifndef _OBJECT_DUCT_WALL_H_
#define _OBJECT_DUCT_WALL_H_
//=============================================================================
// �_�N�g [object_duct_wall.h]
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
class CDuct_Wall : public CObject
{
public:
	CDuct_Wall(PRIORITY Priority = PRIORITY_MAP);				// �R���X�g���N�^
	~CDuct_Wall();												// �f�X�g���N�^
	static CDuct_Wall*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��
private:
};
#endif