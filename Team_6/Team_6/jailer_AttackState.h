//=============================================================================
//
// 看守階層用基底状態クラス [jailer_Hierachystate.cpp]
// Author : OgumaAkira
//
//=============================================================================
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

//=============================================================================
//攻撃状態クラス
//=============================================================================
class CAttackState : public CJailerState
{
public:
	//インスタンス生成
	static CAttackState *GetInstance();

	virtual void Init(CJailer *pJailer, CJailerView *pJailerView);
	virtual void Update(CJailer *pJailer, CJailerView *pJailerView);

private:
	CAttackState() {};
	~CAttackState() {};
};
#endif // !JAILER_WAITSTATE_H_