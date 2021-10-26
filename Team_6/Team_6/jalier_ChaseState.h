#ifndef JALIER_CHASESTATE_H_
#define JALIER_CHASESTATE_H_

#include "jailer_State.h"

class CChaseState : public CJailerState
{
public:
	static CChaseState *GetInstance()
	{
		static CChaseState instance;
		return &instance;
	}

	virtual void Init(CJailer *Jailer);
	virtual void Update(CJailer *Jailer);

private:
	CChaseState() {}
};
#endif // !JALIER_MOVESTATE_H_