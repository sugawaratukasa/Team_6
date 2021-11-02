#ifndef _ITEM_OBJECT_PC_PRISON_KEY_H_
#define _ITEM_OBJECT_PC_PRISON_KEY_H_
//=============================================================================
// PC���̌��I�u�W�F�N�g [item_object_pc_prison_key.h]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Nikaido Taichi
//=============================================================================
#include "item_object.h"

//=============================================================================
// PC���̌��I�u�W�F�N�g�N���X
// Author : Nikaido Taichi
//=============================================================================
class CPrisonKeyObject : public CItemObject
{
public:
	CPrisonKeyObject(PRIORITY Priority = PRIORITY_MODEL);	// �R���X�g���N�^
	virtual ~CPrisonKeyObject();							// �f�X�g���N�^
	static CPrisonKeyObject * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void Draw(void);										// �`�揈��
private:
};
#endif