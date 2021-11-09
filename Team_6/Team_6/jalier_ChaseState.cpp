//=============================================================================
//
// 看守追跡状態クラス [jailer_Hierachystate.cpp]
// Author : OgumaAkira
//
//=============================================================================
#include "jailer_WaitState.h"
#include "jailer.h"
#include "jalier_ChaseState.h"
#include "Jailer_AttackState.h"
#include "jailer_LostTargetState.h"
//=============================================================================
//マクロ定義
//=============================================================================
#define CHASE_TIME (60)

//=============================================================================
//インスタンス生成関数
//=============================================================================
CChaseState * CChaseState::GetInstance()
{
	static CChaseState instance;
	return &instance;
}

//=============================================================================
//初期化関数
//=============================================================================
void CChaseState::Init(CJailer *pJailer, CJailerView *pJailerView)
{
	
}

//=============================================================================
//更新関数
//=============================================================================
void CChaseState::Update(CJailer *pJailer, CJailerView *pJailerView)
{
	//追跡する
	pJailer->Chase();

	//プレイヤーを発見している
	if (pJailerView->GetIsDetection() == true)
	{
		//当たり判定を行う
		if (pJailer->IsHitPlayer() == true)
		{
			//別の状態へ移行
			//警戒状態へ
			//pJailer->ChangeState(CJailer_LostTarget::GetInstance());
		}
	}
	else
	{
		if (pJailer->GetDistanceRange() <= 10.0f)
		{
			//警戒状態へ
			pJailer->ChangeState(CJailer_LostTarget::GetInstance());
		}
	}
}