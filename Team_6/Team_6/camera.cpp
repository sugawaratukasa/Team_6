//=============================================================================
//
// カメラの処理 [camera.cpp]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "camera.h"
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
#define PLAYER_HEIGHT				(600.0f)						// 注視点の高さ

//=============================================================================
// コンストラクタ
//=============================================================================
CCamera::CCamera()
{
	//各メンバ変数のクリア
	m_posV = ZeroVector3;
	m_posVDest = ZeroVector3;
	m_posR = ZeroVector3;
	m_posRDest = ZeroVector3;
	m_posU = ZeroVector3;
	m_rot = ZeroVector3;
	m_fDistance = 0.0f;
	m_fMove = 0.0f;
	m_id = SCREEN_NONE;
	m_bInterpolation = true;
}

//=============================================================================
// デストラクタ
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCamera::Init(void)
{
	m_fMove = 5.0f;
	m_fDistance = DISTANCE;
	m_fVartical = CAMERA_DEFAULT_Fθ;
	m_fHorizontal = D3DXToRadian(0.0f);											// 初期値敵のほう向ける
	m_posR = D3DXVECTOR3(0.0f, PLAYER_HEIGHT, 0.0f);							// 注視点設定
	m_posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);										// 上方向ベクトル
	m_posV.x = m_posR.x + m_fDistance * sinf(m_fVartical) * sinf(m_fHorizontal);// カメラ位置X
	m_posV.y = m_posR.z + m_fDistance * cosf(m_fVartical);						// カメラ位置Y
	m_posV.z = m_posR.y + m_fDistance * sinf(m_fVartical) * cosf(m_fHorizontal);// カメラ位置Z
	m_id = SCREEN_NONE;															// スクリーンIDの初期化
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void CCamera::Update(void)
{
	bool bUse = CManager::GetRenderer()->GetIsUseSecCam();

	// 監視カメラを使っているなら
	if (bUse)
	{
		m_posRDest.x = m_fDistance * sinf(m_fVartical) * sinf(m_fHorizontal);// カメラ位置X
		m_posRDest.y = m_fDistance * cosf(m_fVartical);						 // カメラ位置Y
		m_posRDest.z = m_fDistance * sinf(m_fVartical) * cosf(m_fHorizontal);// カメラ位置Z

		if (m_bTarget)
		{
			m_posRDest += m_posVDest;
		}
	}
	else
	{
		m_posVDest.x = m_fDistance * sinf(m_fVartical) * sinf(m_fHorizontal);// カメラ位置X
		m_posVDest.y = m_fDistance * cosf(m_fVartical);						 // カメラ位置Y
		m_posVDest.z = m_fDistance * sinf(m_fVartical) * cosf(m_fHorizontal);// カメラ位置Z

		if (m_bTarget)
		{
			m_posVDest += m_posRDest;
		}
	}

    // カメラの位置と注視点を更新
	if (m_bInterpolation)
	{
		m_posR += (m_posRDest - m_posR) * CAMERA_MOVE_RATE;
		m_posV += (m_posVDest - m_posV) * CAMERA_MOVE_RATE;
	}
	else
	{
		m_posR += (m_posRDest - m_posR);
		m_posV += (m_posVDest - m_posV);
	}
}

//=============================================================================
//カメラクラスのセット処理
//=============================================================================
void CCamera::SetCamera(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();


	//スクリーンID別にプロジェクションマトリックスの作成
	if (m_id == SCREEN_NONE)
	{
		//ビューマトリックスの初期化
		D3DXMatrixIdentity(&m_mtxView);


		//ビューマトリックスの作成
		D3DXMatrixLookAtLH(&m_mtxView,
			&m_posV,
			&m_posR,
			&m_posU);


		//ビューマトリックスの設定
		pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);


		//プロジェクションマトリックスの初期化
		D3DXMatrixIdentity(&m_mtxProjection);


		D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
			D3DXToRadian(45.0f),
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
			10.0f,
			200000.0f);


		//プロジェクションマトリックスの設定
		pDevice->SetTransform(D3DTS_PROJECTION,
			&m_mtxProjection);
	}
	else
	{
		//ビューマトリックスの初期化
		D3DXMatrixIdentity(&m_aMtxView[m_id]);

		//ビューマトリックスの作成
		D3DXMatrixLookAtLH(&m_aMtxView[m_id],
			&m_posV,
			&m_posR,
			&m_posU);

		//ビューマトリックスの設定
		pDevice->SetTransform(D3DTS_VIEW, &m_aMtxView[m_id]);

		//プロジェクションマトリックスの初期化
		D3DXMatrixIdentity(&m_aMtxProjection[m_id]);

		D3DXMatrixPerspectiveFovLH(&m_aMtxProjection[m_id],
			D3DXToRadian(45.0f),
			(float)(SCREEN_WIDTH / 2 )/ (float)SCREEN_HEIGHT,
			10.0f,
			200000.0f);

		//プロジェクションマトリックスの設定
		pDevice->SetTransform(D3DTS_PROJECTION,
			&m_aMtxProjection[m_id]);
	}
}