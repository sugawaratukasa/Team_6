#ifndef _ITEM_OBJECT_CONTROL_ROOM_H_
#define _ITEM_OBJECT_CONTROL_ROOM_H_
//=============================================================================
// ���䎺�̌� [item_object_control_room.h]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Nikaido Taichi
//=============================================================================
#include "item_object.h"

//=============================================================================
// �O���錾
// Author : Nikaido Taichi
//=============================================================================
class CParticle_Emitter;

//=============================================================================
// �}�b�v�I�u�W�F�N�g�N���X
// Author : Nikaido Taichi
//=============================================================================
class CControlRoomKeyObject : public CItemObject
{
public:
	CControlRoomKeyObject(PRIORITY Priority = PRIORITY_MODEL);	// �R���X�g���N�^
	virtual ~CControlRoomKeyObject();							// �f�X�g���N�^
	static CControlRoomKeyObject * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��
private:
	CParticle_Emitter * m_pParticleEmitter;
};
#endif