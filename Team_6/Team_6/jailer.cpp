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

int CJailer::m_nJailerTotal = -1;
//=============================================================================
//マクロ定義
//=============================================================================
#define JAILER_NORMAL_SPEED (10.0f)				//通常時の移動速度
#define JAILER_CHASE_SPEED (20.0f)				//追跡時の移動速度

#define JAILER_ROTSTION_RATE (0.1f)	//回転の係数
const D3DXVECTOR3 posdest[CJailer::POS_DEST_MAX] =
{
	D3DXVECTOR3(-1000.0f, 0.0f, 1000.0f),
	D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f),
	D3DXVECTOR3(1000.0f, 0.0f, -1000.0f),
	D3DXVECTOR3(1000.0f, 0.0f, 1000.0f),
};

//=============================================================================
//コンストラクタ
//=============================================================================
CJailer::CJailer()
{
	m_rotDest = ZeroVector3;
	m_posDest = ZeroVector3;
	m_posDestOld = ZeroVector3;
	m_nIndex = 0;
	m_SwitchingTimer = 0;
	m_nNumber = 0;
	m_cStateName.clear();		//デバック用状態名称
	m_pView = nullptr;		//扇クラスのポインタ変数
	m_pState = nullptr;
	m_nJailerTotal++;
}

//=============================================================================
//デストラクタ
//=============================================================================
CJailer::~CJailer()
{
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

	if (m_nNumber == 0)
	{
		m_nIndex = 0;
	}
	else
	{
		m_nIndex = 2;
	}
	
	//目的地を設定
	m_posDest = posdest[m_nIndex];

	//位置の設定
	SetPos(m_posDest);

	//視界のクリエイト
	m_pView = CJailerView::Create(D3DXVECTOR3(m_posDest.x, 2.0f, m_posDest.z), ZeroVector3, 8, D3DCOLOR_RGBA(255, 0, 0, 255));

	//状態設定
	m_pState = CWaitState::GetInstance();

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
	//キャラクターの更新処理
	CCharacter::Update();

	//位置の取得
	D3DXVECTOR3 pos = GetPos();

	//前回位置の設定
	SetPosOld(pos);

	//アニメーションの更新
	ModelAnimeUpdate();

	DebugpPrint();

	//回転処理
	Rotation();

	//状態処理の更新
	m_pState->Update(this, m_pView);
	
	if (m_pView)
	{
		m_pView->SetRotation(GetRot());							//扇の向きの設定
		m_pView->SetPosition(D3DXVECTOR3(pos.x, 70.0f, pos.z));	//扇の位置の設定
	}

	// キーボード取得
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_NUMPAD7))
	{
		SettingPosDest();
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


void CJailer::UpdateState(void)
{

}

//=============================================================================
//攻撃処理
//=============================================================================
void CJailer::Attack(void)
{
}

//=============================================================================
//回転関数
//=============================================================================
void CJailer::Rotation(void)
{	
	D3DXVECTOR3	nor = ZeroVector3;

	//移動方向のベクトルの正規化
	D3DXVec3Normalize(&nor, &m_Distance);

	//移動方向に対しての回転角を求める
	float angle = atan2f(-nor.x, -nor.z);

	//目的の角度へ設定
	m_rotDest.y = angle;

	//向きを取得
	D3DXVECTOR3 rot = GetRot();

	// 向き補間
	while ((m_rotDest.y - rot.y) > D3DXToRadian(180))
	{
		m_rotDest.y -= D3DXToRadian(360);
	}

	while ((m_rotDest.y - rot.y) < -D3DXToRadian(180))
	{
		m_rotDest.y += D3DXToRadian(360);
	}

	//向きの回転
	rot += (m_rotDest - rot) * JAILER_ROTSTION_RATE;

	//向き設定
	SetRot(rot);
}

//=============================================================================
//死亡処理
//=============================================================================
void CJailer::Death(void)
{

}

//=============================================================================
// 状態切り替え関数
//=============================================================================
void CJailer::ChangeState(CJailerState * jailerstate)
{
	m_pState = jailerstate;
	m_pState->Init(this, m_pView);
}

//=============================================================================
//移動処理
//=============================================================================
void CJailer::Move(void)
{
	D3DXVECTOR3 move = ZeroVector3;

	//単位ベクトル
	D3DXVECTOR3 nor = ZeroVector3;

	//位置の取得
	D3DXVECTOR3 pos = GetPos();

	//現在地と目的地までのベクトルを計算
	m_Distance = (m_posDest - pos);

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
	//位置の取得
	D3DXVECTOR3 pos = GetPos();

	//前回の向きへ確認
	m_Distance = (m_posDestOld - pos);

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
	D3DXVECTOR3 move = ZeroVector3;
	//単位ベクトル
	D3DXVECTOR3 nor = ZeroVector3;

	//検出した位置
	D3DXVECTOR3 detectedPos = ZeroVector3;

	//位置の取得
	D3DXVECTOR3 pos = GetPos();
	
	if (m_pView)
	{
		//検出した位置の取得
		detectedPos = m_pView->GetDetectionPos();
	}

	//現在位置と検出した位置までのベクトルを計算
	m_Distance = (detectedPos - pos);

	//アイドルモーション再生
	SetMotion(JAILER_MOTION::JAILER_MOTION_MOVE);

	//速さの設定
	SetSpeed(JAILER_CHASE_SPEED);

	//移動方向のベクトルの正規化
	D3DXVec3Normalize(&nor, &m_Distance);

	//移動量を設定
	move.x = nor.x * GetSpeed();
	move.z = nor.z * GetSpeed();

	//移動量の設定
	SetMove(move);
}


//=============================================================================
// 秒数加算
//=============================================================================
int CJailer::AddTimer(int add)
{
	m_SwitchingTimer += add;
	return m_SwitchingTimer;
}

//=============================================================================
// 目的地の設定
//=============================================================================
void CJailer::SettingPosDest(void)
{
	m_nIndex++;
	
	//インデックスが最大値以上の場合
	if (m_nIndex >= CJailer::POS_DEST_MAX)
	{
		m_nIndex = CJailer::POS_DEST_LEFT_TOP;
	}
	//次の目的の位置を設定
	m_posDest = posdest[m_nIndex];

	//前回のインデックスを計算
	int IndexOld = m_nIndex - 1;

	//前回のインデックスが最小値より小さくなった場合
	if (IndexOld < CJailer::POS_DEST_LEFT_TOP)
	{
		IndexOld = POS_DEST_RIGHT_TOP;
	}

	//前回の目的地を設定する
	m_posDestOld = posdest[IndexOld];
}


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
	CDebugProc::Print("【目的の位置】 X:%f,Y:%f,Z:%f\n", posdest[m_nIndex].x, posdest[m_nIndex].y, posdest[m_nIndex].z);
	CDebugProc::Print("【Index】 %d\n", m_nIndex);
	CDebugProc::Print("【移動量】 X:%f,Y:%f,Z:%f\n", move.x, move.y, move.z);
	CDebugProc::Print("【Speed】 %f\n", Speed);
	CDebugProc::Print("【カウント】 %d\n", m_SwitchingTimer);
}

