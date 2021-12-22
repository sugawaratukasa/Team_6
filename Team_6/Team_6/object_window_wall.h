#ifndef _OBJECT_WINDOW_WALL_H_
#define _OBJECT_WINDOW_WALL_H_
//=============================================================================
// ���t���� [object_window_wall.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// ���t����
// Author : Sugawara Tsukasa
//=============================================================================
class CWindow_Wall : public CObject
{
public:
	CWindow_Wall(PRIORITY Priority = PRIORITY_MAP);					// �R���X�g���N�^
	~CWindow_Wall();													// �f�X�g���N�^
	static CWindow_Wall*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
private:
};
#endif#pragma once
