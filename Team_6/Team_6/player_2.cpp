//=============================================================================
// プレイヤー2 [player_2.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// インクルードファイル
// Author : Nikaido Taichi
//=============================================================================
#include "manager.h"
#include "game.h"
#include "player_2.h"
#include "keyboard.h"
#include "joypad.h"
#include "resource_manager.h"
#include "ui_player2_item.h"
#include "manager.h"
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

#define PRISON_POSITION (D3DXVECTOR3(-538.0f, 0.0f, -7089.0f))	//独房の位置

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CPlayer2::CPlayer2(PRIORITY Priority)
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
CPlayer2::~CPlayer2()
{
}

//=============================================================================
// 生成処理関数
// Author : Nikaido Taichi
//=============================================================================
CPlayer2 * CPlayer2::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CPlayer2のポインタ
	CPlayer2 *pPlayer2 = nullptr;

	// nullcheck
	if (pPlayer2 == nullptr)
	{
		// メモリ確保
		pPlayer2 = new CPlayer2;

		// !nullcheck
		if (pPlayer2 != nullptr)
		{
			// 初期化処理
			pPlayer2->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pPlayer2;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CPlayer2::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// タイプ設定
	SetType(PLAYER_2);

	// CXfile取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデル生成
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_PLAYER2);
	}
	// プレイヤーの初期化処理関数呼び出し
	CPlayer::Init(pos, rot);
	// プレイヤー2のUI生成
	SetUI(CPlayer2ItemUI::Create());

	//プレイヤー2の警告バー生成
	m_pCaveatBar = CCaveatBar::Create(D3DXVECTOR3(SCREEN_WIDTH - 300.0f, SCREEN_HEIGHT - 100.0f, 0), PLAYER_2);

	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPlayer2::Uninit(void)
{
	// プレイヤーの終了処理関数呼び出し
	CPlayer::Uninit();
}

//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPlayer2::Update(void)
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
	float fAngle = ((CGame*)CManager::GetModePtr())->GetCamera(1)->GetHorizontal();

	// レンダラー取得
	CRenderer *pRenderer = CManager::GetRenderer();

	// 監視カメラ使用状態取得
	bool bCameraUse = pRenderer->GetIsUseSecCamPlayer(PLAYER_2);

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
			// キーボード移動処理
			InputMove(fSpeed, fAngle);
		}
	}
	// もし行動不能状態の場合又はゴール状態の場合
	if (bIncapacitated == true || bItemGuidCreate == true || bGoal == true)
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
				m_pBlackTexture = CBlackTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT, 0.0f));
				m_bBlackTextureCreate = true;
			}
		}
	}
	// 向き補正処理
	UpdateRot();
	if (bItemGuidCreate == false && bCameraUse == false)
	{
		// アイテム削除処理関数呼び出し
		ItemDelete(PLAYER_2);
	}

	// 扉を開く処理
	DoorOpen(PLAYER_2);

	//警告バー処理
	if (m_pCaveatBar != nullptr)
	{
		m_pCaveatBar->Update();
	}

	// カメラ使用処理
	UseSecurity_Cam(PLAYER_2);

	// ダクトアイテム受け渡し
	Item_DuctPass(PLAYER_2);
}

//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPlayer2::Draw(void)
{
	// プレイヤーの描画処理関数呼び出し
	CPlayer::Draw();
}

//=============================================================================
// 独房ワープ処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPlayer2::PrisonWarp(void)
{
	// サウンドのポインタを取得する
	CSound * pSound = GET_SOUND_PTR;
	// ワープ時SEを再生する
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
void CPlayer2::SetbGuidCreate(CItemObject::ITEM_OBJECT_LIST Type)
{

	if (m_pItemGuidTexture == nullptr && m_pGuidBG == nullptr)
	{
		m_pGuidBG = CGuidBG::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 0.0f));
		switch (Type)
		{
		case CItemObject::ITEM_OBJECT_KEY_STORAGE:
			m_pItemGuidTexture = CStorageKeyGuidTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 0.0f));
			SetbItemGuidCreate(true);
			break;
		case CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM:
			m_pItemGuidTexture = CJailerKeyGuidTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 0.0f));
			SetbItemGuidCreate(true);
			break;

		case CItemObject::ITEM_OBJECT_KEY_CONTOROL_ROOM:
			m_pItemGuidTexture = CControlRoomKeyGuidTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 0.0f));
			SetbItemGuidCreate(true);
			break;

		case CItemObject::ITEM_OBJECT_KEY_ELECTRICAL_ROOM:
			m_pItemGuidTexture = CElectricalRoomKeyGuidTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 0.0f));
			SetbItemGuidCreate(true);
			break;

		case CItemObject::ITEM_OBJECT_KEY_PC_ROOM:
			m_pItemGuidTexture = CPCRoomKeyGuidTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 0.0f));
			SetbItemGuidCreate(true);
			break;
		case CItemObject::ITEM_OBJECT_BATON:
			m_pItemGuidTexture = CBatonGuidTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 0.0f));
			SetbItemGuidCreate(true);
			break;
		case CItemObject::ITEM_OBJECT_MAP:
			m_pItemGuidTexture = CMapGuidTexture::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(500.0f, 500.0f, 0.0f));
			SetbItemGuidCreate(true);
			break;
		default:
			break;
		}
	}
}

