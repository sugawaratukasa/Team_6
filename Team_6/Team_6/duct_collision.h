#ifndef _DUCT_COLLISON_H_
#define _DUCT_COLLISON_H_
//=============================================================================
// �_�N�g�̔��� [duct_collision.h]
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

//=============================================================================
// �h�A�̔���N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CDuct_Collision : public CModel
{
public:
	// ���
	enum TYPE
	{
		TYPE_NONE = -1,
		TYPE_LEFT,
		TYPE_RIGHT,
		TYPE_MAX
	};
	CDuct_Collision(PRIORITY Priority = PRIORITY_DUCT);					// �R���X�g���N�^
	virtual ~CDuct_Collision();														// �f�X�g���N�^

	static CDuct_Collision *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type);	// ��������
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);							// ����������
	virtual void Uninit(void);														// �I������
	virtual void Update(void);														// �X�V����
	virtual void Draw(void);														// �`�揈��
	int GetType(void) { return m_Type; }											// �^�C�v�擾�֐�
private:
	TYPE m_Type;	// ���
};
#endif