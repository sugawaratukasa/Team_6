//******************************************************************************
// パーティクル[particle.cpp]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "resource_manager.h"
#include "particle.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define RANDOM_POS_MUT	(10)															// 10倍
#define MUT				(2)																// ２倍
#define ROT				(D3DXVECTOR3(0.0f,0.0f,0.0f))									// 向き
#define MIN_COL			(0.0f)															// 色の最小値
#define MIN_LIFE		(0)																// ライフの最小値
#define MIN_SCALE		(0.0f)															// 拡大率の最小値
#define DEVIDE_SIZE		(10)															// サイズ除算
#define ROT_RANDOM		(360)															// 向きのランダム値
#define POS				(D3DXVECTOR3(pos.x,pos.y + m_ParticleInfo.size.x / 2 ,pos.z))	// 位置
//******************************************************************************
// コンストラクタ
//******************************************************************************
CParticle::CParticle(PRIORITY Priority) : CBillboard(Priority)
{
	m_ParticleInfo = {};
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CParticle::~CParticle()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CParticle *CParticle::Create(D3DXVECTOR3 pos, CParticle_Manager::TYPE Type)
{
	// CParticleのポインタ
	CParticle *pParticle = nullptr;

	// nullptrの場合
	if (pParticle == nullptr)
	{
		// メモリ確保
		pParticle = new CParticle;

		// NULLでない場合
		if (pParticle != nullptr)
		{
			// 初期化
			pParticle->Init(pos, Type);
		}
	}
	// ポインタを返す
	return pParticle;
}

//******************************************************************************
// 初期化
//******************************************************************************
HRESULT CParticle::Init(D3DXVECTOR3 pos, CParticle_Manager::TYPE Type)
{
	// パーティクルマネージャー取得
	CParticle_Manager *pParticle_Manager = CManager::GetParticle_Manager();

	// 情報取得
	m_ParticleInfo = pParticle_Manager->GetInfo(Type);

	// 初期化
 	CBillboard::Init(POS, m_ParticleInfo.size);

	// サイズ設定
	SetSize(m_ParticleInfo.size);

	// サイズ設定
	SetRot(ROT);

	// セットアルファ
	SetAlphaNum(m_ParticleInfo.nAlpha);

	// !nullcheck
	if (pParticle_Manager != nullptr)
	{
		// falseの場合
		if (m_ParticleInfo.bTexRandom == false)
		{
			// テクスチャ受け渡し
			BindTexture(pParticle_Manager->GetTexture(m_ParticleInfo.nTexNum));
		}
		// trueの場合
		if (m_ParticleInfo.bTexRandom == true)
		{
			// テクスチャランダム
			int nTexNum = m_ParticleInfo.nMinTex_RandomNum + (int)(rand() * (m_ParticleInfo.nMaxTex_RandomNum - m_ParticleInfo.nMinTex_RandomNum + 1.0f) / (1.0f + RAND_MAX));

			// テクスチャ受け渡し
			BindTexture(pParticle_Manager->GetTexture(nTexNum));
		}
	}

	// trueの場合
	if (m_ParticleInfo.bColorRandom == true)
	{
		// 色ランダム
		int nColor_R = (rand() % m_ParticleInfo.RGB.nR);
		int nColor_G = (rand() % m_ParticleInfo.RGB.nG);
		int nColor_B = (rand() % m_ParticleInfo.RGB.nB);

		D3DXCOLOR col = D3DCOLOR_RGBA(nColor_R, nColor_G, nColor_B, 255);

		// 色設定
		SetColor(col);
	}

	// falseの場合
	if (m_ParticleInfo.bColorRandom == false)
	{
		// 色設定
		SetColor(m_ParticleInfo.color);
	}

	// trueの場合
	if (m_ParticleInfo.bRotRandom == true)
	{
		D3DXVECTOR3 rot = ZeroVector3;

		// 向きランダム
		rot.z = float(rand() % ROT_RANDOM);

		// ラジアン変換
		rot = D3DXToRadian(rot);

		// 向き設定
		SetRot(rot);
	}
	// trueの場合
	if (m_ParticleInfo.bRandomSize == true)
	{
		// サイズ
		D3DXVECTOR3 size = ZeroVector3;

		// サイズをランダム
		float fRandomSize = float(rand() % (int)m_ParticleInfo.fRandom_Max_Size + (int)m_ParticleInfo.fRandom_Min_Size);

		// サイズを設定
		size.x = fRandomSize;

		// サイズを設定
		size.y = fRandomSize;

		// サイズ設定
		SetSize(size);
	}

	// trueの場合
	if (m_ParticleInfo.bRandomPos == true)
	{
		// 位置取得
		D3DXVECTOR3 pos = GetPos();

		// 位置
		D3DXVECTOR3 Random_pos = ZeroVector3;

		// 位置ランダム
		Random_pos.x = float(rand() % (int)m_ParticleInfo.Random_pos.x *RANDOM_POS_MUT * MUT - (int)m_ParticleInfo.Random_pos.x *RANDOM_POS_MUT / MUT);

		// 除算
		Random_pos.x = Random_pos.x / RANDOM_POS_MUT;

		// yが0より大きい場合
		if (m_ParticleInfo.Random_pos.y > ZERO_FLOAT)
		{
			// 位置ランダム
			Random_pos.y = float(rand() % (int)m_ParticleInfo.Random_pos.y * RANDOM_POS_MUT);

			// 除算
			Random_pos.y = Random_pos.y / RANDOM_POS_MUT;
		}
		// 位置ランダム
		pos += Random_pos;

		// 位置設定
		SetPosition(pos);
	}

	// 0.0f出ない場合
	if (m_ParticleInfo.fAngle != 0.0f)
	{
		// 角度ランダム
		m_ParticleInfo.fAngle = float(rand() % (int)m_ParticleInfo.fAngle);

		// 角度取得
		m_ParticleInfo.Angle.x = m_ParticleInfo.fAngle;
		m_ParticleInfo.Angle.y = m_ParticleInfo.fAngle;
		m_ParticleInfo.Angle.z = m_ParticleInfo.fAngle;
	}

	// 加算合成を使用する場合
	if (m_ParticleInfo.bAlpha_Blend == true)
	{
		SetBlend(true);
	}
	return S_OK;
}

//******************************************************************************
// 終了
//******************************************************************************
void CParticle::Uninit(void)
{
	// 終了
	CBillboard::Uninit();
}

//******************************************************************************
// 更新
//******************************************************************************
void CParticle::Update(void)
{
	// 更新
	CBillboard::Update();

	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// 色取得
	D3DXCOLOR col = GetColor();

	// 拡大率取得
	float fScale = GetScale();

	// 角度加算
	m_ParticleInfo.Angle.x += m_ParticleInfo.AddAngle.x;
	m_ParticleInfo.Angle.y += m_ParticleInfo.AddAngle.y;
	m_ParticleInfo.Angle.z += m_ParticleInfo.AddAngle.z;

	// ライフを使用する場合
	if (m_ParticleInfo.bLife == true)
	{
		// デクリメント
		m_ParticleInfo.nLife--;

		// ライフが0以下の場合
		if (m_ParticleInfo.nLife <= MIN_LIFE)
		{
			// 終了
			Uninit();
			return;
		}
	}
	// 拡大率加算が使用状態なら
	if (m_ParticleInfo.bAddScale == true)
	{
		// 拡大率加算
		fScale += m_ParticleInfo.fAddScale;

		// 拡大率が0.0f以下の場合
		if (fScale <= MIN_SCALE)
		{
			// 終了
			Uninit();
			return;
		}
	}
	// 色減算を使用する場合
	if (m_ParticleInfo.bSubColor == true)
	{
		// 減算
		col -= m_ParticleInfo.SubColor;

		// 色設定
		SetColor(col);

		// α値が0.0f以下の場合
		if (col.a <= MIN_COL)
		{
			// 終了
			Uninit();
			return;
		}
	}

	// 拡大率設定
	SetScale(fScale);

	// サイズ設定
	SetSize(size);

	// 位置更新
	pos.x += cosf(D3DXToRadian(m_ParticleInfo.Angle.x))*m_ParticleInfo.move.x;
	pos.y += sinf(D3DXToRadian(m_ParticleInfo.Angle.y))*m_ParticleInfo.move.y;
	pos.z += sinf(D3DXToRadian(m_ParticleInfo.Angle.z))*m_ParticleInfo.move.z;

	SetPosition(pos);
}

//******************************************************************************
// 描画
//******************************************************************************
void CParticle::Draw(void)
{
	// 描画
	CBillboard::Draw();
}