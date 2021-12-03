#include "spot_polygon.h"
#include "manager.h"
#include "renderer.h"
#include "collision.h"
#define SPOT_SIZE D3DXVECTOR3(100.0f, 0.0f, 100.0f)

CSpotPolygon::CSpotPolygon(PRIORITY Priority) : CScene3D(Priority)
{
	m_eFlashing = FLASHING_NONE;
	m_bIsDraw = true;
	m_nNumber = 0;
}

CSpotPolygon::~CSpotPolygon()
{
}

CSpotPolygon * CSpotPolygon::Create(D3DXVECTOR3 pos, int nNumber)
{
	CSpotPolygon *pSpotPolgon;

	pSpotPolgon = new CSpotPolygon;

	if (pSpotPolgon)
	{
		pSpotPolgon->Init(pos, SPOT_SIZE);
		pSpotPolgon->SetNumber(nNumber);

		return pSpotPolgon;
	}
	return nullptr;
}

HRESULT CSpotPolygon::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene3D::Init(pos, size);
	return S_OK;
}

void CSpotPolygon::Uninit(void)
{
	CScene3D::Uninit();
}

void CSpotPolygon::Update(void)
{
	CScene3D::Update();

	Flasing();
}

void CSpotPolygon::Draw(void)
{
	if (m_bIsDraw)
	{
		// �f�o�C�X���擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		//���C�e�B���O�̉e�����󂯂Ȃ��悤�ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		CScene3D::Draw();

		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		//���C�e�B���O�̉e�����󂯂Ȃ��悤�ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}

void CSpotPolygon::SetFlashing(void)
{
	if (m_eFlashing == FLASHING_NONE)
	{
		m_eFlashing = FLASHING_SUB;
	}
}

void CSpotPolygon::EndFlashing(void)
{
	if (m_eFlashing != FLASHING_NONE)
	{
		m_eFlashing = FLASHING_NONE;

		D3DXCOLOR col = GetColor();

		col.a = 1.0f;
		SetColor(col);
	}
}



void CSpotPolygon::Flasing(void)
{
	if (m_eFlashing != FLASHING_NONE)
	{
		// �F�̏��
		D3DXCOLOR col = GetColor();

		if (m_eFlashing == FLASHING_ADD)
		{
			col.a += 0.25f;

			if (col.a >= 1.0f)
			{
				col.a = 1.0f;
				m_eFlashing = FLASHING_NONE;
			}
		}
		else if (m_eFlashing == FLASHING_SUB)
		{
			col.a -= 0.25f;

			if (col.a <= 0.0f)
			{
				col.a = 0.0f;
				m_eFlashing = FLASHING_ADD;
			}
		}

		SetColor(col);

		//LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();	// �o�b�t�@�擾
		//VERTEX_3D*pVtx;	//���_���ւ̃|�C���^

		//				//���_�f�[�^�͈͂����b�N���A���_�o�b�t�@�ւ̃|�C���^������
		//pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
		//{
		//	//���_�J���[�̐ݒ�i0�`255�̐��l�Őݒ�j
		//	pVtx[nCount].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
		//}

		////���_�f�[�^���A�����b�N
		//pVtxBuff->Unlock();
	}
}
