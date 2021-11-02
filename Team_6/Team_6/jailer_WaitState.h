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
#include "fan3d.h"

//=============================================================================
//前方宣言
//=============================================================================

//=============================================================================
//待機状態クラス
//=============================================================================
class CWaitState : public CJailerState
{
public:
	//インスタンス生成
	static CWaitState *GetInstance();

	virtual void Init(CJailer *pJailer, CJailerView *pJailerView);
	virtual void Update(CJailer *pJailer, CJailerView *pJailerView);

private:
	CWaitState(){}
	~CWaitState(){}
};
#endif // !JAILER_WAITSTATE_H_
