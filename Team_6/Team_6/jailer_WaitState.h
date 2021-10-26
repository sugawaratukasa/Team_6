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

//=============================================================================
//�O���錾
//=============================================================================

class CWaitState : public CJailerState
{
public:
	static CWaitState *GetInstance()
	{
		static CWaitState instance;
		return &instance;
	}

	virtual void Init(CJailer *jailer);
	virtual void Update(CJailer *jailer);

private:
	CWaitState() {}
};
#endif // !JAILER_WAITSTATE_H_
