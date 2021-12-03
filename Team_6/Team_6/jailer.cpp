//=============================================================================
//
// 看守クラス [jailer.cpp]
// Author : Yamada Ryota
//
//=============================================================================
#include "jailer.h"
#include "manager.h"
#include "resource_manager.h"
#include "xfile.h"
#include "debug_proc.h"
#include "keyboard.h"
#include "player.h"
#include "jailer_State.h"
#include "fan3d.h"
#include "mode_base.h"
#include "collision.h"
#include "character_collision_box.h"
#include "jailer_spot.h"
#include "Jalier_MoveState.h"
#include "Jalier_MoveState.h"
#include "object.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define JAILER_NORMAL_SPEED (10.0f)	//通常時の移動速度
#define JAILER_CHASE_SPEED (20.0f)	//追跡時の移動速度
#define JAILER_ROTSTION_RATE (0.1f)	//回転の係数
#define VIEW_POS_Y (70.0f)			//視線の高さ
#define VIEW_POLYGON_NUM (8)		//視線のポリゴン数
#define JAILER_SIZE (D3DXVECTOR3 (100.0f,200.0f,100.0f))	// サイズ
#define GUARD_ROT_ANGLE D3DXToRadian(45)
#define TURN_SPEED (10.0f)
//=============================================================================
//静的メンバ変数宣言
//=============================================================================
int CJailer::m_nJailerTotal = -1;

//=============================================================================
//コンストラクタ
//=============================================================================
CJailer::CJailer()
{
	m_pView = nullptr;				//看守の視線クラスのポインタ変数
	m_pJailerState = nullptr;		//状態のポインタ
	m_pSpot = nullptr;
	m_rotDest = ZeroVector3;		//向きの目的地
	m_posDest = ZeroVector3;		//位置の目的地
	m_posDestOld = ZeroVector3;		//前回の位置の目的地
	m_distance = ZeroVector3;		//目的地までの距離
	m_GuardBaseDir = ZeroVector3;	//警戒時の基準の方向
	m_nSwitchingTime = ZERO_INT;	//状態の切り替えタイマー
	m_nNumber = ZERO_INT;			//自分の番号	
	m_fDestLength = ZERO_FLOAT;		//目的地と自分の距離の長さ
	m_TurnSpeed = ZERO_FLOAT;

	//総数の加算
	m_nJailerTotal++;
}

//=============================================================================
//デストラクタ
//=============================================================================
CJailer::~CJailer()
{
	//総数の減算
	m_nJailerTotal--;
}

//=============================================================================
//クリエイト処理
//=============================================================================
CJailer * CJailer::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CJailer *pJailer = nullptr;

	//インスタンス生成
	pJailer = new CJailer;

	if (pJailer != nullptr)
	{
		//初期化処理
		pJailer->Init(pos, rot);

		return pJailer;
	}
	
	return nullptr;
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CJailer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//Xファイルクラスの取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	if (pXfile != nullptr)
	{
		//看守モデルのクリエイト
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_JAILER);
	}

	//キャラクターの初期化処理
	CCharacter::Init(pos, rot);

	//アイドルモーション再生
	SetMotion(JAILER_MOTION_IDOL);

	//速さの設定
	SetSpeed(0.0f);

	SetUseShadow();

	// 影の向き
	SetShadowRotCalculation();

	//自分の番号を設定
	m_nNumber = m_nJailerTotal;

	//スポットクラスのクリエイト
	m_pSpot = CJailerSpot::Create(m_nNumber);

	//位置の設定
	SetPos(m_pSpot->GetSpotDest());

	//目的地を設定
	m_posDest = m_pSpot->ChangePatrolSpot();

	//視界のクリエイト
	m_pView = CJailerView::Create(D3DXVECTOR3(m_posDest.x, VIEW_POS_Y, m_posDest.z), 
		ZeroVector3, VIEW_POLYGON_NUM, D3DCOLOR_RGBA(255, 0, 0, 255));

	//状態設定
	m_pJailerState = CMoveState::GetInstance();

	//サイズの設定
	SetSize(JAILER_SIZE);

	m_TurnSpeed = TURN_SPEED;
	CCharacterCollisionBox::Create(GetPos(), GetRot(), this);

	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CJailer::Uninit(void)
{
	//キャラクターの終了処理
	CCharacter::Uninit();
}

