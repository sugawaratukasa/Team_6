#//=============================================================================
//
// �Ŏ�ҋ@��ԃN���X [jailer_WaitState.cpp]
// Author : OgumaAkira
//
//=============================================================================
#ifndef JAILER_WAITSTATE_H_
#define JAILER_WAITSTATE_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "jailer_State.h"
#include "fan3d.h"

//=============================================================================
//�O���錾
//=============================================================================

//=============================================================================
//�ҋ@��ԃN���X
//=============================================================================
class CWaitState : public CJailerState
{
public:
	//�C���X�^���X����
	static CWaitState *GetInstance();

	virtual void Init(CJailer *pJailer, CJailerView *pJailerView);
	virtual void Update(CJailer *pJailer, CJailerView *pJailerView);

private:
	CWaitState(){}
	~CWaitState(){}
};
#endif // !JAILER_WAITSTATE_H_
