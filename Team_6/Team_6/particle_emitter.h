#ifndef _PARTICLE_EMITTER_H_
#define _PARTICLE_EMITTER_H_
//===============================================================================
// �p�[�e�B�N���G�~�b�^�[ [particle_emitter.h]
// Author: Sugawara Tsukasa
//===============================================================================
//===============================================================================
// �C���N���[�h�t�@�C��
// Author : SugawaraTsukasa
//===============================================================================
#include "scene.h"
#include "particle_manager.h"
//===============================================================================
// �p�[�e�B�N���}�l�[�W���[�N���X
// Author : SugawaraTsukasa
//===============================================================================
class CParticle_Emitter : public CScene
{
public:
	CParticle_Emitter(PRIORITY Priority = PRIORITY_FADE);
	virtual ~CParticle_Emitter();

	static CParticle_Emitter *Create(D3DXVECTOR3 pos, CParticle_Manager::TYPE Type);
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	//=======================================================
	// Set�֐�
	//=======================================================
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
private:
	D3DXVECTOR3 m_pos;				// �ʒu
	CParticle_Manager::TYPE m_Type;	// �^�C�v
	int m_nCreateCnt;				// �����J�E���g
};
#endif
