//******************************************************************************
// �p�[�e�B�N�� [ particle.h]
// Author : �ǌ� �i
//******************************************************************************
#ifndef _PARTICLE_H_
#define _PARTICLE_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "billboard.h"
#include "particle_manager.h"
//******************************************************************************
// �N���X
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

	CParticle_Manager::INFO m_ParticleInfo;	// �p�[�e�B�N�����
};
#endif