//=============================================================================
//更新処理
//=============================================================================
void CJailer::Update(void)
{
	//位置の取得
	D3DXVECTOR3 pos = GetPos();

	//前回位置の設定
	SetPosOld(pos);

	//キャラクターの更新処理
	CCharacter::Update();

	//アニメーションの更新
	ModelAnimeUpdate();

	//回転処理
	Rotation();

	CheckMapCollision();

	m_pSpot->Update();
	//状態処理の更新
	if (m_pJailerState != nullptr)
	{
		m_pJailerState->Update(this, m_pView);
	}
	
	if (m_pView)
	{
		m_pView->SetRotation(GetRot());									//扇の向きの設定
		m_pView->SetPosition(D3DXVECTOR3(pos.x, VIEW_POS_Y, pos.z));	//扇の位置の設定
	}
}

//=============================================================================
//描画処理
//=============================================================================
void CJailer::Draw(void)
{
	//キャラクターの描画処理
	CCharacter::Draw();
}

//=============================================================================
//回転関数
//=============================================================================
void CJailer::Rotation(void)
{
	//向きを取得
	D3DXVECTOR3 rot = GetRot();

	// 向き補間
	while ((m_rotDest.y - rot.y) > D3DXToRadian(180.0f))
	{
		m_rotDest.y -= D3DXToRadian(360.0f);
	}

	while ((m_rotDest.y - rot.y) < -D3DXToRadian(180.0f))
	{
		m_rotDest.y += D3DXToRadian(360.0f);
	}

	rot += (m_rotDest - rot) * JAILER_ROTSTION_RATE;

	if (rot.y > D3DXToRadian(360.0f))
	{
		rot.y = D3DXToRadian(0.0f);
	}
	if (rot.y < D3DXToRadian(0.0f))
	{
		rot.y = D3DXToRadian(360.0f);
	}

	//向き設定
	SetRot(rot);
}

//=============================================================================
// 状態切り替え関数
//=============================================================================
void CJailer::ChangeState(CJailerState * jailerstate)
{
	m_pJailerState = jailerstate;
	m_pJailerState->Init(this, m_pView);
}

//=============================================================================
//移動処理
//=============================================================================
void CJailer::Patrol(void)
{
	D3DXVECTOR3 move = ZeroVector3;

	//単位ベクトル
	D3DXVECTOR3 nor = ZeroVector3;

	//現在地と目的地までのベクトルを計算
	m_distance = m_posDest - GetPos();

	//目的地と自分の距離の長さを計算
	m_fDestLength = sqrtf((m_distance.x * m_distance.x) + (m_distance.z * m_distance.z));

	//向きの目的の値の計算
	ChangeRotDest();

	//アイドルモーション再生
	SetMotion(JAILER_MOTION::JAILER_MOTION_MOVE);

	//速さの設定
	SetSpeed(JAILER_NORMAL_SPEED);

	//移動方向のベクトルの正規化
	D3DXVec3Normalize(&nor, &m_distance);

	//移動量を設定
	move.x = nor.x * GetSpeed();
	move.z = nor.z * GetSpeed();

	//移動量の設定
	SetMove(move);

	if (m_fDestLength <= 5.0f)
	{
		//目的地の再設定
		ChangePosDest();
	}
}

//=============================================================================
// 巡回ルートへ戻る
//=============================================================================
void CJailer::RetrunRoute(void)
{
	D3DXVECTOR3 move = ZeroVector3;

	//単位ベクトル
	D3DXVECTOR3 nor = ZeroVector3;

	//現在位置と検出した位置までのベクトルを計算
	m_distance = (m_posDest - GetPos());

	//目的地と自分の距離を計算
	m_fDestLength = sqrtf((m_distance.x * m_distance.x) + (m_distance.z * m_distance.z));

	if (m_fDestLength > 5.0f)
	{
		//ステートを移動に変更
		ChangeState(CMoveState::GetInstance());

		return;
	}

	//アイドルモーション再生
	SetMotion(JAILER_MOTION::JAILER_MOTION_MOVE);

	//速さの設定
	SetSpeed(JAILER_NORMAL_SPEED);

	//移動方向のベクトルの正規化
	D3DXVec3Normalize(&nor, &m_distance);

	//移動量を設定
	move.x = nor.x * GetSpeed();
	move.z = nor.z * GetSpeed();

	//移動量の設定
	SetMove(move);
}

