#ifndef _ITEM_OBJECT_ELECTRICAL_ROOM_KEY_H_
#define _ITEM_OBJECT_ELECTRICAL_ROOM_KEY_H_
//=============================================================================
// �d�C���̌� [item_object_electrical_room_key.h]
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
class CElectricalRoomKeyObject : public CItemObject
{
public:
	CElectricalRoomKeyObject(PRIORITY Priority = PRIORITY_MODEL);		// �R���X�g���N�^
	virtual ~CElectricalRoomKeyObject();								// �f�X�g���N�^
	static CElectricalRoomKeyObject * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��
private:
	CParticle_Emitter * m_pParticleEmitter;
};
#endif