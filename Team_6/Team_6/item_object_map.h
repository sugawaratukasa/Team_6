#ifndef _ITEM_OBJECT_MAP_H_
#define _ITEM_OBJECT_MAP_H_
//=============================================================================
// �}�b�v�I�u�W�F�N�g [item_object_map.h]
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
class CMapObject : public CItemObject
{
public:
	CMapObject(PRIORITY Priority = PRIORITY_MODEL);	// �R���X�g���N�^
	virtual ~CMapObject();							// �f�X�g���N�^
	static CMapObject * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void Draw(void);										// �`�揈��
private:
};
#endif