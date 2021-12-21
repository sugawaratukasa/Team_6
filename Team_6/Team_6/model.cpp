//=============================================================================
//
// ���f���N���X���� [model.cpp]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "game.h"
#include "xfile.h"

#include "collision.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define ALPHA_NUM_MAX		(1.0f)		// �����x�̍ő吔

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CModel::CModel(PRIORITY Priority) : CScene(Priority)
{
	m_pos = ZeroVector3;
	m_rot = ZeroVector3;
	m_move = ZeroVector3;
	m_size = ZeroVector3;
	m_scale = MODEL_DEFAULT_SIZE;
	m_apTexture = nullptr;
	m_nTexPattern = 0;
	m_nLife = 0;
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fAlphaNum = 0.0f;

	m_State = STATE_NORMAL;
	m_RayData = { ZERO_FLOAT,ZERO_FLOAT,ZERO_INT };
	m_bDraw = true;
	m_Model.dwNumMat = ZERO_INT;
	m_Model.pBuffMat = nullptr;
	m_Model.pMesh = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CModel::~CModel()
{
}

//=============================================================================
// �N���G�C�g����
//=============================================================================
CModel * CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//���f���N���X�̃|�C���^�ϐ�
	CModel *pModel = nullptr;

	//�������m��
	pModel = new CModel;

	// nullcheck
	if (pModel != nullptr)
	{
		//�����������Ăяo��
		pModel->Init(pos, rot);
	}
	//�������m�ۂɎ��s�����Ƃ�
	else
	{
		return nullptr;
	}

	return pModel;
}

//=============================================================================
//���f���N���X�̏���������
//=============================================================================
HRESULT CModel::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �ʒu�̏�����
	m_pos = pos;

	// �T�C�Y������
	m_rot = rot;

	return S_OK;
}

//=============================================================================
//���f���N���X�̏I������
//=============================================================================
void CModel::Uninit(void)
{
	//�I�u�W�F�N�g�̔j��
	Release();

}

//=============================================================================
// ���f���N���X�̍X�V����
//=============================================================================
void CModel::Update(void)
{
	// ���������炷
	m_nLife--;

	// ���W�̍X�V
	m_pos += m_move;
}

//=============================================================================
// ���f���N���X�̕`�揈��
//=============================================================================
void CModel::Draw(void)
{
	if (m_bDraw)
	{
		//�f�o�C�X���̎擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		D3DXMATRIX mtxRot, mtxTrans, mtxScale;
		D3DMATERIAL9 matDef;					//���݂̃}�e���A���ێ��p


		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		// �g�嗦�𔽉f
		D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//���݂̃}�e���A�����擾����
		pDevice->GetMaterial(&matDef);

		D3DXMATERIAL*pMat;		//�}�e���A���f�[�^�ւ̃|�C���^

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)m_Model.pBuffMat->GetBufferPointer();


		for (int nCntMat = 0; nCntMat < (int)m_Model.dwNumMat; nCntMat++)
		{
			//�}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
			pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			if (m_Model.apTexture[nCntMat] != nullptr)
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, m_Model.apTexture[nCntMat]);
			}
			else
			{
				pDevice->SetTexture(0, nullptr);
			}

			//���f���p�[�c�̕`��
			m_Model.pMesh->DrawSubset(nCntMat);

			pDevice->SetTexture(0, nullptr);
		}


		//�ێ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);

	}
}

//=============================================================================

// ���f�����̐ݒ�
//=============================================================================
void CModel::BindModel(CXfile::MODEL model)
{
	m_Model.pMesh = model.pMesh;
	m_Model.pBuffMat = model.pBuffMat;
	m_Model.dwNumMat = model.dwNumMat;
	m_Model.apTexture = model.apTexture;
}
//=============================================================================

// �����x�̌��Z
//=============================================================================
void CModel::SubAlpha(float fAlpha)
{
	if (m_fAlphaNum < ALPHA_NUM_MAX)
	{
		m_fAlphaNum += fAlpha;
	}
	else
	{
		m_fAlphaNum = ALPHA_NUM_MAX;
	}
}