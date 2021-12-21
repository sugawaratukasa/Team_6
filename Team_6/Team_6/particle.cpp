//******************************************************************************
// �p�[�e�B�N��[particle.cpp]
// Author : �ǌ��@�i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "resource_manager.h"
#include "particle.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define RANDOM_POS_MUT	(10)															// 10�{
#define MUT				(2)																// �Q�{
#define ROT				(D3DXVECTOR3(0.0f,0.0f,0.0f))									// ����
#define MIN_COL			(0.0f)															// �F�̍ŏ��l
#define MIN_LIFE		(0)																// ���C�t�̍ŏ��l
#define MIN_SCALE		(0.0f)															// �g�嗦�̍ŏ��l
#define DEVIDE_SIZE		(10)															// �T�C�Y���Z
#define ROT_RANDOM		(360)															// �����̃����_���l
#define POS				(D3DXVECTOR3(pos.x,pos.y + m_ParticleInfo.size.x / 2 ,pos.z))	// �ʒu
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CParticle::CParticle(PRIORITY Priority) : CBillboard(Priority)
{
	m_ParticleInfo = {};
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CParticle::~CParticle()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CParticle *CParticle::Create(D3DXVECTOR3 pos, CParticle_Manager::TYPE Type)
{
	// CParticle�̃|�C���^
	CParticle *pParticle = nullptr;

	// nullptr�̏ꍇ
	if (pParticle == nullptr)
	{
		// �������m��
		pParticle = new CParticle;

		// NULL�łȂ��ꍇ
		if (pParticle != nullptr)
		{
			// ������
			pParticle->Init(pos, Type);
		}
	}
	// �|�C���^��Ԃ�
	return pParticle;
}

//******************************************************************************
// ������
//******************************************************************************
HRESULT CParticle::Init(D3DXVECTOR3 pos, CParticle_Manager::TYPE Type)
{
	// �p�[�e�B�N���}�l�[�W���[�擾
	CParticle_Manager *pParticle_Manager = CManager::GetParticle_Manager();

	// ���擾
	m_ParticleInfo = pParticle_Manager->GetInfo(Type);

	// ������
 	CBillboard::Init(POS, m_ParticleInfo.size);

	// �T�C�Y�ݒ�
	SetSize(m_ParticleInfo.size);

	// �T�C�Y�ݒ�
	SetRot(ROT);

	// �Z�b�g�A���t�@
	SetAlphaNum(m_ParticleInfo.nAlpha);

	// !nullcheck
	if (pParticle_Manager != nullptr)
	{
		// false�̏ꍇ
		if (m_ParticleInfo.bTexRandom == false)
		{
			// �e�N�X�`���󂯓n��
			BindTexture(pParticle_Manager->GetTexture(m_ParticleInfo.nTexNum));
		}
		// true�̏ꍇ
		if (m_ParticleInfo.bTexRandom == true)
		{
			// �e�N�X�`�������_��
			int nTexNum = m_ParticleInfo.nMinTex_RandomNum + (int)(rand() * (m_ParticleInfo.nMaxTex_RandomNum - m_ParticleInfo.nMinTex_RandomNum + 1.0f) / (1.0f + RAND_MAX));

			// �e�N�X�`���󂯓n��
			BindTexture(pParticle_Manager->GetTexture(nTexNum));
		}
	}

	// true�̏ꍇ
	if (m_ParticleInfo.bColorRandom == true)
	{
		// �F�����_��
		int nColor_R = (rand() % m_ParticleInfo.RGB.nR);
		int nColor_G = (rand() % m_ParticleInfo.RGB.nG);
		int nColor_B = (rand() % m_ParticleInfo.RGB.nB);

		D3DXCOLOR col = D3DCOLOR_RGBA(nColor_R, nColor_G, nColor_B, 255);

		// �F�ݒ�
		SetColor(col);
	}

	// false�̏ꍇ
	if (m_ParticleInfo.bColorRandom == false)
	{
		// �F�ݒ�
		SetColor(m_ParticleInfo.color);
	}

	// true�̏ꍇ
	if (m_ParticleInfo.bRotRandom == true)
	{
		D3DXVECTOR3 rot = ZeroVector3;

		// ���������_��
		rot.z = float(rand() % ROT_RANDOM);

		// ���W�A���ϊ�
		rot = D3DXToRadian(rot);

		// �����ݒ�
		SetRot(rot);
	}
	// true�̏ꍇ
	if (m_ParticleInfo.bRandomSize == true)
	{
		// �T�C�Y
		D3DXVECTOR3 size = ZeroVector3;

		// �T�C�Y�������_��
		float fRandomSize = float(rand() % (int)m_ParticleInfo.fRandom_Max_Size + (int)m_ParticleInfo.fRandom_Min_Size);

		// �T�C�Y��ݒ�
		size.x = fRandomSize;

		// �T�C�Y��ݒ�
		size.y = fRandomSize;

		// �T�C�Y�ݒ�
		SetSize(size);
	}

	// true�̏ꍇ
	if (m_ParticleInfo.bRandomPos == true)
	{
		// �ʒu�擾
		D3DXVECTOR3 pos = GetPos();

		// �ʒu
		D3DXVECTOR3 Random_pos = ZeroVector3;

		// �ʒu�����_��
		Random_pos.x = float(rand() % (int)m_ParticleInfo.Random_pos.x *RANDOM_POS_MUT * MUT - (int)m_ParticleInfo.Random_pos.x *RANDOM_POS_MUT / MUT);

		// ���Z
		Random_pos.x = Random_pos.x / RANDOM_POS_MUT;

		// y��0���傫���ꍇ
		if (m_ParticleInfo.Random_pos.y > ZERO_FLOAT)
		{
			// �ʒu�����_��
			Random_pos.y = float(rand() % (int)m_ParticleInfo.Random_pos.y * RANDOM_POS_MUT);

			// ���Z
			Random_pos.y = Random_pos.y / RANDOM_POS_MUT;
		}
		// �ʒu�����_��
		pos += Random_pos;

		// �ʒu�ݒ�
		SetPosition(pos);
	}

	// 0.0f�o�Ȃ��ꍇ
	if (m_ParticleInfo.fAngle != 0.0f)
	{
		// �p�x�����_��
		m_ParticleInfo.fAngle = float(rand() % (int)m_ParticleInfo.fAngle);

		// �p�x�擾
		m_ParticleInfo.Angle.x = m_ParticleInfo.fAngle;
		m_ParticleInfo.Angle.y = m_ParticleInfo.fAngle;
		m_ParticleInfo.Angle.z = m_ParticleInfo.fAngle;
	}

	// ���Z�������g�p����ꍇ
	if (m_ParticleInfo.bAlpha_Blend == true)
	{
		SetBlend(true);
	}
	return S_OK;
}

//******************************************************************************
// �I��
//******************************************************************************
void CParticle::Uninit(void)
{
	// �I��
	CBillboard::Uninit();
}

//******************************************************************************
// �X�V
//******************************************************************************
void CParticle::Update(void)
{
	// �X�V
	CBillboard::Update();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// �F�擾
	D3DXCOLOR col = GetColor();

	// �g�嗦�擾
	float fScale = GetScale();

	// �p�x���Z
	m_ParticleInfo.Angle.x += m_ParticleInfo.AddAngle.x;
	m_ParticleInfo.Angle.y += m_ParticleInfo.AddAngle.y;
	m_ParticleInfo.Angle.z += m_ParticleInfo.AddAngle.z;

	// ���C�t���g�p����ꍇ
	if (m_ParticleInfo.bLife == true)
	{
		// �f�N�������g
		m_ParticleInfo.nLife--;

		// ���C�t��0�ȉ��̏ꍇ
		if (m_ParticleInfo.nLife <= MIN_LIFE)
		{
			// �I��
			Uninit();
			return;
		}
	}
	// �g�嗦���Z���g�p��ԂȂ�
	if (m_ParticleInfo.bAddScale == true)
	{
		// �g�嗦���Z
		fScale += m_ParticleInfo.fAddScale;

		// �g�嗦��0.0f�ȉ��̏ꍇ
		if (fScale <= MIN_SCALE)
		{
			// �I��
			Uninit();
			return;
		}
	}
	// �F���Z���g�p����ꍇ
	if (m_ParticleInfo.bSubColor == true)
	{
		// ���Z
		col -= m_ParticleInfo.SubColor;

		// �F�ݒ�
		SetColor(col);

		// ���l��0.0f�ȉ��̏ꍇ
		if (col.a <= MIN_COL)
		{
			// �I��
			Uninit();
			return;
		}
	}

	// �g�嗦�ݒ�
	SetScale(fScale);

	// �T�C�Y�ݒ�
	SetSize(size);

	// �ʒu�X�V
	pos.x += cosf(D3DXToRadian(m_ParticleInfo.Angle.x))*m_ParticleInfo.move.x;
	pos.y += sinf(D3DXToRadian(m_ParticleInfo.Angle.y))*m_ParticleInfo.move.y;
	pos.z += sinf(D3DXToRadian(m_ParticleInfo.Angle.z))*m_ParticleInfo.move.z;

	SetPosition(pos);
}

//******************************************************************************
// �`��
//******************************************************************************
void CParticle::Draw(void)
{
	// �`��
	CBillboard::Draw();
}