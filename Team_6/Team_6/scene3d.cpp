//=============================================================================
//
// シーン3Dクラス [scene3D.cpp]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "scene3D.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CScene3D::CScene3D(PRIORITY Priority) : CSceneBase(Priority)
{
	m_nCountAnim = 0;
	m_nCountAnimPattern = 0;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_nLoop = -1;
	m_fScaleNum = 0.0f;
	m_nAlphaTestNum = 0;
	m_bAlpha = false;
	m_bInverse = false;
	m_fAlphaNum = 0.0f;
	m_move = ZeroVector3;

}

//=============================================================================
// デストラクタ
//=============================================================================
CScene3D::~CScene3D()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScene3D::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// デバイス情報取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = nullptr;
	VERTEX_3D*pVtx = nullptr;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		nullptr);
	// 情報の代入
	SetPos(pos);
	SetSize(size);

	// 色取得
	D3DXCOLOR color = GetColor();

	//頂点バッファをロック
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定の設定
	pVtx[0].pos = D3DXVECTOR3((-size.x / DIVIDE_2), (size.y / DIVIDE_2), (size.z / DIVIDE_2));
	pVtx[1].pos = D3DXVECTOR3((size.x / DIVIDE_2), (size.y / DIVIDE_2), (size.z / DIVIDE_2));
	pVtx[2].pos = D3DXVECTOR3((-size.x / DIVIDE_2), (-size.y / DIVIDE_2), (-size.z / DIVIDE_2));
	pVtx[3].pos = D3DXVECTOR3((size.x / DIVIDE_2), (-size.y / DIVIDE_2), (-size.z / DIVIDE_2));

	//各頂点の法線の設定（※ベクトルの大きさは１にする必要がある）
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定（0～255の数値で設定）
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	// テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	pVtxBuff->Unlock();

	// バッファの受け渡し
	BindVtxBuff(pVtxBuff);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CScene3D::Uninit(void)
{
	//オブジェクト破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CScene3D::Update(void)
{
	// 移動量加算
	GetPos() += m_move;

	// アニメーションの設定がされたとき
	if (m_nPatternAnim != 0)
	{
		// アニメーションを更新する
		UpdateAnimation();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CScene3D::Draw(void)
{
	// デバイス情報取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//計算用のマトリクス
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	// 加算合成
	if (m_bBlend == true)
	{
		// 加算合成を行う
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// aデスティネーションカラー
	}

	// テクスチャの設定
	pDevice->SetTexture(0, GetTexture());

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向き取得
	D3DXVECTOR3 rot = GetRot();

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// サイズ情報
	D3DXVECTOR3 pos = GetPos();

	// 位置を反映、ワールドマトリクス設定、ポリゴン描画
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリクスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// 加算合成を行う処理
	if (m_bBlend == true)
	{
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// aデスティネーションカラー
	}
}

//=============================================================================
// 移動量
//=============================================================================
void CScene3D::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// 座標設定(座標更新用)
//=============================================================================
void CScene3D::SetPosision(D3DXVECTOR3 pos)
{
	// 座標設定
	SetPos(pos);

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// 頂点情報を設定
	VERTEX_3D *pVtx = nullptr;

	// バッファ取得
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定の設定
	pVtx[0].pos = D3DXVECTOR3(-(size.x / 2), +(size.y / 2), (size.z / 2));
	pVtx[1].pos = D3DXVECTOR3(+(size.x / 2), +(size.y / 2), (size.z / 2));
	pVtx[2].pos = D3DXVECTOR3(-(size.x / 2), -(size.y / 2), -(size.z / 2));
	pVtx[3].pos = D3DXVECTOR3(+(size.x / 2), -(size.y / 2), -(size.z / 2));

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();
}

//=============================================================================
// 色の設定
//=============================================================================
void CScene3D::SetColor(D3DXCOLOR col)
{
	// 色を変える
	CSceneBase::SetColor(col);

	// バッファ取得
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	VERTEX_3D*pVtx = nullptr;

	//頂点バッファをロック
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定（0～255の数値で設定）
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//頂点バッファのアンロック
	pVtxBuff->Unlock();
}

//=============================================
// アニメーション情報取得
//=============================================
void CScene3D::InitAnimation(D3DXVECTOR2 TexInfo, int nLoop)
{
	// 値の代入
	m_nPatternAnim = (int)TexInfo.x;
	m_nCounterAnim = (int)TexInfo.y;
	m_nLoop = nLoop;

	// バッファ取得
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	VERTEX_3D *pVtx = nullptr;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標を更新
	pVtx[0].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 0.0f);
	pVtx[2].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 1.0f);

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();
}

//=============================================
// アニメーション更新関数
//=============================================
void CScene3D::UpdateAnimation(void)
{
	// 爆発のアニメーションカウントを進めて、パターンを切り替える
	m_nCountAnim++;

	// 頂点情報(テクスチャ座標)の更新
	if (m_nCountAnim >= m_nCounterAnim)	// 爆発の速さ
	{
		// アニメーションのカウントを0にする
		m_nCountAnim = 0;

		// アニメーションのパターンをカウントさせる
		m_nCountAnimPattern++;
	}

	// アニメーションが終わったら
	if (m_nCountAnimPattern >= m_nPatternAnim)
	{
		// 数値を戻しておく
		m_nCountAnimPattern = 0;

		if (m_nLoop == 0)
		{
			// 終了処理
			Uninit();
		}
	}
	else
	{
		// バッファ取得
		LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
		VERTEX_3D *pVtx = nullptr;

		// 頂点バッファをロックし、頂点情報へのポインタを取得
		pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//テクスチャ座標を更新
		pVtx[0].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 1.0f);

		// 頂点バッファをアンロックする
		pVtxBuff->Unlock();
	}
}

