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

//=============================================================================
//マクロ定義
//=============================================================================
#define JAILER_SPEED (10.0f)	//速さ
#define MOVE_TEST D3DXVECTOR3(0.0f, 0.0f, -2.0f)

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
	m_nIndex = 0;
	m_posDest = ZeroVector3;
	m_pFan3d = nullptr;
}

//=============================================================================
//デストラクタ
//=============================================================================
CJailer::~CJailer()
{
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
	SetMotion(JAILER_MOTION_MOVE);

	//速さの設定
	SetSpeed(JAILER_SPEED);

	SetUseShadow();

	// 影の向き
	SetShadowRotCalculation();
	m_posDest = posdest[0];

	SetPos(m_posDest);

	//視界のクリエイト
	m_pFan3d = CFan3D::Create(D3DXVECTOR3(m_posDest.x, 20.0f, m_posDest.z), ZeroVector3, 8, D3DCOLOR_RGBA(255, 0, 0, 255));

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

	//移動処理
	Move();

	//m_pState->Update(this);
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
//移動処理
//=============================================================================
void CJailer::Move(void)
{
	D3DXVECTOR3 move = ZeroVector3;
	//単位ベクトル
	D3DXVECTOR3 nor = ZeroVector3;
	float angle = 0.0f;
	//位置の取得
	D3DXVECTOR3 pos = GetPos();

	D3DXVECTOR3 postodest = (m_posDest - pos);

	/*if (postodest.x < 0.0f)
	{
		if (postodest.z > 0.0f)
		{
				m_nIndex++;

				if (m_nIndex >= CJailer::POS_DEST_MAX)
				{
					m_nIndex = CJailer::POS_DEST_LEFT_TOP;
				}

				m_posDest = posdest[m_nIndex];
			
		}
	}*/
	if (postodest == ZeroVector3)
	{
		m_nIndex++;

		if (m_nIndex >= CJailer::POS_DEST_MAX)
		{
			m_nIndex = CJailer::POS_DEST_LEFT_TOP;
		}

		m_posDest = posdest[m_nIndex];
	}
	
	//移動方向のベクトルの正規化
	D3DXVec3Normalize(&nor, &postodest);

	//移動方向に対しての回転角を求める
	angle = atan2f(-nor.x, -nor.z);

	//目的の角度へ設定
	m_rotDest.y = angle;

	//移動量を設定
	move.x = nor.x * GetSpeed();
	move.z = nor.z * GetSpeed();

	//向きを取得
	D3DXVECTOR3 rot = GetRot();

	// 向き補間
	while (m_rotDest.y - rot.y > D3DXToRadian(180))
	{
		m_rotDest.y -= D3DXToRadian(360);
	}

	while (m_rotDest.y - rot.y < -D3DXToRadian(180))
	{
		m_rotDest.y += D3DXToRadian(360);
	}

	//向きの回転
	rot += (m_rotDest - rot)*0.1f;

	//向き設定
	SetRot(rot);

	//移動量の設定
	SetMove(move);
	
	if (m_pFan3d)
	{
		m_pFan3d->SetRotation(rot);									//扇の向きの設定
		m_pFan3d->SetPosition(D3DXVECTOR3(pos.x, 500.0f, pos.z));	//扇の位置の設定
	}

	CDebugProc::Print("=====================Jailer=====================\n");
	CDebugProc::Print("【向き】 X:%f,Y:%f,Z:%f\n", rot.x, rot.y, rot.z);
	CDebugProc::Print("【目的の向き（度数法）】 %f\n", D3DXToDegree(m_rotDest.y));
	CDebugProc::Print("【現在の向き（度数法）】 %f\n", D3DXToDegree(rot.y));
	CDebugProc::Print("【位置】 X:%f,Y:%f,Z:%f\n", pos.x, pos.y, pos.z);
	CDebugProc::Print("【目的の位置】 X:%f,Y:%f,Z:%f\n", posdest[m_nIndex].x, posdest[m_nIndex].y, posdest[m_nIndex].z);
	CDebugProc::Print("【目的-位置】 X:%f,Y:%f,Z:%f\n", postodest.x, postodest.y, postodest.z);
	CDebugProc::Print("【Index】 %d\n", m_nIndex);
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
void CJailer::ChangeState(CJailerState * state)
{
	m_pState = state;
	m_pState->Init(this);
}

//=============================================================================
// 追跡
//=============================================================================
void CJailer::Chase()
{
}

bool CJailer::IsDistanceToPlayer(float distance, bool outside)
{
	if (outside == true)
	{
		return GetDistance() <= distance ? true : false;
	}
	return GetDistance() >= distance ? true : false;
}

//プレイヤーとの距離感
float CJailer::GetDistance()
{
	float X = (m_posX - m_pPlayer->GetPos().x)*(m_posX - m_pPlayer->GetPos().x);
	float Z = (m_posZ - m_pPlayer->GetPos().z)*(m_posZ - m_pPlayer->GetPos().z);

	return sqrt(X+Z);
}
