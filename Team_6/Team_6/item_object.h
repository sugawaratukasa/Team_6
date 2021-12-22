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
class CItemObject : public CScene
{
public:
	enum ITEM_OBJECT_LIST
	{
		ITEM_OBJECT_NONE = -1,
		ITEM_OBJECT_KEY_STORAGE,
		ITEM_OBJECT_KEY_JAILER_ROOM,
		ITEM_OBJECT_KEY_CONTOROL_ROOM,
		ITEM_OBJECT_KEY_ELECTRICAL_ROOM,
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
	void SetPos(D3DXVECTOR3 Pos) { m_Position = Pos; }
	void SetSize(D3DXVECTOR3 Size) { m_Size = Size; }
	void SetType(ITEM_OBJECT_LIST Type) { m_Type = Type; }
	//=============================================================================
	//�@Get�֐�
	//=============================================================================
	D3DXVECTOR3 GetPos(void) { return m_Position; }
	D3DXVECTOR3 GetSize(void) { return m_Size; }
	ITEM_OBJECT_LIST GetType(void) { return m_Type; }
private:
	void Collision(void);		// �Փˏ���
	D3DXVECTOR3 m_Position;		// �ʒu
	D3DXVECTOR3 m_Size;			// �T�C�Y
	D3DXVECTOR3 m_Rotation;		// ����
	ITEM_OBJECT_LIST m_Type;	// ���
};
#endif