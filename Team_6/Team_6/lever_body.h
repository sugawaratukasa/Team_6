#ifndef _LEVER_BODY_H_
#define _LEVER_BODY_H_
//=============================================================================
// ���o�[�{�f�B [lever_body.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "model.h"

//=============================================================================
// ���o�[�{�f�B�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CLever_Body : public CModel
{
public:
	CLever_Body(PRIORITY Priority = PRIORITY_MODEL);				// �R���X�g���N�^
	~CLever_Body();													// �f�X�g���N�^

	static CLever_Body *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
private:
};
#endif