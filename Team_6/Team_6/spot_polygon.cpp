//=============================================================================
//
// スポットポリゴン [spot_polygon.cpp]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "spot_polygon.h"
#include "manager.h"
#include "renderer.h"
#include "collision.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define SPOT_SIZE D3DXVECTOR3(100.0f, 0.0f, 100.0f)	//サイズ
#define ALPHA_RATE (0.025f)	//アルファ値の係数
#define MAX_ALPHA (1.0f)	//アルファの最大値
#define MIN_ALPHA (0.0f)	//アルファの最低値

//=============================================================================
//コンストラクタ
//=============================================================================
CSpotPolygon::CSpotPolygon(PRIORITY Priority) : CScene3D(Priority)
{
	m_eFlashing = FLASHING_NONE;
	m_bIsDraw = true;
	m_nNumber = 0;
}

//=============================================================================
//デストラクタ
//=============================================================================
CSpotPolygon::~CSpotPolygon()
{
}

//=============================================================================
//クリエイト処理
//=============================================================================
CSpotPolygon * CSpotPolygon::Create(D3DXVECTOR3 pos, int nNumber)
{
	CSpotPolygon *pSpotPolgon;

	//インスタンス生成
	pSpotPolgon = new CSpotPolygon;

	if (pSpotPolgon)
	{
		//初期化
		pSpotPolgon->Init(pos, SPOT_SIZE);

		//番号の設定
		pSpotPolgon->SetNumber(nNumber);

		return pSpotPolgon;
	}
	return nullptr;
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CSpotPolygon::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//基底の初期化
	CScene3D::Init(pos, size);

	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CSpotPolygon::Uninit(void)
{
	//基底の終了
	CScene3D::Uninit();
}

//=============================================================================
//更新処理
//=============================================================================
void CSpotPolygon::Update(void)
{
	//基底の更新
	CScene3D::Update();

	//点滅処理
	Flasing();
}

//=============================================================================
//描画処理
//=============================================================================
void CSpotPolygon::Draw(void)
{
	if (m_bIsDraw)
	{
		// デバイス情報取得
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		//ライティングの影響を受けないようにする
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		//アルファテストを行う
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		//基底の描画
		CScene3D::Draw();

		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		//ライティングの影響を受けないようにする
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}

//=============================================================================
//点滅開始
//=============================================================================
void CSpotPolygon::SetFlashing(void)
{
	if (m_eFlashing == FLASHING_NONE)
	{
		m_eFlashing = FLASHING_SUB;
	}
}

//=============================================================================
//点滅終了
//=============================================================================
void CSpotPolygon::EndFlashing(void)
{
	if (m_eFlashing != FLASHING_NONE)
	{
		m_eFlashing = FLASHING_NONE;

		//色の取得
		D3DXCOLOR col = GetColor();

		//アルファ値を最大に修正
		col.a = MAX_ALPHA;
		SetColor(col);
	}
}

//=============================================================================
//点滅処理
//=============================================================================
void CSpotPolygon::Flasing(void)
{
	if (m_eFlashing != FLASHING_NONE)
	{
		// 色の情報
		D3DXCOLOR col = GetColor();

		if (m_eFlashing == FLASHING_ADD)
		{
			//アルファの加算
			col.a += ALPHA_RATE;

			//最大値を超えた
			if (col.a >= MAX_ALPHA)
			{
				//最大に修正し、点滅しないい状態にする
				col.a = MAX_ALPHA;
				m_eFlashing = FLASHING_NONE;
			}
		}
		else if (m_eFlashing == FLASHING_SUB)
		{
			//アルファ値の減算
			col.a -= ALPHA_RATE;

			//最低値を超えた
			if (col.a <= MIN_ALPHA)
			{
				//最低値に修正し、加算状態にする
				col.a = MIN_ALPHA;
				m_eFlashing = FLASHING_ADD;
			}
		}

		//色の設定
		SetColor(col);
	}
}