//=============================================================================
// 追跡
//=============================================================================
void CJailer::ChasePlayer()
{
	D3DXVECTOR3 move = ZeroVector3;
	//単位ベクトル
	D3DXVECTOR3 nor = ZeroVector3;

	//検出した位置
	D3DXVECTOR3 detectedPos = ZeroVector3;
	
	if (m_pView)
	{
		//検出した位置の取得
		detectedPos = m_pView->GetDetectionPos();
		m_pView->JailerCaution(true);
	}

	//現在位置と検出した位置までのベクトルを計算
	m_distance = (detectedPos - GetPos());

	//目的地と自分の距離を計算
	m_fDestLength = sqrtf((m_distance.x * m_distance.x) + (m_distance.z * m_distance.z));

	if (m_fDestLength > 5.0f)
	{
		//向きの目的の値の計算
		ChangeRotDest();

		//アイドルモーション再生
		SetMotion(JAILER_MOTION::JAILER_MOTION_MOVE);

		//速さの設定
		SetSpeed(JAILER_CHASE_SPEED);

		//移動方向のベクトルの正規化
		D3DXVec3Normalize(&nor, &m_distance);

		//移動量を設定
		move.x = nor.x * GetSpeed();
		move.z = nor.z * GetSpeed();

		//ルートの検索
		m_posDest = m_pSpot->SearchRoute(GetPos(), detectedPos);
	}

	//移動量の設定
	SetMove(move);
}

//=============================================================================
// 警戒状態
//=============================================================================
void CJailer::GuardSurrounding(void)
{
	//アイドルモーション再生
	SetMotion(JAILER_MOTION::JAILER_MOTION_IDOL);

	//向きを取得
	D3DXVECTOR3 rot = GetRot();

	if (m_nSwitchingTime % 120 == 0)
	{
		m_rotDest.y = m_GuardBaseDir.y + GUARD_ROT_ANGLE;
	}
	else if (m_nSwitchingTime % 60 == 0)
	{
		m_rotDest.y = m_GuardBaseDir.y - GUARD_ROT_ANGLE;
	}
}

//=============================================================================
//攻撃処理
//=============================================================================
void CJailer::Attack(void)
{
}

//=============================================================================
// 秒数加算
//=============================================================================
int CJailer::AddTime(int add)
{
	m_nSwitchingTime += add;
	return m_nSwitchingTime;
}

//=============================================================================
// 目的地の設定
//=============================================================================
void CJailer::ChangePosDest(void)
{
	//目的地の更新
	m_posDest = m_pSpot->ChangePatrolSpot();
}

//=============================================================================
// 向きの目的の値の設定
//=============================================================================
void CJailer::ChangeRotDest(void)
{
	D3DXVECTOR3	nor = ZeroVector3;

	//移動方向のベクトルの正規化
	D3DXVec3Normalize(&nor, &m_distance);

	//移動方向に対しての回転角を求める
	float fAngle = atan2f(-nor.x, -nor.z);

	//目的の角度へ設定
	m_rotDest.y = fAngle;
}

//=============================================================================
// プレイヤーとの当たり判定
//=============================================================================
bool CJailer::IsHitPlayer(void)
{
	//位置の取得
	D3DXVECTOR3 pos = GetPos();

	//前回位置の取得
	D3DXVECTOR3 posOld = GetOldPos();

	//サイズの取得
	D3DXVECTOR3 size = GetSize();
	
	bool bIsHit = false;	//当たったかどうかのフラグ

	for (int nCntPlayer = ZERO_INT; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		//プレイヤーのポインタを取得
		CPlayer *pPlayer = CManager::GetModePtr()->GetPlayer(nCntPlayer);

		//プレイヤーの位置の取得
		D3DXVECTOR3 playerPos = pPlayer->GetPos();

		//プレイヤーのサイズの取得
		D3DXVECTOR3 playerSize = pPlayer->GetSize();

		//プレイヤーとの判定
		int nHitSurface = CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, playerPos, size, playerSize);

		//左
		if (nHitSurface == CCollision::SURFACE_LEFT)
		{
			pos.x = ((-playerSize.x / 2) + playerPos.x) - (size.x / 2);

			SetPos(pos);

			bIsHit = true;
		}
		//右
		else if (nHitSurface == CCollision::SURFACE_RIGHT)
		{
			pos.x = ((playerSize.x / 2) + playerPos.x) + (size.x / 2);

			SetPos(pos);
			bIsHit = true;
		}
		//奥
		else if (nHitSurface == CCollision::SURFACE_PREVIOUS)
		{
			pos.z = ((-playerSize.z / 2) + playerPos.z) - (size.z / 2);

			SetPos(pos);

			bIsHit = true;
		}
		//手前
		else if (nHitSurface == CCollision::SURFACE_BACK)
		{
			pos.z = ((playerSize.z / 2) + playerPos.z) + (size.z / 2);

			SetPos(pos);

			bIsHit = true;
		}

		if (bIsHit)
		{
			//プレイヤーに対しアクションする
			//pPlayer->
		}
	}

	return bIsHit;
}

