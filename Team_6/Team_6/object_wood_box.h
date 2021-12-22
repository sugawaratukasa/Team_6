#ifndef _OBJECT_WOOD_BOX_H_
#define _OBJECT_WOOD_BOX_H_
//=============================================================================
// �ؔ� [object_wood_box.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// �ؔ��N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CWood_Box : public CObject
{
public:
	CWood_Box(PRIORITY Priority = PRIORITY_MAP);					// �R���X�g���N�^
	~CWood_Box();													// �f�X�g���N�^
	static CWood_Box*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
private:
};
#endif#pragma once
