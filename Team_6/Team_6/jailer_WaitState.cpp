//=============================================================================
//
// 看守待機状態クラス [jailer_WaitState.cpp]
// Author : OgumaAkira
//
//=============================================================================
#include "jailer_WaitState.h"
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
void CWaitState::Init(CJailer *jailer, CFan3D *fan3d)
{
	jailer->SetTimer(ZERO_INT);
}
//=============================================================================
//更新関数
//=============================================================================
void CWaitState::Update(CJailer *jailer, CFan3D *fan3d)
{//索敵範囲にがいる場合
	if (fan3d->GetDetection() == false)
	{	
		//待機時間
		if (jailer->AddTimer(ADD_TIME) >= WAIT_TIME)
		{
			jailer->AddIndex();
			//巡回状態へ
			jailer->ChangeState(CMoveState::GetInstance());
		}
		else
		{
			jailer->Wait();
		}
	}
	//索敵範囲にがいる場合
	else if (fan3d->GetDetection() == true)
	{
		//追跡状態へ
		jailer->ChangeState(CChaseState::GetInstance());
	}

}
