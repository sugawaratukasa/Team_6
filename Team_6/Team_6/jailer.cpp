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

//=============================================================================
//マクロ定義
//=============================================================================
#define JAILER_NORMAL_SPEED (10.0f)	//通常時の移動速度
#define JAILER_CHASE_SPEED (20.0f)	//追跡時の移動速度
#define JAILER_ROTSTION_RATE (0.1f)	//回転の係数
#define VIEW_POS_Y (70.0f)			//視線の高さ
#define VIEW_POLYGON_NUM (8)		//視線のポリゴン数
#define JAILER_SIZE (D3DXVECTOR3 (100.0f,200.0f,100.0f))	// サイズ
const D3DXVECTOR3 aMoveSpot[CJailer::POS_DEST_MAX] =
{
	D3DXVECTOR3(-1000.0f, 0.0f, 1000.0f),
	D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f),
	D3DXVECTOR3(1000.0f, 0.0f, -1000.0f),
	D3DXVECTOR3(1000.0f, 0.0f, 1000.0f),
};

//=============================================================================
//静的メンバ変数宣言
//=============================================================================
int CJailer::m_nJailerTotal = -1;

//=============================================================================
//コンストラクタ
//=============================================================================
CJailer::CJailer()
{
	m_pView = nullptr;		//扇クラスのポインタ変数
	m_pJailerState = nullptr;
	m_rotDest = ZeroVector3;
	m_posDest = ZeroVector3;
	m_posDestOld = ZeroVector3;
	m_nIndex = ZERO_INT;
	m_nSwitchingTimer = ZERO_INT;
	m_nNumber = ZERO_INT;
	m_fDestinationRange = ZERO_FLOAT;
	
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
	SetSpeed(JAILER_NORMAL_SPEED);

	SetUseShadow();

	// 影の向き
	SetShadowRotCalculation();

	//自分の番号を設定
	m_nNumber = m_nJailerTotal;

	m_nIndex = m_nNumber;
	
	//目的地を設定
	m_posDest = aMoveSpot[m_nIndex];

	//位置の設定
	SetPos(m_posDest);

	//視界のクリエイト
	m_pView = CJailerView::Create(D3DXVECTOR3(m_posDest.x, VIEW_POS_Y, m_posDest.z), 
		ZeroVector3, VIEW_POLYGON_NUM, D3DCOLOR_RGBA(255, 0, 0, 255));

	//状態設定
	m_pJailerState = CWaitState::GetInstance();

	//サイズの設定
	SetSize(JAILER_SIZE);

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

#ifdef _DEBUG
	CDebugProc::Print("【目的位置との距離】X:%f\n",m_fDestinationRange);
	CDebugProc::Print("【目的位置】X:%f,Y:%f,Z:%f\n", m_Distance.x, m_Distance.y, m_Distance.z);

	// キーボード取得
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_NUMPAD7))
	{
		SettingPosDest();
	}

	//DebugpPrint();
#endif
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

	//向きの回転
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
void CJailer::Move(void)
{
#ifdef _DEBUG
	CDebugProc::Print("巡回状態\n");
#endif
	D3DXVECTOR3 move = ZeroVector3;

	//単位ベクトル
	D3DXVECTOR3 nor = ZeroVector3;

	//現在地と目的地までのベクトルを計算
	m_Distance = m_posDest - GetPos();

	//目的地と自分の距離の長さを計算
	m_fDestinationRange = sqrtf((m_Distance.x * m_Distance.x) + (m_Distance.z * m_Distance.z));

	//向きの目的の値の計算
	SetRotDest();

	//アイドルモーション再生
	SetMotion(JAILER_MOTION::JAILER_MOTION_MOVE);

	//速さの設定
	SetSpeed(JAILER_NORMAL_SPEED);

	//移動方向のベクトルの正規化
	D3DXVec3Normalize(&nor, &m_Distance);

	//移動量を設定
	move.x = nor.x * GetSpeed();
	move.z = nor.z * GetSpeed();

	//移動量の設定
	SetMove(move);
}

//=============================================================================
// 待機
//=============================================================================
void CJailer::Wait(void)
{
#ifdef _DEBUG
	CDebugProc::Print("待機状態\n");
#endif

	//前回の向きへ確認
	m_Distance = (m_posDestOld - GetPos());

	//向きの目的の値の計算
	SetRotDest();

	//速さの設定
	SetSpeed(ZERO_FLOAT);

	//移動量の設定
	SetMove(ZeroVector3);

	//アイドルモーション再生
	SetMotion(JAILER_MOTION::JAILER_MOTION_IDOL);
}

//=============================================================================
// 追跡
//=============================================================================
void CJailer::Chase()
{
#ifdef _DEBUG
	CDebugProc::Print("追跡状態\n");
#endif
	D3DXVECTOR3 move = ZeroVector3;
	//単位ベクトル
	D3DXVECTOR3 nor = ZeroVector3;

	//検出した位置
	D3DXVECTOR3 detectedPos = ZeroVector3;
	
	if (m_pView)
	{
		//検出した位置の取得
		detectedPos = m_pView->GetDetectionPos();
#ifdef _DEBUG
		CDebugProc::Print("【プレイヤーを検出した位置】X:%f,Y:%f,Z:%f\n", detectedPos.x, detectedPos.y, detectedPos.z);
#endif
	}
	
	//現在位置と検出した位置までのベクトルを計算
	m_Distance = (detectedPos - GetPos());

	//目的地と自分の距離を計算
	m_fDestinationRange = sqrtf((m_Distance.x * m_Distance.x) + (m_Distance.z * m_Distance.z));

	if (m_fDestinationRange > 10.0f)
	{
		//向きの目的の値の計算
		SetRotDest();

		//アイドルモーション再生
		SetMotion(JAILER_MOTION::JAILER_MOTION_MOVE);

		//速さの設定
		SetSpeed(JAILER_CHASE_SPEED);

		//移動方向のベクトルの正規化
		D3DXVec3Normalize(&nor, &m_Distance);

		//移動量を設定
		move.x = nor.x * GetSpeed();
		move.z = nor.z * GetSpeed();
	}

	//移動量の設定
	SetMove(move);
}

