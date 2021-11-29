#ifndef _OBJECT_SWITCH_COLLISION_H_
#define _OBJECT_SWITCH_COLLISION_H_
//=============================================================================
// �X�C�b�`����N���X [object_switch_collision.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"
#include "object_switch.h"
//=============================================================================
// �X�C�b�`����N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CSwitch_Collision : public CObject
{
public:
	CSwitch_Collision(PRIORITY Priority = PRIORITY_MAP);								// �R���X�g���N�^
	~CSwitch_Collision();																// �f�X�g���N�^

	static CSwitch_Collision*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,CSwitch *pSwitch);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);										// ����������
	void Uninit(void);																	// �I������
	void Update(void);																	// �X�V����
	void Draw(void);																	// �`�揈��
	void Push(void);																	// �X�C�b�`�������֐�
private:
	CSwitch *m_pSwitch;	// CSwitch�̃|�C���^
};
#endif