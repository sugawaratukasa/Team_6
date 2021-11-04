#ifndef _OBJECT_WALL_H_
#define _OBJECT_WALL_H_
//=============================================================================
// �ǃN���X [object_wall.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// �ǃN���X
// Author : Sugawara Tsukasa
//=============================================================================
class CWall : public CObject
{
public:
	CWall(PRIORITY Priority = PRIORITY_MODEL);				// �R���X�g���N�^
	~CWall();												// �f�X�g���N�^
	static CWall*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void Draw(void);										// �`�揈��
private:
};
#endif