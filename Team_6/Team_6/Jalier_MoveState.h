#ifndef JALIER_MOVESTATE_H_
#define JALIER_MOVESTATE_H_
//=============================================================================
//
// �Ŏ珄���ԃN���X [jalier_MoveState.h]
// Author : OgumaAkira
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

	virtual void Init(CJailer *Jailer, CFan3D *fan3d);
	virtual void Update(CJailer *Jailer, CFan3D *fan3d);

private:
	CMoveState() {}
	~CMoveState(){}
};
#endif // !JALIER_MOVESTATE_H_
