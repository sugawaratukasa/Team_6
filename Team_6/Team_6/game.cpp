//=======================================================================================
//
// ゲーム処理 [game.cpp]
// Author : Sugawara Tsukasa
//
//=======================================================================================

//=======================================================================================
// インクルード
//=======================================================================================
#include "game.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "player_1.h"
#include "player_2.h"
#include "joypad.h"
#include "time.h"
#include "sound.h"
#include "keyboard.h"
#include "resource_manager.h"
#include "library.h"
#include "debug_proc.h"
#include "camera_game.h"
#include "floor.h"
#include "fade.h"
#include "object.h"

#include "item_object_baton.h"
#include "item_object_jailer_room_key.h"
#include "item_object_map.h"
#include "item_object_pc_room_key.h"
#include "item_object_prison_key.h"
#include "item_object_storage_key.h"

//=======================================================================================
// マクロ定義
//=======================================================================================
#define FLOOR_SIZE	(D3DXVECTOR3(10000.0f,0.0f,10000.0f))	// 床のサイズ
#define OBJECT_POS	(D3DXVECTOR3(1000.0f,0.0f,5000.0f))

#define PLAYER1_POS (D3DXVECTOR3(300.0f,0.0f,0.0f))
#define PLAYER2_POS (D3DXVECTOR3(-300.0f,0.0f,0.0f))

#define BATON_POS (D3DXVECTOR3(300.0f,0.0f,600.0f))
#define JAILER_ROOM_KEY_POS (D3DXVECTOR3(100.0f,0.0f,1500.0f))
#define MAP_POS (D3DXVECTOR3(-300.0f,0.0f,-600.0f))
#define PC_ROOM_KEY_POS (D3DXVECTOR3(600.0f,0.0f,300.0f))
#define PRISON_KEY_POS (D3DXVECTOR3(-600.0f,0.0f,-300.0f))
#define STORAGE_KEY_POS (D3DXVECTOR3(150.0f,0.0f,600.0f))

//=======================================================================================
// コンストラクタ
//=======================================================================================
CGame::CGame()
{
	m_pCamera = nullptr;
	m_pLight = nullptr;
	memset(m_apPlayer, NULL, sizeof(m_apPlayer));
	m_pFont = nullptr;
}

//=======================================================================================
// デストラクタ
//=======================================================================================
CGame::~CGame()
{
	// 終了処理
	Uninit();
}

//=======================================================================================
// 初期化処理
//=======================================================================================
HRESULT CGame::Init(void)
{
	// カメラクラスのクリエイト
	m_pCamera = CCameraGame::Create();

	//ライトクラスの生成
	m_pLight = new CLight;

	// ライトの初期化処理
	if (m_pLight != nullptr)
	{
		if (FAILED(m_pLight->Init()))
		{
			return -1;
		}
	}
	// プレイヤーの生成
	CreatePlayer();
	// アイテムの生成
	CreateItem();
	// 生成
	CreateGround();

	return S_OK;
}
//=======================================================================================
// 終了処理
//=======================================================================================
void CGame::Uninit(void)
{
	if (m_pCamera != nullptr)
	{
		//カメラクラスの終了処理呼び出す
		m_pCamera->Uninit();

		//メモリの破棄
		delete m_pCamera;

		//メモリのクリア
		m_pCamera = nullptr;
	}

	// ライトの終了処理
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	for (int nCount = 0; nCount < 2; nCount++)
	{
		if (m_apPlayer[nCount] != NULL)
		{
			m_apPlayer[nCount]->Uninit();
			m_apPlayer[nCount] = nullptr;
		}
	}

	// デバッグ情報表示用フォントの破棄
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
}

//=======================================================================================
// 更新処理
//=======================================================================================
void CGame::Update(void)
{
	if (m_pCamera != nullptr)
	{
		//カメラクラスの更新処理
		m_pCamera->Update();
	}

	// ゲームの設定
	SetGame();

}

//=======================================================================================
// 描画処理
//=======================================================================================
void CGame::Draw(void)
{

}

//=======================================================================================
// ゲームの設定
//=======================================================================================
void CGame::SetGame(void)
{
}

//=======================================================================================
// プレイヤーの生成
//=======================================================================================
void CGame::CreatePlayer(void)
{
	// プレイヤーの生成
	if (m_apPlayer[0] == nullptr)
	{
		m_apPlayer[0] = CPlayer1::Create(PLAYER1_POS, ZeroVector3);
	}
	// プレイヤーの生成
	if (m_apPlayer[1] == nullptr)
	{
		m_apPlayer[1] = CPlayer2::Create(PLAYER2_POS, ZeroVector3);
	}
}

//=======================================================================================
// アイテムの生成
//=======================================================================================
void CGame::CreateItem(void)
{
	CBatonObject::Create(BATON_POS, ZeroVector3);
	CJailerKeyObject::Create(JAILER_ROOM_KEY_POS, ZeroVector3);
	CMapObject::Create(MAP_POS, ZeroVector3);
	CPCRoomKeyObject::Create(PC_ROOM_KEY_POS, ZeroVector3);
	CPrisonKeyObject::Create(PRISON_KEY_POS, ZeroVector3);
	CStorageKeyObject::Create(STORAGE_KEY_POS, ZeroVector3);
}

//=======================================================================================
// マップの生成
//=======================================================================================
void CGame::CreateMap(void)
{
	// 地面の生成
	CreateGround();
}

//=======================================================================================
// 地面の生成
//=======================================================================================
void CGame::CreateGround(void)
{
	// 床生成
	CFloor::Create(ZeroVector3, FLOOR_SIZE);

	//CObject::Create(OBJECT_POS, ZeroVector3);
}