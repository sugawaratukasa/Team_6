//=============================================================================
// 牢屋の扉 [object_prison_door_right.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "prison_cell_door.h"
#include "object.h"
#include "manager.h"
#include "resource_manager.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE		(D3DXVECTOR3(130.0f,330.0f,25.0f))	// サイズ
#define COLLISION_SIZE2		(D3DXVECTOR3(25.0f,330.0f,130.0f))	// サイズ
#define ROT_90				(D3DXToRadian(89.0f))				// 向き
#define CLOSE_COUNT			(1200)								// 扉を閉じるカウント
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CPrison_Cell_Door::CPrison_Cell_Door(PRIORITY Priority)
{
	m_pPlayer = nullptr;
	m_nCloseCnt = ZERO_INT;
}
//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CPrison_Cell_Door::~CPrison_Cell_Door()
{
}
//=============================================================================
// 生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
CPrison_Cell_Door * CPrison_Cell_Door::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CPlayer *pPlayer)
{
	// CPrison_Cell_Doorのポインタ
	CPrison_Cell_Door *pPrison_Door = nullptr;

	// nullcheck
	if (pPrison_Door == nullptr)
	{
		// メモリ確保
		pPrison_Door = new CPrison_Cell_Door;

		// !nullcheck
		if (pPrison_Door != nullptr)
		{
			// CPlayerのポインタ代入
			pPrison_Door->m_pPlayer = pPlayer;

			// 初期化処理
			pPrison_Door->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pPrison_Door;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CPrison_Cell_Door::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ドアの初期化処理関数呼び出し
	CDoor::Init(pos, rot);

	// サイズ
	SetSize(COLLISION_SIZE);

	// モデル情報取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデル情報取得
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_DOOR);

		// モデルの情報を渡す
		BindModel(model);
	}

	// 90以上の場合
	if (rot.y >= ROT_90)
	{
		// サイズ
		SetSize(COLLISION_SIZE2);
	}

	//OBBの作成
	SetObb(CObb::Create(pos, rot, GetMesh()));

	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPrison_Cell_Door::Uninit(void)
{
	// ドアの終了処理関数呼び出し
	CDoor::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPrison_Cell_Door::Update(void)
{
	// 更新処理
	CDoor::Update();

	// !nullcheck
	if (m_pPlayer != nullptr)
	{
		// 捕まっているか取得
		bool bIncapacitated = m_pPlayer->GetbIncapacitated();

		// trueの場合
		if (bIncapacitated == true)
		{
			// 閉じる
			Close();
		}
		else
		{
			// 開く
			Open();
		}
	}
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPrison_Cell_Door::Draw(void)
{
	// ドアの描画処理関数呼び出し
	CDoor::Draw();
}
//=============================================================================
// ボタンを押した処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPrison_Cell_Door::Push(void)
{
	// 更新処理
	CObject::Update();

	// !nullcheck
	if (m_pPlayer != nullptr)
	{
		// trueの場合
		if (m_pPlayer->GetbIncapacitated() == true)
		{
			// falseに
			m_pPlayer->SetbIncapacitated(false);

			// カウント0に
			m_pPlayer->GetIncapacitatedTimeCount() = ZERO_INT;
		}
	}
}
//=============================================================================
// 開閉処理関数　
// Author : Sugawara Tsukasa
//=============================================================================
void CPrison_Cell_Door::Open_and_Close(void)
{
	// インクリメント
	m_nCloseCnt++;

	// CLOSE_COUNTより小さい場合
	if (m_nCloseCnt <= CLOSE_COUNT)
	{
		// ドアを開く処理

		this->Open();
	}

	// CLOSE_COUNTより大きくなった場合
	if (m_nCloseCnt >= CLOSE_COUNT)
	{
		// 扉を閉じる処理
		this->Close();
	}
}
