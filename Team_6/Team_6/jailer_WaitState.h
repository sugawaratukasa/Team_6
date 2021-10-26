#//=============================================================================
//
// 看守待機状態クラス [jailer_WaitState.cpp]
// Author : OgumaAkira
//
//=============================================================================
#ifndef JAILER_WAITSTATE_H_
#define JAILER_WAITSTATE_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "jailer_State.h"

//=============================================================================
//前方宣言
//=============================================================================

class CWaitState : public CJailerState
{
public:
	static CWaitState *GetInstance()
	{
		static CWaitState instance;
		return &instance;
	}

	virtual void Init(CJailer *jailer);
	virtual void Update(CJailer *jailer);

private:
	CWaitState() {}
};
#endif // !JAILER_WAITSTATE_H_
