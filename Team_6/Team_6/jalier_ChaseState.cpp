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
	//追跡時間
	if (pJailer->AddTimer(ADD_TIME) >= CHASE_TIME)
	{
		//発見状態をリセットする
		pJailerView->ResetDetection();

		//索敵対象がいない場合
		if (pJailerView->GetIsDetection() == false)
		{
			//近いインデックスを検索

			//警戒状態へ
			pJailer->ChangeState(CJailer_LostTarget::GetInstance());

		}
	}
	else
	{
		//追跡する
		pJailer->Chase();
	}
}