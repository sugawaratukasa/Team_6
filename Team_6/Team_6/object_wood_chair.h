#ifndef _OBJECT_WOOD_CHAIR_H_
#define _OBJECT_WOOD_CHAIR_H_
//=============================================================================
// �؂̈֎q [object_wood_chair.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// �؂̈֎q�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CWood_Chair : public CObject
{
public:
	CWood_Chair(PRIORITY Priority = PRIORITY_MAP);					// �R���X�g���N�^
	~CWood_Chair();													// �f�X�g���N�^
	static CWood_Chair*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
private:
};
#endif