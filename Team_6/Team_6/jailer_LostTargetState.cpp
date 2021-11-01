//=============================================================================
//
// 看守のターゲットを見失った状態処理 [jailer_LostTargetState.cpp]
// Author : Yamada Ryota
//
//=============================================================================
#include "jailer_LostTargetState.h"
#include "jailer.h"
#include "jailer_view.h"

//=============================================================================
//静的メンバ変数宣言
//=============================================================================
CJailer_LostTarget *CJailer_LostTarget::m_pShingleton = nullptr;

//=============================================================================
//デストラクタ
//=============================================================================
CJailer_LostTarget::~CJailer_LostTarget()
{
	if (m_pShingleton)
	{
		delete m_pShingleton;

		m_pShingleton = nullptr;
	}
}

//=============================================================================
//インスタンス取得
//=============================================================================
CJailer_LostTarget * CJailer_LostTarget::GetInstance()
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
//初期化処理
//=============================================================================
void CJailer_LostTarget::Init(CJailer * pJailer, CJailerView * pJailerView)
{
	//タイマーのセット
	pJailer->SetTimer(ZERO_INT);
}

//=============================================================================
//更新処理
//=============================================================================
void CJailer_LostTarget::Update(CJailer * pJailer, CJailerView * pJailerView)
{
}

//=============================================================================
//コンストラクタ
//=============================================================================
CJailer_LostTarget::CJailer_LostTarget()
{
}
