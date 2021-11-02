#ifndef _ITEM_OBJECT_H_
#define _ITEM_OBJECT_H_
//=============================================================================
// �A�C�e���I�u�W�F�N�g [item_object.h]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Nikaido Taichi
//=============================================================================
#include "model.h"

//=============================================================================
// �I�u�W�F�N�g�N���X
// Author : Nikaido Taichi
//=============================================================================
class CItemObject : public CModel
{
public:
	enum ITEM_OBJECT_LIST
	{
		ITEM_OBJECT_NONE = -1,
		ITEM_OBJECT_KEY_PRISON,
		ITEM_OBJECT_KEY_STORAGE,
		ITEM_OBJECT_KEY_JAILER_ROOM,
		ITEM_OBJECT_KEY_PC_ROOM,
		ITEM_OBJECT_BATON,
		ITEM_OBJECT_MAP,
		ITEM_OBJECT_MAX
	};
	CItemObject(PRIORITY Priority = PRIORITY_MODEL);	// �R���X�g���N�^
	virtual ~CItemObject();								// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��
	//=============================================================================
	//�@Set�֐�
	//=============================================================================
	void SetType(ITEM_OBJECT_LIST Type) { m_Type = Type; }
	//=============================================================================
	//�@Get�֐�
	//=============================================================================
	ITEM_OBJECT_LIST GetType(void) { return m_Type; }
private:
	void Collision(void);								// �Փˏ���
	ITEM_OBJECT_LIST m_Type;							// ���
};
#endif