#ifndef JALIER_MOVESTATE_H_
#define JALIER_MOVESTATE_H_

#include "jailer_State.h"

class CMoveState : public CJailerState
{
public:
	static CMoveState *GetInstance()
	{
		static CMoveState instance;
		return &instance;
	}

	virtual void Init(CJailer *Jailer);
	virtual void Update(CJailer *Jailer);

private:
	CMoveState(){}
};
#endif // !JALIER_MOVESTATE_H_
