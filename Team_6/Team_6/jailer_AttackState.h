#ifndef JAILER_ATTACKSTATE_H_
#define JAILER_ATTACKSTATE_H_
//=============================================================================
//インクルードファイル
//=============================================================================
#include "jailer_State.h"

//=============================================================================
//前方宣言
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