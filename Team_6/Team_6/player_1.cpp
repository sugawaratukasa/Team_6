//=============================================================================
// プレイヤー1 [player_1.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// インクルードファイル
// Author : Nikaido Taichi
//=============================================================================
#include "manager.h"
#include "game.h"
#include "player_1.h"
#include "keyboard.h"
#include "joypad.h"
#include "resource_manager.h"
#include "ui_player1_item.h"
#include "resource_manager.h"
#include "sound.h"
#include "jailer_key_guid_texture.h"
#include "pc_room_key_guid_texture.h"

#include "electrical_room_key_guid_texture.h"
#include "storage_key_guid_texture.h"
#include "baton_guid_texture.h"
#include "map_guid_texture.h"
#include "control_room_key_guid_texture.h"
#include "guid_bg.h"
#include "camera_game.h"
#include "bg_black_texture.h"
#include "caveatbar.h"
#include "renderer.h"

//=============================================================================
// マクロ定義
// Author : Nikaido Taichi
//=============================================================================
#define PRISON_POSITION (D3DXVECTOR3(2450.0f, 0.0f, -7139.0f))	//独房の位置

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CPlayer1::CPlayer1(PRIORITY Priority)
{
	m_rotDest = ZeroVector3;
	m_bBlackTextureCreate = false;
	m_pItemGuidTexture = nullptr;
	m_pGuidBG = nullptr;
	m_pBlackTexture = nullptr;
	m_pCaveatBar = nullptr;
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CPlayer1::~CPlayer1()
{
}

//=============================================================================
// 生成処理関数
// Author : Nikaido Taichi
//=============================================================================
CPlayer1 * CPlayer1::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CPlayer1のポインタ
	CPlayer1 *pPlayer1 = nullptr;

	// nullcheck
	if (pPlayer1 == nullptr)
	{
		// メモリ確保
		pPlayer1 = new CPlayer1;

		// !nullcheck
		if (pPlayer1 != nullptr)
		{
			// 初期化処理
			pPlayer1->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pPlayer1;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CPlayer1::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// タイプ設定
	SetType(PLAYER_1);
	// CXfile取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデル生成
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_PLAYER1);
	}
	// プレイヤーの初期化処理関数呼び出し
	CPlayer::Init(pos, rot);
	// プレイヤー1のUI生成
	SetUI(CPlayer1ItemUI::Create());


	//プレイヤー1の警告バー生成
	m_pCaveatBar = CCaveatBar::Create(D3DXVECTOR3(300.0f, SCREEN_HEIGHT - 100.0f, 0), PLAYER_1);

	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPlayer1::Uninit(void)
{
	// プレイヤーの終了処理関数呼び出し
	CPlayer::Uninit();
}

//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPlayer1::Update(void)
{
	// プレイヤーの更新処理関数呼び出し
	CPlayer::Update();
	// 行動不能状態取得
	bool bIncapacitated = GetbIncapacitated();
	// ゴール状態取得
	bool bGoal = GetbGoal();
	// アイテム説明テクスチャの生成状態
	bool bItemGuidCreate = GetbGuidCreate();
	// スピード取得
	float fSpeed = GetSpeed();

	// カメラ角度取得
	float fAngle = ((CGame*)CManager::GetModePtr())->GetCamera(0)->GetHorizontal();

	// レンダラー取得
	CRenderer *pRenderer = CManager::GetRenderer();

	// 監視カメラ使用状態取得
	bool bCameraUse = pRenderer->GetIsUseSecCamPlayer(PLAYER_1);

	// もし行動可能状態の場合
	if (bIncapacitated == false)
	{
		if (m_bBlackTextureCreate == true)
		{
			if (m_pBlackTexture != nullptr)
			{
				m_pBlackTexture->Uninit();
				m_pBlackTexture = nullptr;
				m_bBlackTextureCreate = false;
			}
		}
		// カメラを使っていない場合
		if (bCameraUse == false)
		{
			// パッド移動
			//PadMove(fSpeed, fAngle);
			// キーボード移動処理
			InputMove(fSpeed, fAngle);
		}
	}
	// もし行動不能状態の場合又はゴール状態の場合
	if(bIncapacitated == true || bItemGuidCreate == true || bGoal == true)
	{
		// 移動量を0にする
		SetMove(ZeroVector3);
		// 待機モーション再生
		SetMotion(MOTION_IDOL);
	}
	if (bIncapacitated == true)
	{
		if (m_bBlackTextureCreate == false)
		{
			if (m_pBlackTexture == nullptr)
			{
				m_pBlackTexture = CBlackTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT, 0.0f));
				m_bBlackTextureCreate = true;
			}
		}
	}
	// 向き補正処理
	UpdateRot();
	if (bItemGuidCreate == false && bCameraUse == false)
	{
		// アイテム削除処理関数呼び出し
		ItemDelete(PLAYER_1);
	}

	// 扉を開く処理
	DoorOpen(PLAYER_1);

	//警告バー処理
	if (m_pCaveatBar != nullptr)
	{
		m_pCaveatBar -> Update();
	}

	// カメラ使用処理
	UseSecurity_Cam(PLAYER_1);

	// ダクトアイテム受け渡し
	Item_DuctPass(PLAYER_1);
}

