#ifndef JAILER_WAITSTATE_H_
#define JAILER_WAITSTATE_H_
#//=============================================================================
//
// �Ŏ�ҋ@��ԃN���X [jailer_WaitState.cpp]
// Author : Yamada Ryota
//
//=============================================================================

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
class CReturnRouteState : public CJailerState
{
public:
	//�C���X�^���X����
	static CReturnRouteState *GetInstance();

	virtual void Init(CJailer *pJailer, CJailerView *pJailerView);
	virtual void Update(CJailer *pJailer, CJailerView *pJailerView);

private:
	CReturnRouteState(){}
	~CReturnRouteState(){}
};
#endif // !JAILER_WAITSTATE_H_
