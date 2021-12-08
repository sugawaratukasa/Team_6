#ifndef JALIER_MOVESTATE_H_
#define JALIER_MOVESTATE_H_
//=============================================================================
//
// 看守巡回状態クラス [jalier_MoveState.h]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "jailer_State.h"

//=============================================================================
//巡回状態クラス
//=============================================================================
class CMoveState : public CJailerState
{
public:
	//インスタンス生成
	static CMoveState *GetInstance();

	virtual void Init(CJailer *pJailer, CJailerView *pJailerView);
	virtual void Update(CJailer *pJailer, CJailerView *pJailerView);

private:
	CMoveState() {}
	~CMoveState(){}
};
#endif // !JALIER_MOVESTATE_H_
