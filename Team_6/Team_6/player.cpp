//=============================================================================
// プレイヤー [player.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "player.h"
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "input.h"
#include "joypad.h"
#include "camera.h"
#include "game.h"
#include "sound.h"
#include "time.h"
#include "collision.h"
#include "fade.h"
#include "texture.h"
#include "resource_manager.h"
#include "motion.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define PLAYER_SPEED			(50.0f)									// プレイヤーの移動量
#define STICK_SENSITIVITY		(50.0f)									// スティック感度
#define PLAYER_ROT_SPEED		(0.1f)									// キャラクターの回転する速度
#define SIZE					(D3DXVECTOR3 (1200.0f,1000.0f,1200.0f))	// サイズ
#define STICK_INPUT_ZONE		(100)									// スティックの入力範囲
#define STICK_INPUT_ZONE_2		(1000)									// スティックの入力範囲
#define STICK_INPUT_ZERO		(0)										// スティックの入力値0
#define MIN_LIFE				(0)										// ライフの最小
#define LIFE					(100)									// ライフ
#define ANGLE_45				(D3DXToRadian(45.0f))					// 角度45
#define ANGLE_90				(D3DXToRadian(90.0f))					// 角度90
#define ANGLE_135				(D3DXToRadian(135.0f))					// 角度90
#define ANGLE_180				(D3DXToRadian(180.0f))					// 角度180
#define ANGLE_270				(D3DXToRadian(270.0f))					// 角度270

//=============================================================================
// 生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer *pPlayer = new CPlayer;

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// 初期化処理
		pPlayer->Init(pos, rot);
	}

	// CPlayerを返す
	return pPlayer;
}

//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer::CPlayer(PRIORITY Priority) : CCharacter(Priority)
{
	m_rotDest = ZeroVector3;
}

//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CXfile取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// モデル生成
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_PLAYER);
	}

	// 初期化処理
	CCharacter::Init(pos, rot);

	// 向き
	m_rotDest = rot;

	// サイズ設定
	SetSize(SIZE);

	// ライフ設定
	SetLife(LIFE);

	// スピード設定
	SetSpeed(PLAYER_SPEED);

	// 影
	SetUseShadow();

	// 影の向き
	SetShadowRotCalculation();

	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::Uninit(void)
{
	CCharacter::Uninit();
}

//=============================================================================
// 更新関数処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::Update(void)
{
	// 更新
	CCharacter::Update();

	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// 古い位置設定
	SetPosOld(pos);

	// プレイヤーの処理
	PlayerControl();
}

//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::Draw(void)
{
	// 描画
	CCharacter::Draw();
}

//=============================================================================
// 状態更新
// Author: Sugawara Tsukasa
//=============================================================================
void CPlayer::UpdateState(void)
{

}

//=============================================================================
// プレイヤーの処理
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::PlayerControl()
{
	// 移動処理
	Move();

	// 角度の更新処理
	UpdateRot();
}

//=============================================================================
// 向き更新処理
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::UpdateRot(void)
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

//=============================================================================
// ヒット処理関数
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::Hit(int nDamage)
{
}

//=============================================================================
// 死亡処理
// Author : Konishi Yuuto
//=============================================================================
void CPlayer::Death(void)
{
}

