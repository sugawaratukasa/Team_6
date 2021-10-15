#ifndef _OBJECT_H_
#define _OBJECT_H_
//=============================================================================
// �I�u�W�F�N�g [object.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "model.h"

//=============================================================================
// �I�u�W�F�N�g�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CObject : public CModel
{
public:
	CObject(PRIORITY Priority = PRIORITY_MODEL);			// �R���X�g���N�^
	~CObject();												// �f�X�g���N�^
	static CObject *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void Draw(void);										// �`�揈��
private:
};
#endif