#include "jailer_WaitState.h"
#include "jalier_MoveState.h"
#include "jalier_ChaseState.h"
#include "jailer.h"

void CMoveState::Init(CJailer * jailer)
{
	jailer->SetTimer(0);
}

void CMoveState::Update(CJailer *jailer)
{
	int time = jailer->AddTimer(1);
}