//=============================================================================
// 移動処理
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::Move(void)
{	
	// スピード取得
	float fSpeed = GetSpeed();

	// カメラ角度取得
	float fAngle = GET_CAMERA_PTR->GetHorizontal();

	// キーボード移動処理
	KeyboardMove(fSpeed, fAngle);

	// パッド移動
	PadMove(fSpeed, fAngle);
}
//=============================================================================
// キーボード移動処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::KeyboardMove(float fSpeed, float fAngle)
{
	// キーボード取得
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// 移動量
	D3DXVECTOR3 move = ZeroVector3;

	// 向き取得
	D3DXVECTOR3 rot = GetRot();

	// 前に移動
	if (pKeyboard->GetPress(DIK_W))
	{
		// 移動量・角度の設定
		move.x = -sinf(fAngle)*fSpeed;
		move.z = -cosf(fAngle)*fSpeed;
		m_rotDest.y = fAngle;
	}
	// 後ろに移動
	if (pKeyboard->GetPress(DIK_S))
	{
		// 移動量・角度の設定
		move.x = sinf((fAngle))*fSpeed;
		move.z = cosf((fAngle))*fSpeed;
		m_rotDest.y = fAngle - ANGLE_180;
	}
	// 左に移動
	if (pKeyboard->GetPress(DIK_A))
	{
		// 移動量・角度の設定
		move.x = sinf(fAngle + ANGLE_90)*fSpeed;
		move.z = cosf(fAngle + ANGLE_90)*fSpeed;
		m_rotDest.y = fAngle - ANGLE_90;
	}
	// 右に移動
	if (pKeyboard->GetPress(DIK_D))
	{
		// 移動量・角度の設定
		move.x = sinf(fAngle - ANGLE_90)*fSpeed;
		move.z = cosf(fAngle - ANGLE_90)*fSpeed;
		m_rotDest.y = fAngle + ANGLE_90;
	}
	// 前に移動
	if (pKeyboard->GetPress(DIK_W)&& pKeyboard->GetPress(DIK_A))
	{
		// 移動量・角度の設定
		move.x = -sinf(fAngle - ANGLE_45)*fSpeed;
		move.z = -cosf(fAngle - ANGLE_45)*fSpeed;
		m_rotDest.y = fAngle - ANGLE_45;
	}
	// 前に移動
	if (pKeyboard->GetPress(DIK_W) && pKeyboard->GetPress(DIK_D))
	{
		// 移動量・角度の設定
		move.x = -sinf(fAngle + ANGLE_45)*fSpeed;
		move.z = -cosf(fAngle + ANGLE_45)*fSpeed;
		m_rotDest.y = fAngle + ANGLE_45;
	}
	// 前に移動
	if (pKeyboard->GetPress(DIK_S) && pKeyboard->GetPress(DIK_A))
	{
		// 移動量・角度の設定
		move.x = -sinf(fAngle - ANGLE_135)*fSpeed;
		move.z = -cosf(fAngle - ANGLE_135)*fSpeed;
		m_rotDest.y = fAngle - ANGLE_135;
	}
	// 前に移動
	if (pKeyboard->GetPress(DIK_S) && pKeyboard->GetPress(DIK_D))
	{
		// 移動量・角度の設定
		move.x = -sinf(fAngle + ANGLE_135)*fSpeed;
		move.z = -cosf(fAngle + ANGLE_135)*fSpeed;
		m_rotDest.y = fAngle + ANGLE_135;
	}
	// 移動量設定
	SetMove(move);
}
//=============================================================================
// パッド移動処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::PadMove(float fSpeed, float fAngle)
{
	// パッド取得
	LPDIRECTINPUTDEVICE8 P1_PAD = CInputJoypad::GetController(0);

	// !nullcheck 
	if (P1_PAD != nullptr)
	{
		// スティック取得
		DIJOYSTATE js = CInputJoypad::GetStick(0);

		// 移動量
		D3DXVECTOR3 move = ZeroVector3;

		// 入力されている場合
		if ((js.lX != ZERO_FLOAT || js.lY != ZERO_FLOAT))
		{
			// コントローラの角度
			float fAngle3 = atan2f((float)js.lX, -(float)js.lY);
			float fAngle2 = atan2f(-(float)js.lX, (float)js.lY);

			// 移動量設定
			move.x = sinf(fAngle + (fAngle2))* fSpeed;
			move.z = cosf(fAngle + (fAngle2))* fSpeed;

			// 角度の設定
			m_rotDest.y = fAngle + (fAngle3);
		}
		else
		{
			// 移動量0
			move = ZeroVector3;
		}

		// 移動量設定
		SetMove(move);
	}
}
//=============================================================================
// 攻撃処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::Attack(void)
{
}
