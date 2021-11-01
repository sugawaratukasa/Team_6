//=============================================================================
//
// 看守階層用基底状態クラス [jailer_Hierachystate.cpp]
// Author : OgumaAkira
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "jailer_WaitState.h"
#include "jailer_AttackState.h"
#include "jailer.h"

//=============================================================================
//インスタンス生成関数
//=============================================================================
CAttackState * CAttackState::GetInstance()
{
	static CAttackState instance;
	return &instance;
}

//=============================================================================
//初期化関数
//=============================================================================
void CAttackState::Init(CJailer *jailer, CFan3D *fan3d)
{
	jailer->SetTimer(ZERO_INT);
}

//=============================================================================
//更新関数
//=============================================================================
void CAttackState::Update(CJailer *jailer, CFan3D *fan3d)
{
	if (jailer->AddTimer(1) >= 10)
	{
		jailer->ChangeState(CWaitState::GetInstance());
	}
}