//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPlayer1::Draw(void)
{
	// プレイヤーの描画処理関数呼び出し
	CPlayer::Draw();
}

//=============================================================================
// 独房ワープ処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPlayer1::PrisonWarp(void)
{
	// サウンドのポインタを取得する
	CSound * pSound = GET_SOUND_PTR;
	// ワープ時SEの再生
	pSound->Play(CSound::SOUND_SE_OPEN_PRISON);
	// 行動不能状態にする
	SetbIncapacitated(true);
	// 独房にワープさせる
	SetPos(PRISON_POSITION);
}

//=============================================================================
// アイテム説明テクスチャの生成
// Author : Nikaido Taichi
//=============================================================================
void CPlayer1::SetbGuidCreate(CItemObject::ITEM_OBJECT_LIST Type)
{

	if (m_pItemGuidTexture == nullptr && m_pGuidBG == nullptr)
	{
		m_pGuidBG = CGuidBG::Create(D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 0.0f));
		switch (Type)
		{
		case CItemObject::ITEM_OBJECT_KEY_STORAGE:
			m_pItemGuidTexture = CStorageKeyGuidTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 0.0f));
			SetbItemGuidCreate(true);
			break;
		case CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM:
			m_pItemGuidTexture = CJailerKeyGuidTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 0.0f));
			SetbItemGuidCreate(true);
			break;

		case CItemObject::ITEM_OBJECT_KEY_CONTOROL_ROOM:
			m_pItemGuidTexture = CControlRoomKeyGuidTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 0.0f));
			SetbItemGuidCreate(true);
			break;

		case CItemObject::ITEM_OBJECT_KEY_ELECTRICAL_ROOM:
			m_pItemGuidTexture = CElectricalRoomKeyGuidTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 0.0f));
			SetbItemGuidCreate(true);
			break;

		case CItemObject::ITEM_OBJECT_KEY_PC_ROOM:
			m_pItemGuidTexture = CPCRoomKeyGuidTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 0.0f));
			SetbItemGuidCreate(true);
			break;
		case CItemObject::ITEM_OBJECT_BATON:
			m_pItemGuidTexture = CBatonGuidTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 0.0f));
			SetbItemGuidCreate(true);
			break;
		case CItemObject::ITEM_OBJECT_MAP:
			m_pItemGuidTexture = CMapGuidTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 0.0f));
			SetbItemGuidCreate(true);
		default:
			break;
		}
	}
}

