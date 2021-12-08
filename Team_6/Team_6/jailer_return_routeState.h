#ifndef JAILER_WAITSTATE_H_
#define JAILER_WAITSTATE_H_
#//=============================================================================
//
// 看守待機状態クラス [jailer_WaitState.cpp]
// Author : Yamada Ryota
//
//=============================================================================

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
class CReturnRouteState : public CJailerState
{
public:
	//インスタンス生成
	static CReturnRouteState *GetInstance();

	virtual void Init(CJailer *pJailer, CJailerView *pJailerView);
	virtual void Update(CJailer *pJailer, CJailerView *pJailerView);

private:
	CReturnRouteState(){}
	~CReturnRouteState(){}
};
#endif // !JAILER_WAITSTATE_H_
