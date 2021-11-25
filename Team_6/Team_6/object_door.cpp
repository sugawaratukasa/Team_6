//=============================================================================
// ドア [object_door.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// マクロ定義
// Author : Nikaido Taichi
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(200.0f,500.f,25.0f))	// 当たり判定サイズ
#define COLLISION_SIZE2	(D3DXVECTOR3(25.0f,500.0f,200.0f))	// サイズ
#define ROT_90			(D3DXToRadian(89.0f))				// 向き
#define ADD_POS			(10.0f)								// 位置加算
//=============================================================================
// インクルードファイル
// Author : Nikaido Taichi
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "object_door.h"

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CDoor::CDoor(PRIORITY Priority) : CObject(Priority)
{
	m_Type = DOOR_NONE;		// ドアの種類
	m_bLock = true;			// ロック状態
	InitPos = ZeroVector3;
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CDoor::~CDoor()
{
}
//=============================================================================
// 生成処理関数
// Author : Nikaido Taichi
//=============================================================================
CDoor * CDoor::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CDoorのポインタ
	CDoor *pDoor = nullptr;

	// nukkcheck
	if (pDoor == nullptr)
	{
		// メモリ確保
		pDoor = new CDoor;

		// !nullchcek
		if (pDoor != nullptr)
		{
			// 初期化処理
			pDoor->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pDoor;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CDoor::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 初期化処理
	CObject::Init(pos, rot);

	// 初期位置代入
	InitPos = pos;

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

	// サイズ設定
	SetSize(COLLISION_SIZE);

	// 90以上の場合
	if (rot.y >= ROT_90)
	{
		// サイズ
		SetSize(COLLISION_SIZE2);
	}
	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CDoor::Uninit(void)
{
	// 終了処理
	CObject::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CDoor::Update(void)
{
	// 更新処理
	CObject::Update();

	// ドアを開く処理
	//Open();

	// ドアを閉じる
	Close();
}
//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CDoor::Draw(void)
{
	// 描画処理
	CObject::Draw();
}
//=============================================================================
// ドアを開く処理関数
// Author : Nikaido Taichi
//=============================================================================
void CDoor::Open(void)
{
	// 向き取得
	D3DXVECTOR3 rot = GetRot();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// 90以上の場合
	if (rot.y >= ROT_90)
	{
		// 初期値+サイズを足した位置まで移動
		if (pos.z <= InitPos.z + size.z)
		{
			// 位置取得
			GetPos().z += ADD_POS;
		}
	}
	else
	{
		// 初期値+サイズを足した位置まで移動
		if (pos.x >= InitPos.x - size.x)
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
void CDoor::Close(void)
{
	// 向き取得
	D3DXVECTOR3 rot = GetRot();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// 90以上の場合
	if (rot.y >= ROT_90)
	{
		// 初期位置まで移動
		if (pos.z >= InitPos.z)
		{
			// 位置取得
			GetPos().z -= ADD_POS;
		}
	}
	else
	{
		// 初期値+サイズを足した位置まで移動
		if (pos.x <= InitPos.x)
		{
			// 位置取得
			GetPos().x += ADD_POS;
		}
	}
}