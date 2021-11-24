#include "goal_area.h"
#include "character.h"
#include "model_collision_box.h"
#include "model.h"

CGoalArea::CGoalArea()
{
}

CGoalArea::~CGoalArea()
{
}

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

HRESULT CGoalArea::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CModel::Init(pos, rot);
	CModelCollisionBox::Create(pos, rot, this);
	return S_OK;
}

void CGoalArea::Uninit(void)
{
	CModel::Uninit();
}

void CGoalArea::Update(void)
{
	CModel::Update();
	Goal();
}

void CGoalArea::Draw(void)
{
	CModel::Draw();
}

void CGoalArea::Goal(void)
{
}
