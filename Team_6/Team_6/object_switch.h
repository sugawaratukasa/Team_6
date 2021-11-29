#ifndef _OBJECT_SWITCH_H_
#define _OBJECT_SWITCH_H_
//=============================================================================
// �X�C�b�`�N���X [object_wall.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"
#include "prison_cell_door.h"
//=============================================================================
// �X�C�b�`�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CSwitch : public CObject
{
public:
	CSwitch(PRIORITY Priority = PRIORITY_MAP);				// �R���X�g���N�^
	~CSwitch();												// �f�X�g���N�^

	static CSwitch*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CPrison_Cell_Door *pPrison_Cell_Door);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);													// ����������
	void Uninit(void);																				// �I������
	void Update(void);																				// �X�V����
	void Draw(void);																				// �`�揈��
	void Push(void);																				// �{�^�������������֐�
private:
	CPrison_Cell_Door *m_pPrison_Cell_Door;	// �Ɩ[�̃h�A
};
#endif