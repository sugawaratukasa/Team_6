#ifndef JALIER_CHASESTATE_H_
#define JALIER_CHASESTATE_H_
//=============================================================================
//
// �Ŏ�K�w�p����ԃN���X [jailer_ChaseState.cpp]
// Author : OgumaAkira
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

	virtual void Init(CJailer *Jailer, CFan3D *fan3d);
	virtual void Update(CJailer *Jailer, CFan3D *fan3d);

private:
	CChaseState() {};
	~CChaseState() {};
};
#endif // !JALIER_MOVESTATE_H_