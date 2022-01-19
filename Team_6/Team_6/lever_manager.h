#ifndef _LEVER_MANAGER_H_
#define _LEVER_MANAGER_H_
//=============================================================================
// ���o�[�}�l�[�W���[ [lever_manager.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
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
class CLever_Manager : public CScene
{
public:
	CLever_Manager(PRIORITY Priority = PRIORITY_MODEL);				// �R���X�g���N�^
	~CLever_Manager();												// �f�X�g���N�^
	static CLever_Manager *Create(CLever *pLever1, CLever *pLever2);// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
private:
	CLever *m_pLever1;		// CLever�̃|�C���^
	CLever *m_pLever2;		// CLever�̃|�C���^
	int m_nLeverCnt;		// �J�E���g
	bool m_bOpen;			// �J��������
};
#endif