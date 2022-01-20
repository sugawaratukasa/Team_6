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

//=============================================================================
//マクロ定義
//=============================================================================
#define FVF_VERTEX_FAN_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE)	//3D扇形の頂点フォーマット
#define VERTEX_MODIFYING_VALUE (2)										//頂点の修正値
#define DEFAULT_CENTER_ANGLE (90.0f)									//中心角のデフォルト値
#define MIN_CENTER_ANGLE (30.0f)										//中心角の最小値
#define MAX_CENTER_ANGLE (180.0f)										//中心角の最小値
#define DEFAULT_LNGTH (1500.0f)											//長さのデフォルト値
#define MIN_LNGTH (50.0f)												//長さの最小値
#define MAX_LNGTH (5000.0f)												//長さの最大値
#define ORIGIN_NUMBER (0)												//原点の番号

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
		//各値の設定
		pFan3D->SetPolygonNum(rnPolygonNum);
		pFan3D->SetColor(rCol);

		//初期化処理
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
	m_nVertexNum = 0;
	m_nPolygonNum = 0;
	m_fCenterAngle = 0.0f;
	m_fLength = 0.0f;
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
	m_nVertexNum = m_nPolygonNum + VERTEX_MODIFYING_VALUE;

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
		sizeof(VERTEX_FAN_3D) * m_nVertexNum,	//バッファサイズ
		D3DUSAGE_WRITEONLY,	//（固定）
		FVF_VERTEX_FAN_3D,	//フォーマット
		D3DPOOL_MANAGED,	//(固定)
		&pVtxBuff,
		nullptr);

	//頂点バッファの設定
	BindVtxBuff(pVtxBuff);

	//頂点の更新
	VertexUpdate();

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
	VertexUpdate();
	
	//中心角の修正
	CenterAngleModifying();

	//長さの修正
	LengthModifying();
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
void CFan3D::VertexUpdate(void)
{
	VERTEX_FAN_3D *pVtxFan = nullptr;

	//頂点バッファの取得
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	//色の取得
	D3DXCOLOR col = GetColor();

	//頂点データをロックし、頂点バッファへのポインタ取得
	pVtxBuff->Lock(0, 0, (void**)&pVtxFan, 0);

	D3DXVECTOR3 pos = ZeroVector3;			//各頂点の回転前の位置
	D3DXVECTOR3 rotate_pos = ZeroVector3;	//各頂点の回転後の位置

	float fAngle = -m_fCenterAngle / (float)m_nPolygonNum;	//一頂点当たりの角度
	float fStrat_Angle = m_fCenterAngle / 2.0f;				//頂点角度の基準点
	float fRotate_Rad = D3DXToRadian(-90.0f);				//回転角度

	//中心（原点）の頂点の設定
	pVtxFan[ORIGIN_NUMBER].pos = ZeroVector3;
	pVtxFan[ORIGIN_NUMBER].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtxFan[ORIGIN_NUMBER].col = col;

	//中心点をのぞいた残りの頂点数分繰り返す
	for (int nCntVerNum = ZERO_INT; nCntVerNum <= m_nPolygonNum; nCntVerNum++)
	{
		//回転前の頂点の計算
		pos.x = cosf(D3DXToRadian(fStrat_Angle + nCntVerNum * fAngle)) * m_fLength;
		pos.y = pVtxFan[ORIGIN_NUMBER].pos.y;
		pos.z = sinf(D3DXToRadian(fStrat_Angle + nCntVerNum * fAngle)) * m_fLength;

		//頂点をポリゴンの向きに合わせて調整
		rotate_pos.x = pos.x * cosf(fRotate_Rad) + pos.z * -sinf(fRotate_Rad) + pVtxFan[ORIGIN_NUMBER].pos.x;
		rotate_pos.y = pVtxFan[0].pos.y;
		rotate_pos.z = pos.x * sinf(fRotate_Rad) + pos.z * cosf(fRotate_Rad) + pVtxFan[ORIGIN_NUMBER].pos.z;

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
	//中心角が最大値より大きくなった場合
	if (m_fCenterAngle > MAX_CENTER_ANGLE)
	{
		m_fCenterAngle = MAX_CENTER_ANGLE;
	}
	//中心角が最小値より大きくなった場合
	if (m_fCenterAngle < MIN_CENTER_ANGLE)
	{
		m_fCenterAngle = MIN_CENTER_ANGLE;
	}
}

//=============================================================================
//長さの修正処理
//=============================================================================
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
