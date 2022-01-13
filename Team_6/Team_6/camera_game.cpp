//=============================================================================
//
// カメラの処理 [camera.cpp]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "camera_game.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "player.h"
#include "joypad.h"
#include "motion.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define DISTANCE					(2200.0f)						// 視点～注視点の距離
#define DISTANCE_FAR_UP				(35.0f)							// カメラを引く値
#define FAR_DISTANCE				(3000.0f)						// 遠めのカメラ
#define PLAYER_HEIGHT				(600.0f)						// 注視点の高さ
#define CAMERA_MIN_Fφ				(D3DXToRadian(10.0f))			// カメラの最小角
#define CAMERA_MAX_Fφ				(D3DXToRadian(170.0f))			// カメラの最大角
#define CAMERA_MIN_HIGHT			(2.0f)							// カメラの最低高度
#define STICK_SENSITIVITY			(100.0f)						// スティック感度
#define STICK_INPUT_CONVERSION		(D3DXToRadian(2.0f))			// スティック入力変化量
#define HEIGHT_DIVIDE				(1.5f)							// 高さ÷
#define MOVE_FRAME					(30.0f)							// カメラ回転のフレーム数

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
float CCameraGame::m_fSecCamAngle = 0.0f;
D3DXVECTOR3 CCameraGame::m_fSecCamPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
CCameraSecurity *CCameraGame::m_pSecCam = nullptr;

//=============================================================================
// インスタンス生成
//=============================================================================
CCameraGame * CCameraGame::Create(CCamera::SCREEN_ID id)
{
	// メモリ確保
	CCameraGame *pCamera = new CCameraGame;

	// 初期化処理
	pCamera->Init();

	pCamera->SetCameraID(id);
	pCamera->SetScreenID(id);

	return pCamera;
}

//=============================================================================
// カメラID設定
//=============================================================================
void CCameraGame::SetCameraID(CCamera::SCREEN_ID id)
{
	SetScreenID(id);
}

