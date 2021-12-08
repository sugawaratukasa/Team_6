//=============================================================================
//
// �X�|�b�g�|���S�� [spot_polygon.cpp]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "spot_polygon.h"
#include "manager.h"
#include "renderer.h"
#include "collision.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define SPOT_SIZE D3DXVECTOR3(100.0f, 0.0f, 100.0f)	//�T�C�Y
#define ALPHA_RATE (0.025f)	//�A���t�@�l�̌W��
#define MAX_ALPHA (1.0f)	//�A���t�@�̍ő�l
#define MIN_ALPHA (0.0f)	//�A���t�@�̍Œ�l

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CSpotPolygon::CSpotPolygon(PRIORITY Priority) : CScene3D(Priority)
{
	m_eFlashing = FLASHING_NONE;
	m_bIsDraw = true;
	m_nNumber = 0;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CSpotPolygon::~CSpotPolygon()
{
}

//=============================================================================
//�N���G�C�g����
//=============================================================================
CSpotPolygon * CSpotPolygon::Create(D3DXVECTOR3 pos, int nNumber)
{
	CSpotPolygon *pSpotPolgon;

	//�C���X�^���X����
	pSpotPolgon = new CSpotPolygon;

	if (pSpotPolgon)
	{
		//������
		pSpotPolgon->Init(pos, SPOT_SIZE);

		//�ԍ��̐ݒ�
		pSpotPolgon->SetNumber(nNumber);

		return pSpotPolgon;
	}
	return nullptr;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CSpotPolygon::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//���̏�����
	CScene3D::Init(pos, size);

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CSpotPolygon::Uninit(void)
{
	//���̏I��
	CScene3D::Uninit();
}

//=============================================================================
//�X�V����
//=============================================================================
void CSpotPolygon::Update(void)
{
	//���̍X�V
	CScene3D::Update();

	//�_�ŏ���
	Flasing();
}

//=============================================================================
//�`�揈��
//=============================================================================
void CSpotPolygon::Draw(void)
{
	if (m_bIsDraw)
	{
		// �f�o�C�X���擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		//���C�e�B���O�̉e�����󂯂Ȃ��悤�ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		//�A���t�@�e�X�g���s��
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		//���̕`��
		CScene3D::Draw();

		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		//���C�e�B���O�̉e�����󂯂Ȃ��悤�ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}

//=============================================================================
//�_�ŊJ�n
//=============================================================================
void CSpotPolygon::SetFlashing(void)
{
	if (m_eFlashing == FLASHING_NONE)
	{
		m_eFlashing = FLASHING_SUB;
	}
}

//=============================================================================
//�_�ŏI��
//=============================================================================
void CSpotPolygon::EndFlashing(void)
{
	if (m_eFlashing != FLASHING_NONE)
	{
		m_eFlashing = FLASHING_NONE;

		//�F�̎擾
		D3DXCOLOR col = GetColor();

		//�A���t�@�l���ő�ɏC��
		col.a = MAX_ALPHA;
		SetColor(col);
	}
}

//=============================================================================
//�_�ŏ���
//=============================================================================
void CSpotPolygon::Flasing(void)
{
	if (m_eFlashing != FLASHING_NONE)
	{
		// �F�̏��
		D3DXCOLOR col = GetColor();

		if (m_eFlashing == FLASHING_ADD)
		{
			//�A���t�@�̉��Z
			col.a += ALPHA_RATE;

			//�ő�l�𒴂���
			if (col.a >= MAX_ALPHA)
			{
				//�ő�ɏC�����A�_�ł��Ȃ�����Ԃɂ���
				col.a = MAX_ALPHA;
				m_eFlashing = FLASHING_NONE;
			}
		}
		else if (m_eFlashing == FLASHING_SUB)
		{
			//�A���t�@�l�̌��Z
			col.a -= ALPHA_RATE;

			//�Œ�l�𒴂���
			if (col.a <= MIN_ALPHA)
			{
				//�Œ�l�ɏC�����A���Z��Ԃɂ���
				col.a = MIN_ALPHA;
				m_eFlashing = FLASHING_ADD;
			}
		}

		//�F�̐ݒ�
		SetColor(col);
	}
}