//=============================================================================
// 警戒状態
//=============================================================================
void CJailer::Caution(void)
{
#ifdef _DEBUG
	CDebugProc::Print("警戒状態\n");
#endif
	const D3DXVECTOR3 rot = GetRot();
}

//=============================================================================
//攻撃処理
//=============================================================================
void CJailer::Attack(void)
{
#ifdef _DEBUG
	CDebugProc::Print("攻撃状態\n");
#endif
}

//=============================================================================
// 秒数加算
//=============================================================================
int CJailer::AddTimer(int add)
{
	m_nSwitchingTimer += add;
	return m_nSwitchingTimer;
}

//=============================================================================
// 目的地の設定
//=============================================================================
void CJailer::SettingPosDest(void)
{
	//現在の目的地を前回の目的地として保存
	m_posDestOld = aMoveSpot[m_nIndex];

	//目的地のインデックスを加算
	m_nIndex++;
	
	//インデックスが最大値以上の場合
	if (m_nIndex >= CJailer::POS_DEST_MAX)
	{
		//最初のインデックスへ戻す
		m_nIndex = CJailer::POS_DEST_LEFT_TOP;
	}

	//次の目的の位置を設定
	m_posDest = aMoveSpot[m_nIndex];
}

//=============================================================================
// 向きの目的の値の設定
//=============================================================================
void CJailer::SetRotDest()
{
	D3DXVECTOR3	nor = ZeroVector3;

	//移動方向のベクトルの正規化
	D3DXVec3Normalize(&nor, &m_Distance);

	//移動方向に対しての回転角を求める
	float angle = atan2f(-nor.x, -nor.z);

	//目的の角度へ設定
	m_rotDest.y = angle;
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

#ifdef _DEBUG
			CDebugProc::Print("プレイヤー%dと左側が当たった\n", nCntPlayer);
#endif

			bIsHit = true;
		}
		//右
		else if (nHitSurface == CCollision::SURFACE_RIGHT)
		{
			pos.x = ((playerSize.x / 2) + playerPos.x) + (size.x / 2);

			SetPos(pos);
#ifdef _DEBUG
			CDebugProc::Print("プレイヤー%dと右側が当たった\n", nCntPlayer);
#endif
			bIsHit = true;
		}
		//奥
		else if (nHitSurface == CCollision::SURFACE_PREVIOUS)
		{
			pos.z = ((-playerSize.z / 2) + playerPos.z) - (size.z / 2);

			SetPos(pos);

#ifdef _DEBUG
			CDebugProc::Print("プレイヤー%dと奥側が当たった\n", nCntPlayer);
#endif
			bIsHit = true;
		}
		//手前
		else if (nHitSurface == CCollision::SURFACE_BACK)
		{
			pos.z = ((playerSize.z / 2) + playerPos.z) + (size.z / 2);

			SetPos(pos);

#ifdef _DEBUG
			CDebugProc::Print("プレイヤー%dと手前側が当たった\n", nCntPlayer);
#endif
			bIsHit = true;
		}
		else
		{
#ifdef _DEBUG
			CDebugProc::Print("プレイヤー%dとは当たっていない\n", nCntPlayer);
#endif
		}

		if (bIsHit)
		{
			//プレイヤーに対しアクションする
			//pPlayer->
		}
	}

	return bIsHit;
}

#ifdef _DEBUG
//=============================================================================
//デバック画面
//=============================================================================
void CJailer::DebugpPrint(void)
{
	//変数
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 move = GetMove();
	float Speed = GetSpeed();

	CDebugProc::Print("=====================Jailer=====================\n");
	CDebugProc::Print("【向き】 X:%f,Y:%f,Z:%f\n", rot.x, rot.y, rot.z);
	CDebugProc::Print("【目的の向き（度数法）】 %f\n", D3DXToDegree(m_rotDest.y));
	CDebugProc::Print("【現在の向き（度数法）】 %f\n", D3DXToDegree(rot.y));
	CDebugProc::Print("【位置】 X:%f,Y:%f,Z:%f\n", pos.x, pos.y, pos.z);
	CDebugProc::Print("【目的の位置】 X:%f,Y:%f,Z:%f\n", aMoveSpot[m_nIndex].x, aMoveSpot[m_nIndex].y, aMoveSpot[m_nIndex].z);
	CDebugProc::Print("【Index】 %d\n", m_nIndex);
	CDebugProc::Print("【移動量】 X:%f,Y:%f,Z:%f\n", move.x, move.y, move.z);
	CDebugProc::Print("【Speed】 %f\n", Speed);
	CDebugProc::Print("【カウント】 %d\n", m_nSwitchingTimer);
}
#endif