//=============================================================================
// キーボード移動処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPlayer1::InputMove(float fSpeed, float fAngle)
{
	// キーボード取得
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	CInputJoypad * pJoypad = CManager::GetJoypad();

	// パッド取得
	LPDIRECTINPUTDEVICE8 P1_PAD = CInputJoypad::GetController(PLAYER_1);

	// 移動量
	D3DXVECTOR3 move = ZeroVector3;

	// 向き取得
	D3DXVECTOR3 rot = GetRot();
	// アイテム説明テクスチャの生成状態
	bool bItemGuidCreate = GetbGuidCreate();
	if (bItemGuidCreate == false)
	{
		// 前に移動
		if (pKeyboard->GetPress(DIK_W))
		{
			// 移動量・角度の設定
			move.x = -sinf(fAngle)*fSpeed;
			move.z = -cosf(fAngle)*fSpeed;
			m_rotDest.y = fAngle;
			// 歩行モーション再生
			SetMotion(MOTION_WALK);
		}
		// 後ろに移動
		if (pKeyboard->GetPress(DIK_S))
		{
			// 移動量・角度の設定
			move.x = sinf((fAngle))*fSpeed;
			move.z = cosf((fAngle))*fSpeed;
			m_rotDest.y = fAngle - ANGLE_180;
			// 歩行モーション再生
			SetMotion(MOTION_WALK);
		}
		// 左に移動
		if (pKeyboard->GetPress(DIK_A))
		{
			// 移動量・角度の設定
			move.x = sinf(fAngle + ANGLE_90)*fSpeed;
			move.z = cosf(fAngle + ANGLE_90)*fSpeed;
			m_rotDest.y = fAngle - ANGLE_90;
			// 歩行モーション再生
			SetMotion(MOTION_WALK);
		}
		// 右に移動
		if (pKeyboard->GetPress(DIK_D))
		{
			// 移動量・角度の設定
			move.x = sinf(fAngle - ANGLE_90)*fSpeed;
			move.z = cosf(fAngle - ANGLE_90)*fSpeed;
			m_rotDest.y = fAngle + ANGLE_90;
			// 歩行モーション再生
			SetMotion(MOTION_WALK);
		}
		// 前に移動
		if (pKeyboard->GetPress(DIK_W) && pKeyboard->GetPress(DIK_A))
		{
			// 移動量・角度の設定
			move.x = -sinf(fAngle - ANGLE_45)*fSpeed;
			move.z = -cosf(fAngle - ANGLE_45)*fSpeed;
			m_rotDest.y = fAngle - ANGLE_45;
			// 歩行モーション再生
			SetMotion(MOTION_WALK);
		}
		// 前に移動
		if (pKeyboard->GetPress(DIK_W) && pKeyboard->GetPress(DIK_D))
		{
			// 移動量・角度の設定
			move.x = -sinf(fAngle + ANGLE_45)*fSpeed;
			move.z = -cosf(fAngle + ANGLE_45)*fSpeed;
			m_rotDest.y = fAngle + ANGLE_45;
			// 歩行モーション再生
			SetMotion(MOTION_WALK);
		}
		// 前に移動
		if (pKeyboard->GetPress(DIK_S) && pKeyboard->GetPress(DIK_A))
		{
			// 移動量・角度の設定
			move.x = -sinf(fAngle - ANGLE_135)*fSpeed;
			move.z = -cosf(fAngle - ANGLE_135)*fSpeed;
			m_rotDest.y = fAngle - ANGLE_135;
			// 歩行モーション再生
			SetMotion(MOTION_WALK);
		}
		// 前に移動
		if (pKeyboard->GetPress(DIK_S) && pKeyboard->GetPress(DIK_D))
		{
			// 移動量・角度の設定
			move.x = -sinf(fAngle + ANGLE_135)*fSpeed;
			move.z = -cosf(fAngle + ANGLE_135)*fSpeed;
			m_rotDest.y = fAngle + ANGLE_135;
			// 歩行モーション再生
			SetMotion(MOTION_WALK);
		}

		// !nullcheck 
		if (P1_PAD != nullptr)
		{
			// スティック取得
			DIJOYSTATE js = CInputJoypad::GetStick(PLAYER_1);
			// 入力されている場合
			if ((js.lX != ZERO_FLOAT || js.lY != ZERO_FLOAT))
			{
				// コントローラの角度
				float fAngle3 = atan2f((float)js.lX, -(float)js.lY);
				float fAngle2 = atan2f(-(float)js.lX, (float)js.lY);
				// 歩行モーション再生
				SetMotion(MOTION_WALK);
				// 移動量設定
				move.x = sinf(fAngle + (fAngle2))* fSpeed;
				move.z = cosf(fAngle + (fAngle2))* fSpeed;

				// 角度の設定
				m_rotDest.y = fAngle + (fAngle3);
			}
		}
	}
	else
	{
		if (pKeyboard->GetTrigger(DIK_RETURN) || pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_X,0))
		{

			if (m_pItemGuidTexture != nullptr)
			{
				m_pItemGuidTexture->Uninit();
				m_pItemGuidTexture = nullptr;
			}
			if (m_pGuidBG != nullptr)
			{
				m_pGuidBG->Uninit();
				m_pGuidBG = nullptr;
			}
			SetbItemGuidCreate(false);
		}
	}
	// 移動量が0の場合
	if (move == ZeroVector3)
	{
		// 待機モーション再生
		SetMotion(MOTION_IDOL);
	}
	// 移動量設定
	SetMove(move);
}

//=============================================================================
// 向き更新処理
// Author : Nikaido Taichi
//=============================================================================
void CPlayer1::UpdateRot(void)
{
	// 向き取得
	D3DXVECTOR3 rot = GetRot();

	// 向き補間
	while (m_rotDest.y - rot.y > ANGLE_180)
	{
		m_rotDest.y -= D3DXToRadian(360);
	}

	while (m_rotDest.y - rot.y < -ANGLE_180)
	{
		m_rotDest.y += D3DXToRadian(360);
	}

	// 向き
	rot += (m_rotDest - rot) * PLAYER_ROT_SPEED;

	// 向き設定
	SetRot(rot);
}