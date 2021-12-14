//******************************************************************************
// パーティクル [ particle.h]
// Author : 管原 司
//******************************************************************************
#ifndef _PARTICLE_H_
#define _PARTICLE_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "billboard.h"
#include "particle_manager.h"
//******************************************************************************
// クラス
//******************************************************************************
class CParticle : public CBillboard
{
public:
	CParticle(PRIORITY Priority = PRIORITY_FADE);
	virtual ~CParticle();
	static CParticle *Create(D3DXVECTOR3 pos, CParticle_Manager::TYPE Type);
	virtual HRESULT Init(D3DXVECTOR3 pos, CParticle_Manager::TYPE Type);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
private:

	CParticle_Manager::INFO m_ParticleInfo;	// パーティクル情報
};
#endif