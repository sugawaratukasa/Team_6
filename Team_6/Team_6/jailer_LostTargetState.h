#ifndef _JAILER_LOST_TARGET_H_
#define _JAILER_LOST_TARGET_H_

//=============================================================================
//
// �Ŏ�̃^�[�Q�b�g������������ԏ��� [jailer_LostTargetState.h]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "jailer_State.h"

//=============================================================================
//�Ŏ�̃^�[�Q�b�g������������Ԃ̃N���X
//=============================================================================
class CJailer_LostTarget :public CJailerState
{
public:
	//=========================================================================
	//�����o�֐��錾
	//=========================================================================
	~CJailer_LostTarget();	//�f�X�g���N�^

	//�C���X�^���X����
	static CJailer_LostTarget *GetInstance(void);
	static void Release(void);

	virtual void Init(CJailer *pJailer, CJailerView *pJailerView);
	virtual void Update(CJailer *pJailer, CJailerView *pJailerView);

private:
	CJailer_LostTarget();	//�B���R���X�g���N�^

	//=========================================================================
	//�����o�ϐ��錾
	//=========================================================================
	static CJailer_LostTarget *m_pShingleton;	//���g��singleton�p�|�C���^
};
#endif // !_JAILER_LOST_TARGET_H_
