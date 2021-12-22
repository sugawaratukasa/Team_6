#ifndef _GOAL_DOOR_H_
#define _GOAL_DOOR_H_
//=============================================================================
// �S�[���̔� [goal_door.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "object_door.h"
#include "lever.h"
//=============================================================================
// �O���錾
// Author : Sugawara Tsukasa
//=============================================================================
class CLever;
//=============================================================================
// �S�[���̔��N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CGoal_Door : public CDoor
{
public:
	CGoal_Door(PRIORITY Priority = PRIORITY_MODEL);													// �R���X�g���N�^
	~CGoal_Door();																					// �f�X�g���N�^
	static CGoal_Door *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CLever *pLever1, CLever *pLever2);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);													// ����������
	void Uninit(void);																				// �I������
	void Update(void);																				// �X�V����
	void Draw(void);																				// �`�揈��
	void Open(void);																				// �J������
	void Close(void);																				// ���鏈��
private:
	CLever *m_pLever1;	// CLever�̃|�C���^
	CLever *m_pLever2;	// CLever�̃|�C���^
	D3DXVECTOR3 m_InitPos;	// �����ʒu
};
#endif