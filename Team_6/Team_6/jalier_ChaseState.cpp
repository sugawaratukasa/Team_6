#include "jailer_WaitState.h"
#include "jailer.h"
#include "jalier_ChaseState.h"
#include "Jailer_AttackState.h"



void CChaseState::Init(CJailer *jailer)
{

}

void CChaseState::Update(CJailer *jailer)
{
	if (jailer->IsDistanceToPlayer(2.0f))
	{
		jailer->ChangeState(CAttackState::GetInstance());
	}
	else if (jailer->IsDistanceToPlayer(15.0f,true))
	{
		jailer->ChangeState(CWaitState::GetInstance());
	}
	else
	{
		jailer->Chase();
	}
}


