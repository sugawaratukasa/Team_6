#ifndef JALIER_CHASESTATE_H_
#define JALIER_CHASESTATE_H_
//=============================================================================
//
// �Ŏ�K�w�p����ԃN���X [jailer_ChaseState.cpp]
// Author : Yamada Ryota
//
//=============================================================================
#include "jailer_State.h"

//=============================================================================
//�ǐՏ�ԃN���X
//=============================================================================
class CChaseState : public CJailerState
{
public:
	//�C���X�^���X����
	static CChaseState *GetInstance();

	virtual void Init(CJailer *pJailer, CJailerView *pJailerView);
	virtual void Update(CJailer *pJailer, CJailerView *pJailerView);

private:
	CChaseState() {};
	~CChaseState() {};
};
#endif // !JALIER_MOVESTATE_H_