//======================================================
// 拡大関数
//======================================================
void CScene3D::ScaleUp(float fScaleUp)
{
	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	m_fScaleNum += fScaleUp;

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();	// バッファ取得
	VERTEX_3D *pVtx = nullptr;							//頂点情報へのポインタ

														//頂点データ範囲をロックし、頂点バッファへのポインタを所得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-(size.x * m_fScaleNum), +(size.y * m_fScaleNum), (size.z * m_fScaleNum));
	pVtx[1].pos = D3DXVECTOR3(+(size.x * m_fScaleNum), +(size.y * m_fScaleNum), (size.z * m_fScaleNum));
	pVtx[2].pos = D3DXVECTOR3(-(size.x * m_fScaleNum), -(size.y * m_fScaleNum), -(size.z * m_fScaleNum));
	pVtx[3].pos = D3DXVECTOR3(+(size.x * m_fScaleNum), -(size.y * m_fScaleNum), -(size.z * m_fScaleNum));

	//頂点データをアンロック
	pVtxBuff->Unlock();
}

//=============================================================================
// 透明度の減算
//=============================================================================
void CScene3D::SubAlpha(float fAlphaNum)
{
	// 色の情報
	D3DXCOLOR col = GetColor();

	m_fAlphaNum = fAlphaNum;

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();	// バッファ取得
	VERTEX_3D*pVtx;	//頂点情報へのポインタ

					//頂点データ範囲をロックし、頂点バッファへのポインタを所得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		//頂点カラーの設定（0～255の数値で設定）
		pVtx[nCount].col = D3DXCOLOR(col.r, col.g, col.b, col.a - m_fAlphaNum);
	}

	//頂点データをアンロック
	pVtxBuff->Unlock();
}

//=============================================================================
// 透明
//=============================================================================
void CScene3D::SetAlpha(bool bAlpha)
{
	m_bAlpha = bAlpha;
}

//=============================================================================
// アルファテストの値
//=============================================================================
void CScene3D::SetAlphaNum(int nAlphaNum)
{
	m_nAlphaTestNum = nAlphaNum;
}

//=============================================================================
// 加算合成の設定
//=============================================================================
void CScene3D::SetBlend(bool bBlend)
{
	m_bBlend = bBlend;
}

//=============================================================================
// 逆行列の設定
//=============================================================================
void CScene3D::SetInverse(bool bInverse)
{
	m_bInverse = bInverse;
}