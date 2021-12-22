//=============================================================================
// ゴールエリア [goal_area.cpp]
// Author : Nikaido Taichi
//=============================================================================
#include "goal_area.h"
#include "character.h"
#include "model_collision_box.h"
#include "model.h"
#include "player.h"
#include "manager.h"
#include "mode_base.h"
#include "collision.h"
#include "fade.h"

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CGoalArea::CGoalArea()
{
	m_bGoal = false;		// ゴール状態
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CGoalArea::~CGoalArea()
{
}

//=============================================================================
// 生成処理関数
// Author : Nikaido Taichi
//=============================================================================
CGoalArea * CGoalArea::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//タイトルに戻るボタンのポインタ
	CGoalArea * pGoalArea = nullptr;
	//タイトルに戻るボタンのポインタがnullptrの場合
	if (pGoalArea == nullptr)
	{
		//タイトルに戻るボタンのメモリ確保
		pGoalArea = new CGoalArea;
		//タイトルに戻るボタンのポインタがnullptrではない場合
		if (pGoalArea != nullptr)
		{
			//タイトルに戻るボタンの初期化処理関数呼び出し
			pGoalArea->Init(pos,rot);
		}
	}
	//タイトルに戻るボタンのポインタを返す
	return pGoalArea;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CGoalArea::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// モデルの初期化処理関数呼び出し
	CModel::Init(pos, rot);
	SetSize(D3DXVECTOR3(1200.0f, 1000.0f, 500.0f));
	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CGoalArea::Uninit(void)
{
	// モデルの終了処理関数呼び出し
	CModel::Uninit();
}

//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CGoalArea::Update(void)
{
	// モデルの更新処理関数呼び出し
	CModel::Update();
	// ゴール処理関数
	Goal();
}

//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CGoalArea::Draw(void)
{
}

//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CGoalArea::Goal(void)
{
	// 位置を取得する
	D3DXVECTOR3 Position = GetPos();
	// サイズを取得する
	D3DXVECTOR3 Size = GetSize();
	// プレイヤーのポインタ
	CPlayer * apPlayer[MAX_PLAYER];
	// プレイヤーのゴール状態
	bool bPlayerGoal[MAX_PLAYER];
	// プレイヤーの最大数分回す
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		// プレイヤーのポインタを取得する
		apPlayer[nCount] = CManager::GetModePtr()->GetPlayer(nCount);
		// !nullcheck
		if (apPlayer[nCount] != nullptr)
		{
			// プレイヤーの位置を取得する
			D3DXVECTOR3 PlayerPosition = apPlayer[nCount]->GetPos();
			// プレイヤーのサイズを取得する
			D3DXVECTOR3 PlayerSize = apPlayer[nCount]->GetSize();
			// プレイヤーの矩形型の当たり判定
			if (CCollision::CollisionRectangleAndRectangle(Position, PlayerPosition, Size, PlayerSize) == true)
			{
				// プレイヤーのゴール状態をtrueにする
				apPlayer[nCount]->SetbGoal(true);
			}
			// プレイヤーのゴール状態を取得する
			bPlayerGoal[nCount] = apPlayer[nCount]->GetbGoal();
		}
	}
	// もしプレイヤー1とプレイヤー2の両方がtrueの場合
	if (bPlayerGoal[0] == true && bPlayerGoal[1] == true)
	{
		// もしゴール状態がfalseの場合
		if (m_bGoal == false)
		{
			// 遷移
			CFade *pFade = CManager::GetFade();
			pFade->SetFade(CManager::MODE_TYPE_RANKING_RESULT);
			// ゴール状態をtrueにする
			m_bGoal = true;
		}
	}
}