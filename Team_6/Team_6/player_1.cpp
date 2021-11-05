#include "manager.h"
#include "game.h"
#include "camera.h"
#include "player_1.h"
#include "keyboard.h"
#include "joypad.h"
#include "resource_manager.h"

CPlayer1::CPlayer1(PRIORITY Priority)
{
	m_rotDest = ZeroVector3;
}

CPlayer1::~CPlayer1()
{
}

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

HRESULT CPlayer1::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
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
	// スピード設定
	SetSpeed(PLAYER_SPEED);
	return S_OK;
}

void CPlayer1::Uninit(void)
{
	// プレイヤーの終了処理関数呼び出し
	CPlayer::Uninit();
}

void CPlayer1::Update(void)
{
	// プレイヤーの更新処理関数呼び出し
	CPlayer::Update();
	//行動不能状態取得
	bool bIncapacitated = GetbIncapacitated();
	// スピード取得
	float fSpeed = GetSpeed();
	// カメラ角度取得
	float fAngle = GET_CAMERA_PTR->GetHorizontal();
	// もし行動可能状態の場合
	if (bIncapacitated == false)
	{
		// キーボード移動処理
		KeyboardMove(fSpeed, fAngle);
		// パッド移動
		PadMove(fSpeed, fAngle);
	}
	else
	{
		SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	// マップとの当たり判定
	MapCollision();
}

void CPlayer1::Draw(void)
{
	// プレイヤーの描画処理関数呼び出し
	CPlayer::Draw();
}

void CPlayer1::KeyboardMove(float fSpeed, float fAngle)
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
	if (pKeyboard->GetPress(DIK_W) && pKeyboard->GetPress(DIK_A))
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
void CPlayer1::PadMove(float fSpeed, float fAngle)
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
// 向き更新処理
// Author : Sugawara Tsukasa
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