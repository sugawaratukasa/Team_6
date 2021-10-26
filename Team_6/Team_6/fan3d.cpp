//=============================================================================
//
// 3D扇形処理 [fan3d.cpp]
// Author : 山田陵太
//
//=============================================================================
#include "fan3d.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "player.h"
#include "debug_proc.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define VERTEX_MODIFYING_VALUE (2)		//頂点の修正値
#define DEFAULT_CENTER_ANGLE (80.0f)	//中心角のデフォルト値
#define MIN_CENTER_ANGLE (30.0f)		//中心角の最小値
#define MAX_CENTER_ANGLE (120.0f)		//中心角の最小値
#define DEFAULT_LNGTH (1000.0f)			//長さのデフォルト値
#define MIN_LNGTH (500.0f)				//長さの最小値
#define MAX_LNGTH (2000.0f)				//長さの最大値

//=============================================================================
//クリエイト処理
//=============================================================================
CFan3D * CFan3D::Create(const D3DXVECTOR3 & rPos, const D3DXVECTOR3 & rRot,  const int & rnPolygonNum, const D3DXCOLOR & rCol)
{
	CFan3D *pFan3D = nullptr;

	//インスタンス生成
	pFan3D = new CFan3D;

	if (pFan3D)
	{
		pFan3D->SetPolygonNum(rnPolygonNum);
		pFan3D->SetColor(rCol);
		pFan3D->Init(rPos, rRot);

		return pFan3D;
	}
	return nullptr;
}

//=============================================================================
//コンストラクタ
//=============================================================================
CFan3D::CFan3D()
{
	//各メンバ変数のクリア
	D3DXMatrixIdentity(&m_mtxWorld);
	m_nVerNum = 0;
	m_nPolygonNum = 0;
	m_fCenterAngle = 0.0f;
	m_fLength = 0.0f;
	m_bIsDetection = false;
}

//=============================================================================
//デストラクタ
//=============================================================================
CFan3D::~CFan3D()
{
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CFan3D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = nullptr;	//頂点バッファのポインタ変数

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点数の設定
	m_nVerNum = m_nPolygonNum + VERTEX_MODIFYING_VALUE;

	//位置の設定
	SetPos(pos);

	//向きの設定
	SetRot(rot);

	//中心角の設定
	m_fCenterAngle = DEFAULT_CENTER_ANGLE;

	//長さの設定
	m_fLength = DEFAULT_LNGTH;

	//頂点バッファの作成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_FAN_3D) * m_nVerNum,	//バッファサイズ
		D3DUSAGE_WRITEONLY,	//（固定）
		FVF_VERTEX_FAN_3D,	//フォーマット
		D3DPOOL_MANAGED,	//(固定)
		&pVtxBuff,
		nullptr);

	//頂点バッファの設定
	BindVtxBuff(pVtxBuff);

	//頂点の更新
	VerTexUpdate();

	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CFan3D::Uninit(void)
{
	//オブジェクト破棄
	Release();
}

//=============================================================================
//更新処理
//=============================================================================
void CFan3D::Update(void)
{
	//頂点の更新
	VerTexUpdate();
	
	//中心角の修正
	CenterAngleModifying();

	//長さの修正
	LengthModifying();

	//検出情報を取得
	m_bIsDetection = PlayerDetection();

	//プレイヤーと当たっていた場合
	if (m_bIsDetection)
	{
		//ポリゴンを赤に変える
		SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));
	}
	else
	{
		SetColor(D3DCOLOR_RGBA(0, 0, 255, 255));
	}
	
#ifdef _DEBUG
	//中心角の変更
	if (CManager::GetKeyboard()->GetPress(DIK_NUMPAD4))
	{
		m_fCenterAngle += 1.0f;
	}
	if (CManager::GetKeyboard()->GetPress(DIK_NUMPAD6))
	{
		m_fCenterAngle -= 1.0f;
	}
	//長さの変更
	if (CManager::GetKeyboard()->GetPress(DIK_NUMPAD1))
	{
		m_fLength += 10.0f;
	}
	if (CManager::GetKeyboard()->GetPress(DIK_NUMPAD3))
	{
		m_fLength -= 10.0f;
	}
	CDebugProc::Print("=====================Fan3D=====================\n");
	CDebugProc::Print("【視野角】%0.2f\n",m_fCenterAngle);
	CDebugProc::Print("【Num4で視野角の拡大】\n");
	CDebugProc::Print("【Num6で視野角の縮小】\n");
	CDebugProc::Print("【長さ】%0.2f\n", m_fLength);
	CDebugProc::Print("【Num1で長さの拡大】\n");
	CDebugProc::Print("【Num3で長さの縮小】\n");
#endif
}

//=============================================================================
//描画処理
//=============================================================================
void CFan3D::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ライティングの影響を受けないようにする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;	//計算用のマトリクス

	//位置と向きの取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//スケールの反映
	D3DXMatrixScaling(&mtxScale, 1.0f, 1.0f, 1.0f);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	//向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_FAN_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_FAN_3D);

	// ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLEFAN,	//プリミティブの種類
		0,
		m_nPolygonNum);	//ポリゴン数

	//ライティングの影響を受けないようにする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
