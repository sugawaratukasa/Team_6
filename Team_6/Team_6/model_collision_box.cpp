//=============================================================================
// モデル衝突チェック用箱 [model_collision_box.h]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "character.h"
#include "collision.h"
#include "model_collision_box.h"

//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CModelCollisionBox::CModelCollisionBox(PRIORITY Priority)
{
	m_pModel = nullptr;
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CModelCollisionBox::~CModelCollisionBox()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CModelCollisionBox * CModelCollisionBox::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel *pModel)
{
	// CModel_Boxのポインタ
	CModelCollisionBox *pBox = nullptr;

	// nullcheck
	if (pBox == nullptr)
	{
		// メモリ確保
		pBox = new CModelCollisionBox;

		// !nullcheck
		if (pBox != nullptr)
		{
			// ポインタ代入
			pBox->m_pModel = pModel;

			// 初期化処理
			pBox->Init(pos, ZeroVector3);
		}
	}
	// ポインタを返す
	return pBox;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CModelCollisionBox::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// モデル情報取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデル情報取得
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_BOX);

		// モデルの情報を渡す
		BindModel(model);
	}

	// サイズ取得
	D3DXVECTOR3 size = m_pModel->GetSize();

	// 拡大率の設定
	SetScale(size);

	// 初期化処理
	CModel::Init(pos, rot);

	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CModelCollisionBox::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CModelCollisionBox::Update(void)
{
	// 更新処理
	CModel::Update();

	// サイズ取得
	D3DXVECTOR3 size = m_pModel->GetSize();

	// 拡大率の設定
	SetScale(size);

	// 位置取得
	D3DXVECTOR3 pos = m_pModel->GetPos();

	// モデルの状態取得
	int nState = m_pModel->GetState();

	// 位置設定
	SetPos(pos);

	// 死亡状態の場合
	if (nState == CModel::STATE_DEAD)
	{
		// 終了
		Uninit();
		return;
	}
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CModelCollisionBox::Draw(void)
{
	// 描画処理
	CModel::Draw();
}