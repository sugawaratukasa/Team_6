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

	virtual void Init(CJailer *Jailer, CFan3D *fan3d);
	virtual void Update(CJailer *Jailer, CFan3D *fan3d);

private:
	CAttackState() {};
	~CAttackState() {};
};
#endif // !JAILER_WAITSTATE_H_