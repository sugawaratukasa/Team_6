//=============================================================================
// 牢屋の扉 [object_prison_door_right.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "object_prison_door_left.h"
#include "object.h"
#include "manager.h"
#include "resource_manager.h"
#include "prison_door_collision.h"
#include "sound.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================

#define COLLISION_SIZE	(D3DXVECTOR3(180.0f,450.0f,50.0f))	// サイズ
#define COLLISION_SIZE2	(D3DXVECTOR3(50.0f,450.0f,180.0f))	// サイズ
#define ROT_90			(D3DXToRadian(89.0f))				// 向き
#define ROT_90			(D3DXToRadian(89.0f))				// 向き
#define ADD_POS			(10.0f)								// 位置加算
#define CLOSE_COUNT		(600)								// 扉を閉じるカウント
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CPrison_Door_Left::CPrison_Door_Left(PRIORITY Priority)
{
}
//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CPrison_Door_Left::~CPrison_Door_Left()
{
}
//=============================================================================
// 生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
CPrison_Door_Left * CPrison_Door_Left::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CPrison_Door_Leftのポインタ
	CPrison_Door_Left *pPrison_Door = nullptr;

	// nullcheck
	if (pPrison_Door == nullptr)
	{
		// メモリ確保
		pPrison_Door = new CPrison_Door_Left;

		// !nullcheck
		if (pPrison_Door != nullptr)
		{
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
HRESULT CPrison_Door_Left::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_PRISON_DOOR_LEFT);

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

	// 判定用オブジェクト生成
	CPrison_Door_Collision::Create(pos, rot, this);
	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPrison_Door_Left::Uninit(void)
{
	// ドアの終了処理関数呼び出し
	CDoor::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPrison_Door_Left::Update(void)
{
	// ドアの更新処理関数呼び出し
	CDoor::Update();

	// 開錠状態
	Open();
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPrison_Door_Left::Draw(void)
{
	// ドアの描画処理関数呼び出し
	CDoor::Draw();
}
//=============================================================================
// ドアを開く処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPrison_Door_Left::Open(void)
{
	// 向き取得
	D3DXVECTOR3 rot = GetRot();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// 初期位置取得
	D3DXVECTOR3 Initpos = GetInitPos();

	if (rot.y >= ROT_90)
	{
		// 初期値+サイズを足した位置まで移動
		if (pos.z <= Initpos.z + size.z)
		{
			// 位置取得
			GetPos().z += ADD_POS;
		}
	}
	else
	{
		// 初期値+サイズを足した位置まで移動
		if (pos.x >= Initpos.x - size.x)
		{
			// 位置取得
			GetPos().x -= ADD_POS;
		}
	}
}
//=============================================================================
// ドアを閉じる処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPrison_Door_Left::Close(void)
{
	// 初期位置取得
	D3DXVECTOR3 Initpos = GetInitPos();

	// 向き取得
	D3DXVECTOR3 rot = GetRot();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// 位置取得
	D3DXVECTOR3 pos = GetPos();
	CSound * pSound = GET_SOUND_PTR;
	// 90以上の場合
	if (rot.y >= ROT_90)
	{
		// 初期位置まで移動
		if (pos.z >= Initpos.z)
		{
			// 位置取得
			GetPos().z -= ADD_POS;
		}
		else
		{
			// ロック状態に
			SetLock(true);
			pSound->CSound::Play(CSound::SOUND_SE_OPEN_PRISON);
			// 0に
			GetCloseCnt() = ZERO_INT;
		}
	}
	else
	{
		// 初期値+サイズを足した位置まで移動
		if (pos.x <= Initpos.x)
		{
			// 位置取得
			GetPos().x += ADD_POS;
		}
		else
		{
			pSound->CSound::Play(CSound::SOUND_SE_OPEN_PRISON);
			// 0に
			GetCloseCnt() = ZERO_INT;

			// ロック状態に
			SetLock(true);
		}
	}
}
