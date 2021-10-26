//=============================================================================
//
// ŠÅŽçŠK‘w—pŠî’êó‘ÔƒNƒ‰ƒX [jailer_Hierachystate.cpp]
// Author : OgumaAkira
//
//=============================================================================
#include "jailer_WaitState.h"
#include "jalier_MoveState.h"
#include "jalier_ChaseState.h"
#include "jailer.h"


void CWaitState::Init(CJailer *jailer)
{
	jailer->SetTimer(0);
}

void CWaitState::Update(CJailer *jailer)
{
	if (jailer->AddTimer(1)>=10)
	{

	}
}
