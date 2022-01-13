#ifndef _LEVER_HANDLE_H_
#define _LEVER_HANDLE_H_
//=============================================================================
// ���o�[�n���h�� [lever_handle.h]
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
class CLever_Handle : public CModel
{
public:
	CLever_Handle(PRIORITY Priority = PRIORITY_MODEL);				// �R���X�g���N�^
	~CLever_Handle();												// �f�X�g���N�^

	static CLever_Handle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
	void Down(void);												// �����鏈��
	void Up(void);													// �グ�鏈��
	//======================================
	// Set�֐�
	//======================================
	void SetDown(bool bDown) { m_bDown = bDown; }	// �������Ă��邩�ݒ肷��
	//======================================
	// Get�֐�
	//======================================
	bool GetbDown(void) { return m_bDown; }			// �������Ă��邩�擾
private:
	D3DXVECTOR3 m_InitPos;	// �����ʒu
	bool m_bDown;			// ������Ă��邩���肷��
	int m_nDownCnt;			// ���o�[�̉������Ă���J�E���g		
};
#endif