void CJailer::CheckMapCollision(void)
{
	// CSceneのポインタ
	CScene *pScene = nullptr;

	// モデルの情報取得
	CModelAnime *pAnime = GetModelAnime(0);

	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// 位置取得
	D3DXVECTOR3 posOld = GetOldPos();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// nullcheck
	if (pScene == nullptr)
	{
		// 先頭のポインタ取得
		pScene = GetTop(CScene::PRIORITY_MAP);

		// !nullcheck
		if (pScene != nullptr)
		{
			// Mapオブジェクトの当たり判定
			while (pScene != nullptr) // nullptrになるまで回す
			{
				// 現在のポインタ
				CScene *pSceneCur = pScene->GetNext();

				// 位置取得
				D3DXVECTOR3 ObjPos = ((CObject*)pScene)->GetPos();

				// サイズ取得
				D3DXVECTOR3 ObjSize = ((CObject*)pScene)->GetSize();

				//どこの面に当たったか取得
				//下
				if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, ObjPos, size, ObjSize) == CCollision::SURFACE_DOWN)
				{
					// 移動量0
					GetMove().y = 0.0f;

					// 位置
					pos.y = (-ObjSize.y / DIVIDE_2 + ObjPos.y) - (size.y / DIVIDE_2);

					// 位置設定
					SetPos(pos);
				}
				// 上
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, ObjPos, size, ObjSize) == CCollision::SURFACE_UP)
				{
					// 移動量0
					GetMove().y = 0.0f;

					// 位置
					pos.y = (ObjSize.y / DIVIDE_2 + ObjPos.y) + (size.y / DIVIDE_2);

					// 位置設定
					SetPos(pos);
				}
				// 左
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, ObjPos, size, ObjSize) == CCollision::SURFACE_LEFT)
				{
					// 移動量0
					GetMove().x = 0.0f;

					// 位置
					pos.x = (-ObjSize.x / DIVIDE_2 + ObjPos.x) - (size.x / DIVIDE_2);

					// 位置設定
					SetPos(pos);
				}
				// 右
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, ObjPos, size, ObjSize) == CCollision::SURFACE_RIGHT)
				{
					// 移動量0
					GetMove().x = 0.0f;

					// 位置
					pos.x = (ObjSize.x / DIVIDE_2 + ObjPos.x) + (size.x / DIVIDE_2);

					// 位置設定
					SetPos(pos);
				}
				// 手前
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, ObjPos, size, ObjSize) == CCollision::SURFACE_PREVIOUS)
				{
					// 移動量0
					GetMove().z = 0.0f;

					// 位置
					pos.z = (-ObjSize.z / DIVIDE_2 + ObjPos.z) - (size.z / DIVIDE_2);

					// 位置設定
					SetPos(pos);
				}
				// 奥
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, ObjPos, size, ObjSize) == CCollision::SURFACE_BACK)
				{
					// 移動量0
					GetMove().z = 0.0f;

					// 位置
					pos.z = (ObjSize.z / DIVIDE_2 + ObjPos.z) + (size.z / DIVIDE_2);

					// 位置設定
					SetPos(pos);
				}

				// 次のポインタ取得
				pScene = pSceneCur;
			}
		}
	}
}

void CJailer::SetRetrunData(void)
{
	m_posDest = m_pSpot->BackToRoute(GetPos());
}

void CJailer::SetGuardBaseDir(void)
{
	D3DXVECTOR3 rot = GetRot();

	m_GuardBaseDir = rot;

	m_rotDest.y = m_GuardBaseDir.y - GUARD_ROT_ANGLE;
}
