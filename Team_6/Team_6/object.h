#ifndef _OBJECT_H_
#define _OBJECT_H_
//=============================================================================
// �I�u�W�F�N�g [object.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "model.h"

//=============================================================================
// �I�u�W�F�N�g�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CObject : public CModel
{
public:
	// ���
	enum TYPE
	{
		TYPE_NONE = -1,
		TYPE_WALL,
		TYPE_SWITCH,
		TYPE_MAX
	};
	CObject(PRIORITY Priority = PRIORITY_MODEL);				// �R���X�g���N�^
	virtual ~CObject();											// �f�X�g���N�^

	static CObject *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		// ����������
	virtual void Uninit(void);									// �I������
	virtual void Update(void);									// �X�V����
	virtual void Draw(void);									// �`�揈��
	void SetType(TYPE type) { m_Type = type; }					// ��ނ̐ݒ�
	TYPE GetType(void) { return m_Type; }						// ��ގ擾
private:
	TYPE m_Type;	// ���
};
#endif