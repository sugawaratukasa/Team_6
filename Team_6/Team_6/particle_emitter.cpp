//===============================================================================
// �p�[�e�B�N���G�~�b�^�[ [particle_emitter.cpp]
// Author: Sugawara Tsukasa
//===============================================================================
//===============================================================================
// �C���N���[�h�t�@�C��
// Author: Sugawara Tsukasa
//===============================================================================
#include "particle_emitter.h"
#include "particle.h"
#include "manager.h"
//===============================================================================
// �R���X�g���N�^
// Author: Sugawara Tsukasa
//===============================================================================
CParticle_Emitter::CParticle_Emitter(PRIORITY Priority)
{
	m_pos			= ZeroVector3;
	m_Type			= CParticle_Manager::TYPE_NONE;
	m_nCreateCnt	= ZERO_INT;
}
//===============================================================================
// �f�X�g���N�^
// Author: Sugawara Tsukasa
//===============================================================================
CParticle_Emitter::~CParticle_Emitter()
{
}
//===============================================================================
// ���������֐�
// Author: Sugawara Tsukasa
//===============================================================================
CParticle_Emitter * CParticle_Emitter::Create(D3DXVECTOR3 pos, CParticle_Manager::TYPE Type)
{
	// CParticle_Emitter�̃|�C���^
	CParticle_Emitter *pParticle_Emitter = nullptr;

	// nullcheck
	if (pParticle_Emitter == nullptr)
	{
		// �������m��
		pParticle_Emitter = new CParticle_Emitter;

		// !nullcheck
		if (pParticle_Emitter != nullptr)
		{
			// ������
			pParticle_Emitter->Init(pos, ZeroVector3);

			// �^�C�v���
			pParticle_Emitter->m_Type = Type;
		}
	}

	// �|�C���^��Ԃ�
	return pParticle_Emitter;
}
//===============================================================================
// �����������֐�
// Author: Sugawara Tsukasa
//===============================================================================
HRESULT CParticle_Emitter::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �ʒu���
	m_pos = pos;
	return S_OK;
}
//===============================================================================
// �I�������֐�
// Author: Sugawara Tsukasa
//===============================================================================
void CParticle_Emitter::Uninit(void)
{
	// �j������
	Release();
}
//===============================================================================
// �X�V�����֐�
// Author: Sugawara Tsukasa
//===============================================================================
void CParticle_Emitter::Update(void)
{
	// �p�[�e�B�N�����擾
	CParticle_Manager::INFO Info = CManager::GetParticle_Manager()->GetInfo(m_Type);

	// �C���N�������g
	m_nCreateCnt++;

	// �]��0�̏ꍇ
	if (m_nCreateCnt %Info.nCreateCnt == ZERO_INT)
	{
		// �����֐�
		CParticle::Create(m_pos, m_Type);
	}
}
//===============================================================================
// �`�揈���֐�
// Author: Sugawara Tsukasa
//===============================================================================
void CParticle_Emitter::Draw(void)
{
}