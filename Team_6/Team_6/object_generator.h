#ifndef _OBJECT_GENERATOR_H_
#define _OBJECT_GENERATOR_H_
//=============================================================================
// ���d�@ [object_generator.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// ���d�@�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CGenerator : public CObject
{
public:
	CGenerator(PRIORITY Priority = PRIORITY_MAP);					// �R���X�g���N�^
	~CGenerator();													// �f�X�g���N�^
	static CGenerator*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
private:
};
#endif#pragma once
