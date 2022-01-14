//=============================================================================
//
// 看守追跡状態クラス [jailer_Hierachystate.cpp]
// Author : Yamada Ryota
//
//=============================================================================
#include "jailer_return_routeState.h"
#include "jailer.h"
#include "jalier_ChaseState.h"
#include "Jailer_AttackState.h"
#include "jailer_LostTargetState.h"
#include "manager.h"
#include "renderer.h"
#include "fog.h"
#include "jailer_emotion.h"

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
	pJailer->SetTime(0);

	//検出したプレイヤー番号を取得
	int nPlayerNumber = pJailerView->GetDetectionNumber();

	//フォグのポインタを取得
	CFog *pFog = CManager::GetRenderer()->GetFog(nPlayerNumber);

	//フォグをワーニングに指定
	pFog->SetFogState(CFog::FOG_WARNING);

	pJailer->GetEmotion()->SetEmotion(CJailer_Emotion::EMOTION_TYPE_ANGER);
}

//=============================================================================
//更新関数
//=============================================================================
void CChaseState::Update(CJailer *pJailer, CJailerView *pJailerView)
{
	//追跡する
	pJailer->ChasePlayer();

	//プレイヤーを発見している
	if (pJailerView->GetIsDetection() == true)
	{
		pJailer->SetTime(0);

		//当たり判定を行う
		if (pJailer->IsHitPlayer() == true)
		{
			//検出したプレイヤー番号を取得
			int nPlayerNumber = pJailerView->GetDetectionNumber();

			//フォグのポインタを取得
			CFog *pFog = CManager::GetRenderer()->GetFog(nPlayerNumber);

			//フォグの終了
			pFog->SetFogState(CFog::FOG_END);

			//別の状態へ移行
			//警戒状態へ
			pJailer->ChangeState(CJailer_LostTarget::GetInstance());
		}
	}
	else
	{
		int nTime = pJailer->AddTime(1);

		if (pJailer->GetDestLength() <= 10.0f || nTime == 60)
		{
			//検出したプレイヤー番号を取得
			int nPlayerNumber = pJailerView->GetDetectionNumber();

			//フォグのポインタを取得
			CFog *pFog = CManager::GetRenderer()->GetFog(nPlayerNumber);

			//フォグの終了
			pFog->SetFogState(CFog::FOG_END);

			//警戒状態へ
			pJailer->ChangeState(CJailer_LostTarget::GetInstance());
		}
	}
}