//=============================================================================
// コンストラクタ
//=============================================================================
CCameraGame::CCameraGame()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CCameraGame::~CCameraGame()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCameraGame::Init(void)
{
	// 初期化処理
	CCamera::Init();
	SetScreenID(CCamera::SCREEN_NONE);
	SetTarget(true);
	m_bIsRotate = false;
	m_fAngleMove = 0.0f;
	m_camAngle = ANGLE_FRONT;
	m_fDestHorizontal = 0.0f;
	m_fHorizontal = 0.0f;

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CCameraGame::Update(void)
{
	//キーボードクラス情報の取得
	CInputKeyboard *pKeyInput = CManager::GetKeyboard();

	CCamera::SCREEN_ID id = GetScreenID();
	bool bUse = CManager::GetRenderer()->GetIsUseSecCamPlayer(id - 1);


	// 監視カメラを使っているなら
	if (bUse)
	{
		// 座標補間しない
		SetIsInterpolation(false);

		// 入力によってカメラを順送り・逆送り
		if (pKeyInput->GetTrigger(DIK_1))
		{
			m_pSecCam = m_pSecCam->GetPrev();
		}
		if (pKeyInput->GetTrigger(DIK_2))
		{
			m_pSecCam = m_pSecCam->GetNext();
		}

		m_fSecCamAngle = m_pSecCam->GetAngle();
		m_fSecCamPos = m_pSecCam->GetPos();

		// 注視点を変更
		SetScreenID(id);
		SetTargetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		SetCameraPos(m_fSecCamPos);
		SetVartical(D3DXToRadian(110));
		SetHorizontal(m_fSecCamAngle);
	}
	else
	{
		SetScreenID(id);
		SetIsInterpolation(true);
		SetVartical(CAMERA_DEFAULT_Fθ);
		CameraRotate();
	}

	CCamera::Update();
	CCamera::SetCamera();
}

//=============================================================================
// カメラ回転処理
//=============================================================================
void CCameraGame::CameraRotate(void)
{
	//キーボードクラス情報の取得
	CInputKeyboard *pKeyInput = CManager::GetKeyboard();
	// ジョイパッドの取得
	DIJOYSTATE js = CInputJoypad::GetStick(0);
	CCamera::SCREEN_ID id = GetScreenID();

	m_fHorizontal = GetHorizontal();

	if (m_bIsRotate)
	{
		m_fHorizontal += m_fAngleMove;

		if (m_fDestHorizontal + D3DXToRadian(1) > m_fHorizontal &&
			m_fDestHorizontal - D3DXToRadian(1) < m_fHorizontal)
		{
			m_bIsRotate = false;
		}
		SetHorizontal(m_fHorizontal);
	}
	else if(!CManager::GetRenderer()->GetIsUseSecCamPlayer(id - 1))
	{
		if (id == SCREEN_LEFT)
		{
			if (pKeyInput->GetTrigger(DIK_Q))
			{
				m_fDestHorizontal = m_fHorizontal - D3DXToRadian(90);
				m_fAngleMove = (m_fDestHorizontal - m_fHorizontal) / MOVE_FRAME;
				m_bIsRotate = true;
				m_camAngle++;
				if (m_camAngle > ANGLE_LEFT)
				{
					m_camAngle = ANGLE_FRONT;
				}
			}
			if (pKeyInput->GetTrigger(DIK_E))
			{
				m_fDestHorizontal = m_fHorizontal + D3DXToRadian(90);
				m_fAngleMove = (m_fDestHorizontal - m_fHorizontal) / MOVE_FRAME;
				m_bIsRotate = true;
				m_camAngle--;
				if (m_camAngle < ANGLE_FRONT)
				{
					m_camAngle = ANGLE_LEFT;
				}
			}
		}
		else
		{
			if (pKeyInput->GetTrigger(DIK_RSHIFT))
			{
				m_fDestHorizontal = m_fHorizontal - D3DXToRadian(90);
				m_fAngleMove = (m_fDestHorizontal - m_fHorizontal) / MOVE_FRAME;
				m_bIsRotate = true;
				m_camAngle++;
				if (m_camAngle > ANGLE_LEFT)
				{
					m_camAngle = ANGLE_FRONT;
				}
			}
			if (pKeyInput->GetTrigger(DIK_NUMPAD1))
			{
				m_fDestHorizontal = m_fHorizontal + D3DXToRadian(90);
				m_fAngleMove = (m_fDestHorizontal - m_fHorizontal) / MOVE_FRAME;
				m_bIsRotate = true;
				m_camAngle--;
				if (m_camAngle < ANGLE_FRONT)
				{
					m_camAngle = ANGLE_LEFT;
				}
			}
		}

		SetHorizontal(m_fHorizontal);
	}
}

//=============================================================================
// 監視カメラとの切り替え処理
//=============================================================================
void CCameraGame::SwitchCam(CGame::CAMERA_ID CamId, bool bSecCam)
{
	CCamera::SCREEN_ID id = GetScreenID();

	if (!bSecCam && CamId == id - 1)
	{
		m_fHorizontal =  D3DXToRadian(m_camAngle * 90);
		SetHorizontal(m_fHorizontal);
	}
}

//=============================================================================
// 通常状態の更新処理
//=============================================================================
void CCameraGame::NomalUpdate(D3DXVECTOR3 PlayerPos, D3DXVECTOR3 PlayerRot)
{
	//キーボードクラス情報の取得
	CInputKeyboard *pKeyInput = CManager::GetKeyboard();

	// ジョイパッドの取得
	DIJOYSTATE js = CInputJoypad::GetStick(0);

	// 角度の取得
	float fAngle3 = atan2f((float)js.lX, -(float)js.lY);	// コントローラの角度
	float fAngle2 = atan2f(-(float)js.lX, (float)js.lY);	// コントローラの角度

															// カメラ座標
	D3DXVECTOR3 VDest = ZeroVector3;

	// 前回の向き取得
	D3DXVECTOR3 posRDest = GetposRDest();

	// 距離取得
	float fDistance = GetDistance();

	// 左右旋回角度取得
	float fHorizontal = GetHorizontal();

	// 上下旋回角度取得
	float fVartical = GetVartical();

	//視点（カメラ座標）の左旋回
	if (pKeyInput->GetPress(DIK_LEFT) || js.lZ > STICK_SENSITIVITY)
	{
		// 加算
		fHorizontal += STICK_INPUT_CONVERSION;
	}
	//視点（カメラ座標）の右旋回
	if (pKeyInput->GetPress(DIK_RIGHT) || js.lZ < -STICK_SENSITIVITY)
	{
		// 減算
		fHorizontal -= STICK_INPUT_CONVERSION;
	}
	//視点（カメラ座標）の上旋回
	if (pKeyInput->GetPress(DIK_UP) || js.lRz > STICK_SENSITIVITY && fVartical >= CAMERA_MIN_Fφ)
	{
		// 減算
		fVartical -= STICK_INPUT_CONVERSION;
	}
	//視点（カメラ座標）の下旋回
	if (pKeyInput->GetPress(DIK_DOWN) || js.lRz < -STICK_SENSITIVITY && fVartical <= CAMERA_MAX_Fφ)
	{
		// 加算
		fVartical += STICK_INPUT_CONVERSION;
	}

	// カメラの位置設定
	VDest.x = PlayerPos.x + fDistance * sinf(fVartical) * sinf(fHorizontal);	// カメラ位置X設定
	VDest.y = PlayerPos.y + PLAYER_HEIGHT + fDistance * cosf(fVartical);		// カメラ位置Y設定
	VDest.z = PlayerPos.z + fDistance * sinf(fVartical) * cosf(fHorizontal);	// カメラ位置Z設定

	posRDest = D3DXVECTOR3(PlayerPos.x, PlayerPos.y + PLAYER_HEIGHT, PlayerPos.z);	//注視点設定

																					//カメラPOSYの下限
	if (VDest.y <= CAMERA_MIN_HIGHT)
	{
		VDest.y = CAMERA_MIN_HIGHT;	//限界値に戻す
	}

	//設定値の反映
	GetposV() += (VDest - GetposV())*0.1f;
	GetposR() += (posRDest - GetposR())*0.9f;

	// 旋回角度設定
	SetHorizontal(fHorizontal);
	SetVartical(fVartical);
}

//=============================================================================
// カメラの位置修正
//=============================================================================
void CCameraGame::ModifyCamera(CGame::CAMERA_ID id)
{
	// プレイヤーのポインタ
	CPlayer *pPlayer;
	CModeBase *pMode = CManager::GetModePtr();

	// 位置修正
	pPlayer = ((CGame*)pMode)->GetPlayer(id);
	SetTargetPos(pPlayer->GetPos());
	CCamera::Update();
	CCamera::SetCamera();
}

//=============================================================================
// カメラの位置修正
//=============================================================================
void CCameraGame::ModifySecCamera(void)
{
	// プレイヤーのポインタ
	SetTargetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetCameraPos(m_fSecCamPos);
	SetVartical(D3DXToRadian(110));
	SetHorizontal(m_fSecCamAngle);
	CCamera::Update();
	CCamera::SetCamera();
}

//=============================================================================
// 監視カメラの生成
//=============================================================================
void CCameraGame::CreateSecCam(D3DXVECTOR3 pos, float fDir)
{
	m_pSecCam = CCameraSecurity::Create(pos, fDir);
}