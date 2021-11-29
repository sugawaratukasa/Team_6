//=============================================================================
//
// 看守待機状態クラス [jailer_WaitState.cpp]
// Author : OgumaAkira
//
//=============================================================================
#include "jailer_return_routeState.h"
#include "jalier_MoveState.h"
#include "jalier_ChaseState.h"
#include "jailer.h"
//=============================================================================
//マクロ定義
//=============================================================================
#define WAIT_TIME (100)	//待機する時間

//=============================================================================
//インスタンス生成関数
//=============================================================================
CWaitState * CWaitState::GetInstance()
{
	static CWaitState instance;
	return &instance;
}

//=============================================================================
//初期化関数
//=============================================================================
void CWaitState::Init(CJailer *pJailer, CJailerView *pJailerView)
{
	pJailer->SetTimer(ZERO_INT);

	pJailer->SetRetrunData();
}
//=============================================================================
//更新関数
//=============================================================================
void CWaitState::Update(CJailer *pJailer, CJailerView *pJailerView)
{//索敵範囲にがいる場合

	pJailer->RetrunRoute();
	//if (pJailerView->GetIsDetection() == false)
	//{	
	//	//待機時間
	//	if (pJailer->AddTimer(ADD_TIME) >= WAIT_TIME)
	//	{
	//		pJailer->SettingPosDest();
	//		//巡回状態へ
	//		pJailer->ChangeState(CMoveState::GetInstance());
	//	}
	//	else
	//	{
	//		
	//	}
	//}
	////索敵範囲にがいる場合
	//else if (pJailerView->GetIsDetection() == true)
	//{
	//	//追跡状態へ
	//	pJailer->ChangeState(CChaseState::GetInstance());
	//}

}
