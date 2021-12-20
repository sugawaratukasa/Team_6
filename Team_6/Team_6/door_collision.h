#ifndef _DOOR_COLLISON_H_
#define _DOOR_COLLISON_H_
//=============================================================================
// �h�A�̔��� [door_collision.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "model.h"
#include "object_door.h"
//=============================================================================
// �O���錾
// Author : Sugawara Tsukasa
//=============================================================================
class CDoor;
//=============================================================================
// �h�A�̔���N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CDoor_Collision : public CModel
{
public:
	// ���
	enum TYPE
	{
		TYPE_NONE = -1,
		TYPE_PRISON,
		TYPE_CONTROL_ROOM,
		TYPE_JAILER_ROOM,
		TYPE_SWITCH,
		TYPE_STORAGE,
		TYPE_MAX
	};
	CDoor_Collision(PRIORITY Priority = PRIORITY_OBJ_COLLISION);					// �R���X�g���N�^
	virtual ~CDoor_Collision();														// �f�X�g���N�^

	static CDoor_Collision *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CDoor *pDoor);	// ��������
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);							// ����������
	virtual void Uninit(void);														// �I������
	virtual void Update(void);														// �X�V����
	virtual void Draw(void);														// �`�揈��
	virtual void Open(void);														// �����J������
	//===========================
	// SetGet�֐�
	//===========================
	void SetType(TYPE type) { m_Type = type; }			// ��ނ̐ݒ�
	TYPE GetType(void) { return m_Type; }				// ��ގ擾
	void SetLock(bool Lock) { m_bLock = Lock; }			// ���b�N��Ԑݒ�
	bool GetLock(void) { return m_bLock;}				// ���b�N��Ԃ̎擾
	void SetpDoor(CDoor *pDoor) { m_pDoor = pDoor; }	// CDoor�̃|�C���^�ݒ�
	CDoor *GetpDoor(void) { return m_pDoor; }			// CDoor�̃|�C���^�擾
private:
	TYPE m_Type;	// ���
	bool m_bLock;	// ���b�N���
	CDoor *m_pDoor;	// CDoor�̃|�C���^
};
#endif