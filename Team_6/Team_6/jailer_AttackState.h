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

class CAttackState : public CJailerState
{
public:
	static CAttackState *GetInstance()
	{
		static CAttackState instance;
		return &instance;
	}

	virtual void Init(CJailer *jailer);
	virtual void Update(CJailer *jailer);

private:
	CAttackState() {}
};
#endif // !JAILER_WAITSTATE_H_