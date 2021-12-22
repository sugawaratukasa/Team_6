//=============================================================================
//
// OBB���� [obb.cpp]
// Author : �R�c�ˑ�
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "obb.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CObb::CObb()
{
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CObb::~CObb()
{
}

//=============================================================================
//�N���G�C�g����
//=============================================================================
CObb * CObb::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const LPD3DXMESH pMesh)
{
	CObb *pObb = nullptr;

	//�C���X�^���X����
	pObb = new CObb;

	if (pObb)
	{
		//������
		if (FAILED(pObb->Init(pos, rot, pMesh)))
		{
			pObb->Uninit();

			pObb = nullptr;
		}
	}

	return pObb;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CObb::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const LPD3DXMESH pMesh)
{
	D3DXMATRIX mtxRot;	//��]�}�g���b�N�X

	D3DXVECTOR3 max = D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f);
	D3DXVECTOR3 min = D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f);

	if (pMesh)
	{
		MESH_VERTEX *pMeshVer = nullptr;

		//���b�V���̒��_�o�b�t�@�̃��b�N
		pMesh->LockVertexBuffer(0, (void**)&pMeshVer);

		//���b�V���̐����擾
		DWORD wdMeshNum = pMesh->GetNumVertices();

		for (int nCntMesh = 0; nCntMesh < (int)wdMeshNum; nCntMesh++)
		{
			D3DXVECTOR3 pos = pMeshVer[nCntMesh].pos;

			if (pos.x < min.x)min.x = pos.x;
			if (pos.x > max.x)max.x = pos.x;
			if (pos.y < min.y)min.y = pos.y;
			if (pos.y > max.y)max.y = pos.y;
			if (pos.z < min.z)min.z = pos.z;
			if (pos.z > max.z)max.z = pos.z;
		}

		//���b�V���̒��_�o�b�t�@�̃A�����b�N
		pMesh->UnlockVertexBuffer();

		//���S�ʒu�̎擾
		m_obb.Center = (min + max) / DIVIDE_2 + pos;

		//���������]�x�N�g�����쐬
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);

		//�e�ʂ̕�������]�x�N�g������擾
		m_obb.Dir[0] = D3DXVECTOR3(mtxRot._11, mtxRot._12, mtxRot._13);
		m_obb.Dir[1] = D3DXVECTOR3(mtxRot._21, mtxRot._22, mtxRot._23);
		m_obb.Dir[2] = D3DXVECTOR3(mtxRot._31, mtxRot._32, mtxRot._33);

		//�����̎擾(�����͔����̐�Βl�Ƃ���)
		m_obb.size.x = fabsf(max.x - min.x) / DIVIDE_2;
		m_obb.size.y = fabsf(max.y - min.y) / DIVIDE_2;
		m_obb.size.z = fabsf(max.z - min.z) / DIVIDE_2;

		return S_OK;
	}

	return E_FAIL;
}

//=============================================================================
//�I������
//=============================================================================
void CObb::Uninit(void)
{
	delete this;
}