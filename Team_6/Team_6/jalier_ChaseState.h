#ifndef JALIER_CHASESTATE_H_
#define JALIER_CHASESTATE_H_
//=============================================================================
//
// 看守階層用基底状態クラス [jailer_ChaseState.cpp]
// Author : Yamada Ryota
//
//=============================================================================
#include "jailer_State.h"

//=============================================================================
//追跡状態クラス
//=============================================================================
class CChaseState : public CJailerState
{
public:
	//インスタンス生成
	static CChaseState *GetInstance();

	virtual void Init(CJailer *pJailer, CJailerView *pJailerView);
	virtual void Update(CJailer *pJailer, CJailerView *pJailerView);

private:
	CChaseState() {};
	~CChaseState() {};
};
#endif // !JALIER_MOVESTATE_H_