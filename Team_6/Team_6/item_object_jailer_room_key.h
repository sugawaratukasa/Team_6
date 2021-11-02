#ifndef _ITEM_OBJECT_JAILER_ROOM_H_
#define _ITEM_OBJECT_JAILER_ROOM_H_
//=============================================================================
// �}�b�v�I�u�W�F�N�g [item_object_jailer_room.h]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Nikaido Taichi
//=============================================================================
#include "item_object.h"

//=============================================================================
// �}�b�v�I�u�W�F�N�g�N���X
// Author : Nikaido Taichi
//=============================================================================
class CJailerKeyObject : public CItemObject
{
public:
	CJailerKeyObject(PRIORITY Priority = PRIORITY_MODEL);	// �R���X�g���N�^
	virtual ~CJailerKeyObject();							// �f�X�g���N�^
	static CJailerKeyObject * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void Draw(void);										// �`�揈��
private:
};
#endif