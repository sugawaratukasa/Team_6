#ifndef _PC_DESK_H_
#define _PC_DESK_H_
//=============================================================================
// PC�̊� [pc_desk.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// PC�̊��N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CPC_Desk : public CObject
{
public:
	CPC_Desk(PRIORITY Priority = PRIORITY_MAP);					// �R���X�g���N�^
	~CPC_Desk();													// �f�X�g���N�^
	static CPC_Desk*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
private:
};
#endif
