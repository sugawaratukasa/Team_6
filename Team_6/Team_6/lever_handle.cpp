//=============================================================================
// レバーハンドル [lever_handle.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "lever_handle.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define DOWN_Y		(40.0f)	// レバーの下がる位置7
#define MOVE_Y		(2.0f)	// 移動
#define UP_COUNT	(150)	// カウント
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CLever_Handle::CLever_Handle(PRIORITY Priority) : CModel(Priority)
{
	m_InitPos = ZeroVector3;
	m_bDown = false;
	m_bOpen = false;
	m_nDownCnt = ZERO_INT;
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CLever_Handle::~CLever_Handle()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CLever_Handle * CLever_Handle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CLever_Handleのポインタ
	CLever_Handle *pLever_Handle = nullptr;

	// nullcheck
	if (pLever_Handle == nullptr)
	{
		// メモリ確保
		pLever_Handle = new CLever_Handle;

		// !nullcheck
		if (pLever_Handle != nullptr)
		{
			// 初期化処理
			pLever_Handle->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pLever_Handle;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CLever_Handle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 初期位置代入
	m_InitPos = pos;

	// 初期化処理
	CModel::Init(pos, rot);

	// モデル情報取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデル情報取得
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_LEVER_SWITCH_HANDLE);

		// モデルの情報を渡す
		BindModel(model);
	}
	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CLever_Handle::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CLever_Handle::Update(void)
{
	// 更新処理
	CModel::Update();

	// レバーが下げられているか
	if (m_bDown == true)
	{
		// 下がる処理
		Down();
		
		// 扉が開いていない場合
		if (m_bOpen == false)
		{
			// インクリメント
			m_nDownCnt++;

			// レバーの上がるカウントよりも大きくなった場合
			if (m_nDownCnt > UP_COUNT)
			{
				// 0に
				m_nDownCnt = ZERO_INT;

				// 上がっている状態に
				m_bDown = false;
			}
		}
	}
	// レバーが上げられている場合
	if (m_bDown == false)
	{
		// 上がる処理
		Up();
	}
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CLever_Handle::Draw(void)
{
	// 描画処理
	CModel::Draw();
}
//=============================================================================
// 下げる処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CLever_Handle::Down(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// 位置が元の位置の場合
	if (pos.y >= m_InitPos.y - DOWN_Y)
	{
		// 移動
		pos.y -= MOVE_Y;

		// 位置設定
		SetPos(pos);
	}
}
//=============================================================================
// 上げる処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CLever_Handle::Up(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// 位置が元の位置の場合
	if (pos.y <= m_InitPos.y)
	{
		// 移動
		pos.y += MOVE_Y;

		// 位置設定
		SetPos(pos);
	}
}