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

#include "camera_game.h"
#include "floor.h"
#include "fade.h"
#include "object.h"
#include "Screenframe.h"
#include "Timer.h"
#include "jailer.h"
#include "item_object_baton.h"
#include "item_object_jailer_room_key.h"
#include "item_object_map.h"
#include "item_object_pc_room_key.h"

#include "item_object_electrical_room_key.h"
#include "item_object_storage_key.h"
#include "map.h"
#include "object_wall.h"
#include "object_prison_door_left.h"
#include "object_prison_door_right.h"
#include "object_prison_wall.h"
#include "pause_button_manager.h"

#include "lever.h"
#include "particle_emitter.h"
#include "map_spot.h"
#include "fog.h"
#include "object_wood_box.h"
#include "object_wood_chair.h"
#include "object_wood_desk.h"
#include "object_metal_chair.h"
#include "object_metal_desk.h"
#include "object_generator.h"
#include "object_table.h"
#include "object_window_wall.h"
#include "goal_door.h"
#include "item_spawn.h"
#include "item_object_control_room_Key.h"

//=======================================================================================
// マクロ定義
//=======================================================================================
#define FLOOR_SIZE	(D3DXVECTOR3(10000.0f,0.0f,10000.0f))	// 床のサイズ
#define OBJECT_POS	(D3DXVECTOR3(1000.0f,0.0f,5000.0f))
#define PLAYER1_POS (D3DXVECTOR3(3801.0f,0.0f,-9234.0f))
#define PLAYER2_POS (D3DXVECTOR3(-821.0f,0.0f,-8215.0f))
#define MAP_POS1 (D3DXVECTOR3(5768.0f,0.0f,-12888.0f))
#define MAP_POS2 (D3DXVECTOR3(-1312.0f,0.0f,-5348.0f))
#define PRISON_KEY_POS1 (D3DXVECTOR3(2460.0f,0.0f,-9729.0f))
#define PRISON_KEY_POS2 (D3DXVECTOR3(-1050.0f,0.0f,-9027.0f))
#define STORAGE_KEY_POS1 (D3DXVECTOR3(2881.0f,0.0f,-9729.0f))
#define STORAGE_KEY_POS2 (D3DXVECTOR3(1943.0f,0.0f,-2438.0f))
#define PC_ROOM_KEY_POS1 (D3DXVECTOR3(4528.0f,0.0f,-4735.0f))
#define PC_ROOM_KEY_POS2 (D3DXVECTOR3(1930.0f,0.0f,-1880.0f))
#define JAILER_ROOM_KEY_POS1 (D3DXVECTOR3(4495.0f,0.0f,-2724.0f))
#define JAILER_ROOM_KEY_POS2 (D3DXVECTOR3(-1350.0f,0.0f,1000.0f))
#define BATON_POS1 (D3DXVECTOR3(5330.0f,0.0f,289.0f))
#define BATON_POS2 (D3DXVECTOR3(-547.0f,0.0f,-5331.0f))

//=======================================================================================
// コンストラクタ
//=======================================================================================
CGame::CGame()
{
	memset(&m_pCamera, 0, sizeof(m_pCamera));
	m_pLight = nullptr;
	memset(m_apPlayer, NULL, sizeof(m_apPlayer));
	m_pPauseButtonManager = nullptr;


	m_pItemSpawn = nullptr;
	memset(m_apJailer, NULL, sizeof(m_apJailer));
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
	m_pCamera[ID_PLAYER_01] = CCameraGame::Create(CCamera::SCREEN_LEFT);
	m_pCamera[ID_PLAYER_02] = CCameraGame::Create(CCamera::SCREEN_RIGHT);

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

	// 監視カメラの生成
	CreateSecCam();

	// UIの生成
	CScreenFrame::Create();
	CTimer::Create();

	// プレイヤーの生成
	CreatePlayer();

	CSound * pSound = GET_SOUND_PTR;
	pSound->StopAll();
	pSound->CSound::Play(CSound::SOUND_BGM_GAME);

	//スポットの初期化
	CMapSpot::Init();

	//看守の生成
	CreateJailer();


	if (m_pItemSpawn == nullptr)
	{
		m_pItemSpawn = CItemSpawn::Create();
		if (m_pItemSpawn != nullptr)
		{
			m_pItemSpawn->Init();
		}
	}

	// マップ生成	
	CMap::Create();

	return S_OK;
}

//=======================================================================================
// 終了処理
//=======================================================================================
void CGame::Uninit(void)
{
	for (int nCount = 0; nCount < ID_PLAYER_MAX; nCount++)
	{
		if (m_pCamera[nCount] != nullptr)
		{
			//カメラクラスの終了処理呼び出す
			m_pCamera[nCount]->Uninit();

			//メモリの破棄
			delete m_pCamera[nCount];

			//メモリのクリア
			m_pCamera[nCount] = nullptr;
		}
	}

	// ライトの終了処理
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	// プレイヤーの最大数分回す
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		// プレイヤーポインタのnullptrチェック
		if (m_apPlayer[nCount] != NULL)
		{
			// プレイヤーの終了処理関数呼び出し
			m_apPlayer[nCount]->Uninit();
			// プレイヤーのポインタを初期化する
			m_apPlayer[nCount] = nullptr;
		}
	}


}

//=======================================================================================
// 更新処理
//=======================================================================================
void CGame::Update(void)
{
	for (int nCount = 0; nCount < ID_PLAYER_MAX; nCount++)
	{
		if (m_pCamera[nCount] != nullptr)
		{
			//カメラクラスの更新処理
			m_pCamera[nCount]->Update();
		}
	}
	// ポーズ入力処理
	PauseInput();
	if (m_pItemSpawn != nullptr)
	{
		m_pItemSpawn->Update();
	}
}

