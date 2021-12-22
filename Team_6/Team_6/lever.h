#ifndef _LEVER_H_
#define _LEVER_H_
//=============================================================================
// ���o�[ [���o�[.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "model.h"
#include "door_collision.h"
//=============================================================================
// �O���錾
// Author : Sugawara Tsukasa
//=============================================================================
class CLever_Handle;
//=============================================================================
// �h�A�̔���N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CLever : public CDoor_Collision
{
public:
	CLever(PRIORITY Priority = PRIORITY_OBJ_COLLISION);						// �R���X�g���N�^
	~CLever();																// �f�X�g���N�^

	static CLever *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);							// ����������
	void Uninit(void);														// �I������
	void Update(void);														// �X�V����
	void Draw(void);														// �`�揈��
	void LeverCrate(D3DXVECTOR3 pos, D3DXVECTOR3 rot);						// ���o�[��������
	void Open(void);														// ���o�[�������鏈��
	bool GetbDownLever(void) { return m_bDownLever; }							// ���o�[���������Ă��邩�擾
private:
	CLever_Handle *m_pLever_Handle;	// CLever_Handle�̃|�C���^
	bool m_bDownLever;					// ���o�[���������Ă��邩
};
#endif