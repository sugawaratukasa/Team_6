//=============================================================================
// スイッチクラス [object_switch.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_POS1	(D3DXVECTOR3(pos.x,0.0f,pos.z - 270))		// サイズ
#define COLLISION_POS2	(D3DXVECTOR3(pos.x,0.0f,pos.z + 270))		// サイズ
#define ROT_180			(D3DXToRadian(179.0f))						// 向き
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
#include "sound.h"

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
	// 向きが180°以下のの場合
	if (rot.y <= ROT_180)
	{
		// 判定生成
		CSwitch_Collision::Create(COLLISION_POS1, rot, this);
	}
	// 向きが180°以上の場合
	if (rot.y >= ROT_180)
	{
		// 判定生成
		CSwitch_Collision::Create(COLLISION_POS2, rot, this);
	}
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
	CSound * pSound = GET_SOUND_PTR;
	pSound->CSound::Play(CSound::SOUND_SE_PUSH_SWITCH);
	// 扉を開く
	m_pPrison_Cell_Door->SetLock(false);
}