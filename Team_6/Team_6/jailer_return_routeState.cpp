//=============================================================================
//
// 看守待機状態クラス [jailer_WaitState.cpp]
// Author : Yamada Ryota
//
//=============================================================================
#include "jailer_return_routeState.h"
#include "jalier_MoveState.h"
#include "jalier_ChaseState.h"
#include "jailer.h"
#include "jailer_emotion.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define WAIT_TIME (100)	//待機する時間

//=============================================================================
//インスタンス生成関数
//=============================================================================
CReturnRouteState * CReturnRouteState::GetInstance()
{
	static CReturnRouteState instance;
	return &instance;
}

//=============================================================================
//初期化関数
//=============================================================================
void CReturnRouteState::Init(CJailer *pJailer, CJailerView *pJailerView)
{
	pJailer->SetTime(ZERO_INT);
	pJailer->SetRetrunData();
	pJailer->GetEmotion()->SetEmotion(CJailer_Emotion::EMOTION_TYPE_NONE);
}

//=============================================================================
//更新関数
//=============================================================================
void CReturnRouteState::Update(CJailer *pJailer, CJailerView *pJailerView)
{//索敵範囲にがいる場合

	pJailer->RetrunRoute();

	//索敵範囲にがいる場合
	if (pJailerView->GetIsDetection() == true)
	{
		//追跡状態へ
		pJailer->ChangeState(CChaseState::GetInstance());
	}
}