//頂点更新処理
//=============================================================================
void CFan3D::VerTexUpdate(void)
{
	VERTEX_FAN_3D *pVtxFan;

	//頂点バッファの取得
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	//色の取得
	D3DXCOLOR col = GetColor();

	//頂点データをロックし、頂点バッファへのポインタ取得
	pVtxBuff->Lock(0, 0, (void**)&pVtxFan, 0);

	D3DXVECTOR3 pos = ZeroVector3;			//各頂点の回転前の位置
	D3DXVECTOR3 rotate_pos = ZeroVector3;	//各頂点の回転後の位置

	float fAngle = -m_fCenterAngle / (float)m_nPolygonNum;	//一ポリゴン当たりの角度
	float fStrat_Angle = m_fCenterAngle / 2.0f;				//ポリゴン角度の基準点
	float fRotate_Rad = D3DXToRadian(-90.0f);				//回転角度

	//中心の頂点の設定
	pVtxFan[0].pos = ZeroVector3;
	pVtxFan[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtxFan[0].col = col;

	//中心点をのぞいた残りの頂点数分繰り返す
	for (int nCntVerNum = 0; nCntVerNum <= m_nPolygonNum; nCntVerNum++)
	{
		//回転前の頂点の計算
		pos.x = cosf(D3DXToRadian(fStrat_Angle + nCntVerNum * fAngle)) * m_fLength;
		pos.y = pVtxFan[0].pos.y;
		pos.z = sinf(D3DXToRadian(fStrat_Angle + nCntVerNum * fAngle)) * m_fLength;

		//頂点をポリゴンの向きに合わせて調整
		rotate_pos.x = pos.x * cosf(fRotate_Rad) + pos.z * -sinf(fRotate_Rad) + pVtxFan[0].pos.x;
		rotate_pos.y = pVtxFan[0].pos.y;
		rotate_pos.z = pos.x * sinf(fRotate_Rad) + pos.z * cosf(fRotate_Rad) + pVtxFan[0].pos.z;

		//頂点情報を設定
		pVtxFan[nCntVerNum + 1].pos = rotate_pos;
		pVtxFan[nCntVerNum + 1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtxFan[nCntVerNum + 1].col = col;
	}

	//頂点バッファをアンロック
	pVtxBuff->Unlock();
}

//=============================================================================
//中心角の修正処理
//=============================================================================
void CFan3D::CenterAngleModifying(void)
{
	//中心角のが360°より大きくなった場合
	if (m_fCenterAngle >= MAX_CENTER_ANGLE)
	{
		m_fCenterAngle = MAX_CENTER_ANGLE;
	}
	//中心角のが0°より小さくなった場合
	if (m_fCenterAngle <= MIN_CENTER_ANGLE)
	{
		m_fCenterAngle = MIN_CENTER_ANGLE;
	}
}

void CFan3D::LengthModifying(void)
{
	//長さが最大値より大きくなった場合
	if (m_fLength > MAX_LNGTH)
	{
		m_fLength = MAX_LNGTH;
	}
	//長さが最小値より大きくなった場合
	if (m_fLength < MIN_LNGTH)
	{
		m_fLength = MIN_LNGTH;
	}
}

//=============================================================================
//プレイヤーの検出処理
//=============================================================================
bool CFan3D::PlayerDetection(void)
{
	//プレイヤーの位置・自分の位置の取得
	D3DXVECTOR3 playerPos = GET_PLAYER_PTR->GetPos();
	D3DXVECTOR3 pos = GetPos();

	//扇からモデルまでのベクトルを計算(高さは必要なしのため除外)
	D3DXVECTOR3 fanToPlayer = ZeroVector3;
	fanToPlayer.x = playerPos.x - pos.x;
	fanToPlayer.z = playerPos.z - pos.z;

	//ベクトルの長さを計算
	float fVecLength = sqrtf((fanToPlayer.x * fanToPlayer.x) + (fanToPlayer.z * fanToPlayer.z));

	//ベクトルの長さが半径より大きいと失敗
	if (fVecLength > m_fLength)
	{
		return false;
	}

	//回転角度0度の単位ベクトル
	D3DXVECTOR3 fanDir = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	D3DXVECTOR3 rotFanDir = ZeroVector3;

	//向きの情報を修正
	float fRot = GetRot().y + D3DXToRadian(90.0f);

	//ベクトルを回転させる
	rotFanDir.x = fanDir.x * cosf(fRot) + fanDir.z *-sinf(fRot);
	rotFanDir.z = fanDir.x * sinf(fRot) + fanDir.z *cosf(fRot);

	//扇からプレイヤーへのベクトルを正規化
	D3DXVECTOR3 norFanToPoint = D3DXVECTOR3(
		fanToPlayer.x / fVecLength,
		fanToPlayer.y / fVecLength,
		fanToPlayer.z / fVecLength);

	//扇とプレイヤーのベクトルのなす角度を求める（内積）
	float fDot = norFanToPoint.x * rotFanDir.x - norFanToPoint.z * rotFanDir.z;

	//扇の方向ベクトルをcosにする
	float fFanCos = cosf(D3DXToRadian(m_fCenterAngle / 2.0f));

	//なす角が扇の角度より大きいと失敗
	if (fFanCos > fDot)
	{
		return false;
	}

	return true;
}
