#ifndef _OBJECT_PRISON_WALL_H_
#define _OBJECT_PRISON_WALL_H_
//=============================================================================
// �S���ǃN���X [object_prison_wall.h]
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
class CPrison_Wall : public CObject
{
public:
	CPrison_Wall(PRIORITY Priority = PRIORITY_MAP);					// �R���X�g���N�^
	~CPrison_Wall();												// �f�X�g���N�^
	static CPrison_Wall*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
private:
};
#endif