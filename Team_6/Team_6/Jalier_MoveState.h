#ifndef JALIER_MOVESTATE_H_
#define JALIER_MOVESTATE_H_
//=============================================================================
//
// �Ŏ珄���ԃN���X [jalier_MoveState.h]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "jailer_State.h"

//=============================================================================
//�����ԃN���X
//=============================================================================
class CMoveState : public CJailerState
{
public:
	//�C���X�^���X����
	static CMoveState *GetInstance();

	virtual void Init(CJailer *pJailer, CJailerView *pJailerView);
	virtual void Update(CJailer *pJailer, CJailerView *pJailerView);

private:
	CMoveState() {}
	~CMoveState(){}
};
#endif // !JALIER_MOVESTATE_H_
