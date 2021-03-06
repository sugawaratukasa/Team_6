//=============================================================================
//
// 看守巡回状態クラス [jalier_MoveState.cpp]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//マクロ定義
//=============================================================================
#define MOVE_TIME (200)	//移動する時間

//=============================================================================
//インクルードファイル
//=============================================================================
#include "jailer_return_routeState.h"
#include "jalier_MoveState.h"
#include "jalier_ChaseState.h"
#include "jailer.h"
#include "jailer_emotion.h"

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
	pJailer->SetTime(ZERO_INT);
	pJailer->GetEmotion()->SetEmotion(CJailer_Emotion::EMOTION_TYPE_NONE);
}

//=============================================================================
//更新関数
//=============================================================================
void CMoveState::Update(CJailer *pJailer, CJailerView *pJailerView)
{
	if (pJailerView->GetIsDetection() == false)
	{
		pJailer->Patrol();
	}
	//索敵範囲にがいる場合
	else 
	{
		//追跡状態へ
		pJailer->ChangeState(CChaseState::GetInstance());
	}
}
