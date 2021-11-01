//=============================================================================
//
// �Ŏ�K�w�p����ԃN���X [jailer_Hierachystate.cpp]
// Author : OgumaAkira
//
//=============================================================================
#ifndef JAILER_ATTACKSTATE_H_
#define JAILER_ATTACKSTATE_H_
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "jailer_State.h"

//=============================================================================
//�O���錾
//=============================================================================
class CJailer;

//=============================================================================
//�U����ԃN���X
//=============================================================================
class CAttackState : public CJailerState
{
public:
	//�C���X�^���X����
	static CAttackState *GetInstance();

	virtual void Init(CJailer *pJailer, CJailerView *pJailerView);
	virtual void Update(CJailer *pJailer, CJailerView *pJailerView);

private:
	CAttackState() {};
	~CAttackState() {};
};
#endif // !JAILER_WAITSTATE_H_