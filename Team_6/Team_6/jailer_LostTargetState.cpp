//=============================================================================
//
// 看守のターゲットを見失った状態処理 [jailer_LostTargetState.cpp]
// Author : Yamada Ryota
//
//=============================================================================
#include "jailer_LostTargetState.h"
#include "jailer.h"
#include "jailer_view.h"
#include "Jalier_MoveState.h"
#include "jalier_ChaseState.h"
#include "jailer_return_routeState.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define CAUTION_TIME (60)	//警戒する時間

//=============================================================================
//静的メンバ変数宣言
//=============================================================================
CJailer_LostTarget *CJailer_LostTarget::m_pShingleton = nullptr;

//=============================================================================
//デストラクタ
//=============================================================================
CJailer_LostTarget::~CJailer_LostTarget()
{
}

//=============================================================================
//インスタンス取得
//=============================================================================
CJailer_LostTarget * CJailer_LostTarget::GetInstance(void)
{
	if (!m_pShingleton)
	{
		//インスタンス生成
		m_pShingleton = new CJailer_LostTarget;

		if (m_pShingleton)
		{
			return m_pShingleton;
		}
		else
		{
			return nullptr;
		}
	}
	return m_pShingleton;
}

//=============================================================================
//インスタンス解放
//=============================================================================
void CJailer_LostTarget::Release(void)
{
	if (m_pShingleton)
	{
		delete m_pShingleton;

		m_pShingleton = nullptr;
	}
}

//=============================================================================
//初期化処理
//=============================================================================
void CJailer_LostTarget::Init(CJailer * pJailer, CJailerView * pJailerView)
{
	//タイマーのセット
	pJailer->SetTimer(ZERO_INT);
	pJailer->SetSpeed(ZERO_FLOAT);
	pJailer->SetMove(ZeroVector3);
	pJailerView->JailerCaution(false);
}

//=============================================================================
//更新処理
//=============================================================================
void CJailer_LostTarget::Update(CJailer * pJailer, CJailerView * pJailerView)
{
	//警戒
	pJailer->Caution();

	//発見したら
	if (pJailerView->GetIsDetection() == true)
	{
		//追跡状態へ
		pJailer->ChangeState(CChaseState::GetInstance());
	}
	else
	{
		//未発見状態が一定時間続いたら
		if (pJailer->AddTimer(ADD_TIME) >= CAUTION_TIME)
		{
			//巡回状態へ
			pJailer->ChangeState(CWaitState::GetInstance());
		}
	}
}

//=============================================================================
//コンストラクタ
//=============================================================================
CJailer_LostTarget::CJailer_LostTarget()
{
}
