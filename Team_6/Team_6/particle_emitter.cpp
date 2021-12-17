//===============================================================================
// パーティクルエミッター [particle_emitter.cpp]
// Author: Sugawara Tsukasa
//===============================================================================
//===============================================================================
// インクルードファイル
// Author: Sugawara Tsukasa
//===============================================================================
#include "particle_emitter.h"
#include "particle.h"
#include "manager.h"
//===============================================================================
// コンストラクタ
// Author: Sugawara Tsukasa
//===============================================================================
CParticle_Emitter::CParticle_Emitter(PRIORITY Priority)
{
	m_pos			= ZeroVector3;
	m_Type			= CParticle_Manager::TYPE_NONE;
	m_nCreateCnt	= ZERO_INT;
}
//===============================================================================
// デストラクタ
// Author: Sugawara Tsukasa
//===============================================================================
CParticle_Emitter::~CParticle_Emitter()
{
}
//===============================================================================
// 生成処理関数
// Author: Sugawara Tsukasa
//===============================================================================
CParticle_Emitter * CParticle_Emitter::Create(D3DXVECTOR3 pos, CParticle_Manager::TYPE Type)
{
	// CParticle_Emitterのポインタ
	CParticle_Emitter *pParticle_Emitter = nullptr;

	// nullcheck
	if (pParticle_Emitter == nullptr)
	{
		// メモリ確保
		pParticle_Emitter = new CParticle_Emitter;

		// !nullcheck
		if (pParticle_Emitter != nullptr)
		{
			// 初期化
			pParticle_Emitter->Init(pos, ZeroVector3);

			// タイプ代入
			pParticle_Emitter->m_Type = Type;
		}
	}

	// ポインタを返す
	return pParticle_Emitter;
}
//===============================================================================
// 初期化処理関数
// Author: Sugawara Tsukasa
//===============================================================================
HRESULT CParticle_Emitter::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 位置代入
	m_pos = pos;
	return S_OK;
}
//===============================================================================
// 終了処理関数
// Author: Sugawara Tsukasa
//===============================================================================
void CParticle_Emitter::Uninit(void)
{
	// 破棄処理
	Release();
}
//===============================================================================
// 更新処理関数
// Author: Sugawara Tsukasa
//===============================================================================
void CParticle_Emitter::Update(void)
{
	// パーティクル情報取得
	CParticle_Manager::INFO Info = CManager::GetParticle_Manager()->GetInfo(m_Type);

	// インクリメント
	m_nCreateCnt++;

	// 余り0の場合
	if (m_nCreateCnt %Info.nCreateCnt == ZERO_INT)
	{
		// 生成関数
		CParticle::Create(m_pos, m_Type);
	}
}
//===============================================================================
// 描画処理関数
// Author: Sugawara Tsukasa
//===============================================================================
void CParticle_Emitter::Draw(void)
{
}