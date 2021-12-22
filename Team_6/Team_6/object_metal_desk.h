#ifndef _OBJECT_METAL_DESK_H_
#define _OBJECT_METAL_DESK_H_
//=============================================================================
// �����̊� [object_metal_desk.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// �����̊��N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CMetal_Desk : public CObject
{
public:
	CMetal_Desk(PRIORITY Priority = PRIORITY_MAP);					// �R���X�g���N�^
	~CMetal_Desk();													// �f�X�g���N�^
	static CMetal_Desk*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
private:
};
#endif#pragma once
