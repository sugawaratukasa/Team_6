//=============================================================================
// 看守室ドアの判定 [guards_door_collision.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "electrical_room_door_collision.h"
#include "map_spot.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(120.0f,450.0f,120.0f))	// サイズ
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CElectrical_Room_Door_Collision::CElectrical_Room_Door_Collision(PRIORITY Priority) : CDoor_Collision(Priority)
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CElectrical_Room_Door_Collision::~CElectrical_Room_Door_Collision()
{
}
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
CElectrical_Room_Door_Collision * CElectrical_Room_Door_Collision::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CDoor *pDoor)
{
	// CElectrical_Room_Door_Collisionのポインタ
	CElectrical_Room_Door_Collision *pElectrical_Room_Door_Collision = nullptr;

	// nullcheck
	if (pElectrical_Room_Door_Collision == nullptr)
	{
		// メモリ確保
		pElectrical_Room_Door_Collision = new CElectrical_Room_Door_Collision;

		// !nullcheck
		if (pElectrical_Room_Door_Collision != nullptr)
		{
			// 初期化処理
			pElectrical_Room_Door_Collision->Init(pos, rot);

			// ポインタを代入
			pElectrical_Room_Door_Collision->SetpDoor(pDoor);
		}
	}
	// ポインタを返す
	return pElectrical_Room_Door_Collision;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CElectrical_Room_Door_Collision::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 初期化処理
	CDoor_Collision::Init(pos, rot);

	// タイプ設定
	SetType(TYPE_ELECTRICAL_ROOM);

	// サイズ設定
	SetSize(COLLISION_SIZE);
	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CElectrical_Room_Door_Collision::Uninit(void)
{
	// 終了処理
	CDoor_Collision::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CElectrical_Room_Door_Collision::Update(void)
{
	// 更新処理
	CDoor_Collision::Update();

	// CDoorのポインタ取得
	CDoor *pDoor = GetpDoor();

	// ロック状態設定
	SetLock(pDoor->GetLock());
}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CElectrical_Room_Door_Collision::Draw(void)
{
}
//=============================================================================
// 開く処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CElectrical_Room_Door_Collision::Open(int nPlayer)
{
	// 開く処理
	CDoor_Collision::Open(nPlayer);

	// テクスチャ取得
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

	// ドア取得
	CDoor *pDoor = GetpDoor();

	// ドアのサイド取得
	CDoor::SIDE side = pDoor->GetSide();

	// 左の場合
	if (side == CDoor::SIDE_LEFT)
	{
		// 扉が開いたかを設定
		CMapSpot::SetIsOpenRoom(CMapSpot::MAP_AREA_LEFT, CMapSpot::ROOM_TYPE_POWER_ROOM);
	}
	// 右の場合
	if (side == CDoor::SIDE_RIGHT)
	{
		// 扉が開いたかを設定
		CMapSpot::SetIsOpenRoom(CMapSpot::MAP_AREA_RIGHT, CMapSpot::ROOM_TYPE_POWER_ROOM);
	}

	// プレイヤー1の場合
	if (nPlayer == PLAYER_1)
	{
		// テキストログ生成
		CTextLog::Create(CTexture::TEXTURE_LOG_P1_OPEN_DOOR);
	}
	// プレイヤー2の場合
	if (nPlayer == PLAYER_2)
	{
		// テキストログ生成
		CTextLog::Create(CTexture::TEXTURE_LOG_P2_OPEN_DOOR);
	}
}

//=============================================================================
// 開けない処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CElectrical_Room_Door_Collision::NotOpen(int nPlayer)
{
	// テクスチャ取得
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

	// プレイヤー1の場合
	if (nPlayer == PLAYER_1)
	{
		// テキストログ生成
		CTextLog::Create(CTexture::TEXTURE_LOG_P1_NOT_OPEN_DOOR);
	}
	// プレイヤー2の場合
	if (nPlayer == PLAYER_2)
	{
		// テキストログ生成
		CTextLog::Create(CTexture::TEXTURE_LOG_P2_NOT_OPEN_DOOR);
	}
}