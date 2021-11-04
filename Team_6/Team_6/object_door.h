#ifndef _OBJECT_DOOR_H_
#define _OBJECT_DOOR_H_
//=============================================================================
// �h�A [object_dor.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// �I�u�W�F�N�g�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CDoor : public CObject
{
public:
	enum DOOR_LIST
	{
		DOOR_NONE = -1,
		DOOR_PC_ROOM,
		DOOR_MAX
	};
	CDoor(PRIORITY Priority = PRIORITY_MODEL);				// �R���X�g���N�^
	~CDoor();												// �f�X�g���N�^
	static CDoor *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void Draw(void);										// �`�揈��
	//=============================================================================
	//�@Set�֐�
	//=============================================================================
	void SetType(DOOR_LIST Type) { m_Type = Type; }
	void SetLock(bool bLock) { m_bLock = bLock; }
	//=============================================================================
	//�@Get�֐�
	//=============================================================================
	DOOR_LIST GetType(void) { return m_Type; }
	bool GetLock(void) { return m_bLock; }
private:
	DOOR_LIST m_Type;										// �h�A�̎��
	bool m_bLock;											// ���b�N���
};
#endif