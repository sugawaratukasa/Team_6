//=============================================================================
//インクルードファイル
//=============================================================================
#include "jailer_WaitState.h"
#include "jailer_AttackState.h"
#include "jailer.h"

void CAttackState::Init(CJailer *jailer)
{
	jailer->SetTimer(0);
}

void CAttackState::Update(CJailer *jailer)
{
	if (jailer->AddTimer(1) >= 10)
	{
		jailer->ChangeState(CWaitState::GetInstance());
	}
}
