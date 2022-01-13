#ifndef _OBJECT_TABLE_H_
#define _OBJECT_TABLE_H_
//=============================================================================
// �e�[�u�� [object_table.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// �e�[�u���N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CTable : public CObject
{
public:
	CTable(PRIORITY Priority = PRIORITY_MAP);					// �R���X�g���N�^
	~CTable();													// �f�X�g���N�^
	static CTable*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
private:
};
#endif#pragma once