//=============================================================================
// キーボード移動処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPlayer2::InputMove(float fSpeed, float fAngle)
{
	// キーボード取得
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	CInputJoypad * pJoypad = CManager::GetJoypad();
	// パッド取得
	LPDIRECTINPUTDEVICE8 P2_PAD = CInputJoypad::GetController(PLAYER_2);
	// 移動量
	D3DXVECTOR3 move = ZeroVector3;
	// アイテム説明テクスチャの生成状態
	bool bItemGuidCreate = GetbGuidCreate();
	// 向き取得
	D3DXVECTOR3 rot = GetRot();
	if (bItemGuidCreate == false)
	{
		// 前に移動
		if (pKeyboard->GetPress(DIK_UP))
		{
			// 移動量・角度の設定
			move.x = -sinf(fAngle)*fSpeed;
			move.z = -cosf(fAngle)*fSpeed;
			m_rotDest.y = fAngle;
			// 歩行モーション再生
			SetMotion(MOTION_WALK);
		}
		// 後ろに移動
		if (pKeyboard->GetPress(DIK_DOWN))
		{
			// 移動量・角度の設定
			move.x = sinf((fAngle))*fSpeed;
			move.z = cosf((fAngle))*fSpeed;
			m_rotDest.y = fAngle - ANGLE_180;
			// 歩行モーション再生
			SetMotion(MOTION_WALK);
		}
		// 左に移動
		if (pKeyboard->GetPress(DIK_LEFT))
		{
			// 移動量・角度の設定
			move.x = sinf(fAngle + ANGLE_90)*fSpeed;
			move.z = cosf(fAngle + ANGLE_90)*fSpeed;
			m_rotDest.y = fAngle - ANGLE_90;
			// 歩行モーション再生
			SetMotion(MOTION_WALK);
		}
		// 右に移動
		if (pKeyboard->GetPress(DIK_RIGHT))
		{
			// 移動量・角度の設定
			move.x = sinf(fAngle - ANGLE_90)*fSpeed;
			move.z = cosf(fAngle - ANGLE_90)*fSpeed;
			m_rotDest.y = fAngle + ANGLE_90;
			SetMotion(MOTION_WALK);
		}
		// 前に移動
		if (pKeyboard->GetPress(DIK_UP) && pKeyboard->GetPress(DIK_LEFT))
		{
			// 移動量・角度の設定
			move.x = -sinf(fAngle - ANGLE_45)*fSpeed;
			move.z = -cosf(fAngle - ANGLE_45)*fSpeed;
			m_rotDest.y = fAngle - ANGLE_45;
			// 歩行モーション再生
			SetMotion(MOTION_WALK);
		}
		// 前に移動
		if (pKeyboard->GetPress(DIK_UP) && pKeyboard->GetPress(DIK_RIGHT))
		{
			// 移動量・角度の設定
			move.x = -sinf(fAngle + ANGLE_45)*fSpeed;
			move.z = -cosf(fAngle + ANGLE_45)*fSpeed;
			m_rotDest.y = fAngle + ANGLE_45;
			// 歩行モーション再生
			SetMotion(MOTION_WALK);
		}
		// 前に移動
		if (pKeyboard->GetPress(DIK_DOWN) && pKeyboard->GetPress(DIK_LEFT))
		{
			// 移動量・角度の設定
			move.x = -sinf(fAngle - ANGLE_135)*fSpeed;
			move.z = -cosf(fAngle - ANGLE_135)*fSpeed;
			m_rotDest.y = fAngle - ANGLE_135;
			// 歩行モーション再生
			SetMotion(MOTION_WALK);
		}
		// 前に移動
		if (pKeyboard->GetPress(DIK_DOWN) && pKeyboard->GetPress(DIK_RIGHT))
		{
			// 移動量・角度の設定
			move.x = -sinf(fAngle + ANGLE_135)*fSpeed;
			move.z = -cosf(fAngle + ANGLE_135)*fSpeed;
			m_rotDest.y = fAngle + ANGLE_135;
			// 歩行モーション再生
			SetMotion(MOTION_WALK);
		}
		// !nullcheck 
		if (P2_PAD != nullptr)
		{
			// スティック取得
			DIJOYSTATE js = CInputJoypad::GetStick(PLAYER_2);
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
		if (pKeyboard->GetTrigger(DIK_NUMPADENTER) || pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_X, 1))
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
	if (move == ZeroVector3)
	{
		// アイドルモーション再生
		SetMotion(MOTION_IDOL);
	}
	// 移動量設定
	SetMove(move);
}

//=============================================================================
// 向き更新処理
// Author : Nikaido Taichi
//=============================================================================
void CPlayer2::UpdateRot(void)
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
