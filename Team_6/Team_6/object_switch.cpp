//=============================================================================
// スイッチクラス [object_switch.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(150.0f,450.0f,50.0f))	// サイズ
#define COLLISION_SIZE2	(D3DXVECTOR3(50.0f,450.0f,150.0f))	// サイズ
#define ROT_180			(D3DXToRadian(179.0f))				// 向き
#define ROT_270			(D3DXToRadian(269.0f))				// 向き
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "object_switch.h"
#include "resource_manager.h"
#include "object_switch_collision.h"
#include "input.h"
#include "keyboard.h"
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CSwitch::CSwitch(PRIORITY Priority) : CObject(Priority)
{
	m_pPrison_Cell_Door = nullptr;
}

//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CSwitch::~CSwitch()
{
}
//=============================================================================
// 生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
CSwitch * CSwitch::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CPrison_Cell_Door *pPrison_Cell_Door)
{
	// CSwitchのポインタ
	CSwitch *pSwitch = nullptr;

	// nullcheck
	if (pSwitch == nullptr)
	{
		// メモリ確保
		pSwitch = new CSwitch;

		// !nullcheck
		if (pSwitch != nullptr)
		{
			// 初期化処理
			pSwitch->Init(pos, rot);

			// 独房のドアのポインタ代入
			pSwitch->m_pPrison_Cell_Door = pPrison_Cell_Door;
		}
	}
	// ポインタを返す
	return pSwitch;
}

//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CSwitch::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 判定生成
	CSwitch_Collision::Create(pos, rot, this);

	// 初期化処理
	CObject::Init(pos, rot);

	// モデル情報取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデル情報取得
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_SWITCH);

		// モデルの情報を渡す
		BindModel(model);
	}

	// 種類設定
	SetType(TYPE_SWITCH);

	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CSwitch::Uninit(void)
{
	// 終了処理
	CObject::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CSwitch::Update(void)
{
	// 更新処理
	CObject::Update();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CSwitch::Draw(void)
{
	// 描画処理
	CObject::Draw();
}
//=============================================================================
// ボタンを押す関数
// Author : Sugawara Tsukasa
//=============================================================================
void CSwitch::Push(void)
{
	// 扉を開く
	m_pPrison_Cell_Door->SetLock(false);
}