//=======================================================================================
// 描画処理
//=======================================================================================
void CGame::Draw(void)
{
}

//=======================================================================================
// プレイヤーの生成
//=======================================================================================
void CGame::CreatePlayer(void)
{
	// プレイヤー1の生成
	if (m_apPlayer[0] == nullptr)
	{
		m_apPlayer[0] = CPlayer1::Create(PLAYER1_POS, ZeroVector3);
	}

	// プレイヤー2の生成
	if (m_apPlayer[1] == nullptr)
	{
		m_apPlayer[1] = CPlayer2::Create(PLAYER2_POS, ZeroVector3);
	}
}

//=======================================================================================
// 監視カメラの生成
//=======================================================================================
void CGame::CreateSecCam(void)
{
	// 左
	m_pCamera[0]->CreateSecCam(D3DXVECTOR3(1900.0f, 0.0f, -460.0f), D3DXToRadian(0.0f),2);
	m_pCamera[0]->CreateSecCam(D3DXVECTOR3(2950.0f, 0.0f, -550.0f), D3DXToRadian(220.0f),2);
	m_pCamera[0]->CreateSecCam(D3DXVECTOR3(1250.0f, 0.0f, -550.0f), D3DXToRadian(145.0f),2);
	m_pCamera[0]->CreateSecCam(D3DXVECTOR3(1300.0f, 0.0f, -2660.0f), D3DXToRadian(30.0f),2);
	m_pCamera[0]->CreateSecCam(D3DXVECTOR3(3690.0f, 0.0f, -3550.0f), D3DXToRadian(320.0f),1);
	m_pCamera[0]->CreateSecCam(D3DXVECTOR3(3300.0f, 0.0f, -4350.0f), D3DXToRadian(320.0f),1);
	m_pCamera[0]->CreateSecCam(D3DXVECTOR3(900.0f, 0.0f, -4500.0f), D3DXToRadian(150.0f),1);
	m_pCamera[0]->CreateSecCam(D3DXVECTOR3(3330.0f, 0.0f, -5850.0f), D3DXToRadian(320.0f),1);
	m_pCamera[0]->CreateSecCam(D3DXVECTOR3(1650.0f, 0.0f, -6590.0f), D3DXToRadian(40.0f),0);
	m_pCamera[0]->CreateSecCam(D3DXVECTOR3(3050.0f, 0.0f, -7350.0f), D3DXToRadian(145.0f),0);

	// 右
	m_pCamera[0]->CreateSecCam(D3DXVECTOR3(-1600.0f, 0.0f, -7350.0f), D3DXToRadian(145.0f),3);
	m_pCamera[0]->CreateSecCam(D3DXVECTOR3(-1780.0f, 0.0f, -6590.0f), D3DXToRadian(40.0f),3);
	m_pCamera[0]->CreateSecCam(D3DXVECTOR3(-1730.0f, 0.0f, -5850.0f), D3DXToRadian(40.0f),4);
	m_pCamera[0]->CreateSecCam(D3DXVECTOR3(450.0f, 0.0f, -4830.0f), D3DXToRadian(220.0f),4);
	m_pCamera[0]->CreateSecCam(D3DXVECTOR3(320.0f, 0.0f, -4420.0f), D3DXToRadian(320.0f),4);
	//m_pCamera[0]->CreateSecCam(D3DXVECTOR3(-250.0f, 0.0f, -3890.0f), D3DXToRadian(320.0f),4);
	//m_pCamera[0]->CreateSecCam(D3DXVECTOR3(-990.0f, 0.0f, -2730.0f), D3DXToRadian(40.0f),5);
	m_pCamera[0]->CreateSecCam(D3DXVECTOR3(340.0f, 0.0f, -900.0f), D3DXToRadian(180.0f),5);
	m_pCamera[0]->CreateSecCam(D3DXVECTOR3(1000.0f, 0.0f, -820.0f), D3DXToRadian(320.0f),5);
}

//=======================================================================================
// ポーズ入力処理
//=======================================================================================
void CGame::PauseInput(void)
{
	// キーボード取得
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	CInputJoypad *pJoypad = CManager::GetJoypad();
	// ポーズボタンマネージャーポインタのnullptrチェック
	if (m_pPauseButtonManager == nullptr)
	{
		// もしESCAPEキー押したら
		if (pKeyboard->GetTrigger(DIK_ESCAPE) || pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START,0) || pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 1))
		{
			// ポーズボタンマネージャーを生成する
			m_pPauseButtonManager = CPauseButtonManager::Create();
		}
	}
	else
	{
		// ポーズボタンマネージャーの更新処理関数
		m_pPauseButtonManager->Update();
		// もしESCAPEキー押したら
		if (pKeyboard->GetTrigger(DIK_ESCAPE) || pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) || pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 1))
		{
			// ポーズ状態を解除する
			CScene::SetPause(false);
		}
		// もしポーズ状態が解除されたら
		if (CScene::GetPause() == false)
		{
			// ポーズボタンマネージャーの終了処理関数
			m_pPauseButtonManager->Uninit();
			// ポーズボタンマネージャーのポインタを初期化する
			m_pPauseButtonManager = nullptr;
		}
	}
}

//=======================================================================================
// 看守の生成
//=======================================================================================
void CGame::CreateJailer(void)
{
	for (int nCntJailer = ZERO_INT; nCntJailer < MAX_JAILER; nCntJailer++)
	{
		//看守の生成
		m_apJailer[nCntJailer] = CJailer::Create(nCntJailer);
	}
}