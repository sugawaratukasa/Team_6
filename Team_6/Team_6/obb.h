#ifndef _OBB_H_
#define _OBB_H_
//=============================================================================
//
// OBB���� [obb.h]
// Author : �R�c�ˑ�
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define CoordinateAxesNum (3)	//���W���̐��iXYZ��3�j

//=============================================================================
//OBB�N���X
//=============================================================================
class CObb
{
public:
	//=========================================================================
	//OBB�̃f�[�^�\����
	//=========================================================================
	struct OBB_DATA
	{
		D3DXVECTOR3 Center;					//���S�ʒu
		D3DXVECTOR3 Dir[CoordinateAxesNum];	//�e���̕����x�N�g��
		D3DXVECTOR3 size;					//�e���W���ւ̃T�C�Y�i���S�_���甼���̒l�j
	};

	//=========================================================================
	//���b�V���̒��_�\����
	//=========================================================================
	struct MESH_VERTEX
	{
		D3DXVECTOR3 pos;	//�ʒu
		D3DXVECTOR3 nor;	//�@���x�N�g��
		float tu;
		float tv;
	};
	//=========================================================================
	//�����o�֐��錾
	//=========================================================================
	CObb();
	~CObb();

	static CObb*Create(const D3DXVECTOR3 pos,
		const D3DXVECTOR3 rot, const LPD3DXMESH pMesh);

	HRESULT Init(const D3DXVECTOR3 pos,
		const D3DXVECTOR3 rot, const LPD3DXMESH pMesh);

	void Uninit(void);

	OBB_DATA& GetObbData(void) { return m_obb; }
	D3DXVECTOR3 GetCenterPos(void) { return m_obb.Center; }
	D3DXVECTOR3 GetDir(const int nCntNum) { return m_obb.Dir[nCntNum]; }
	D3DXVECTOR3 GetSize(void) { return m_obb.size; }

private:
	//=========================================================================
	//�����o�ϐ��錾
	//=========================================================================
	OBB_DATA m_obb;
};


#endif // !_JAILER_H_