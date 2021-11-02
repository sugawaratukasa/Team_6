//=============================================================================
//
// 看守巡回状態クラス [jalier_MoveState.cpp]
// Author : OgumaAkira
//
//=============================================================================

//=============================================================================
//マクロ定義
//=============================================================================
#define MOVE_TIME (200)	//移動する時間

//=============================================================================
//インクルードファイル
//=============================================================================
#include "jailer_WaitState.h"
#include "jalier_MoveState.h"
#include "jalier_ChaseState.h"
#include "jailer.h"

//=============================================================================
//インスタンス生成関数
//=============================================================================
CMoveState * CMoveState::GetInstance()
{
	static CMoveState instance;
	return &instance;
}

//=============================================================================
//初期化関数
//=============================================================================
void CMoveState::Init(CJailer *pJailer, CJailerView *pJailerView)
{
	pJailer->SetTimer(ZERO_INT);
}

//=============================================================================
//更新関数
//=============================================================================
void CMoveState::Update(CJailer *pJailer, CJailerView *pJailerView)
{
	int time = pJailer->AddTimer(ADD_TIME);
	
	if (pJailerView->GetIsDetection() == false)
	{
		pJailer->Move();
		//移動時間
		if (time >= MOVE_TIME)
		{
			//待機状態へ
			pJailer->ChangeState(CWaitState::GetInstance());
		}
	}
	//索敵範囲にがいる場合
	else 
	{
		//追跡状態へ
		pJailer->ChangeState(CChaseState::GetInstance());
	}
}
