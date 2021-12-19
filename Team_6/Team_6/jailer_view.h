#ifndef _JAILER_H_
#define _JAILER_H_
//=============================================================================
//
// �Ŏ�̎������� [jailer_view.h]
// Author : �R�c�ˑ�
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "fan3d.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define CoordinateAxesNum (3)	//���W���̐��iXYZ��3�j

//=============================================================================
//�Ŏ�̎����N���X
//=============================================================================
class CJailerView :public CFan3D
{
public:
	//=========================================================================
	//�����̃f�[�^�\����
	//=========================================================================
	struct ViewData
	{
		D3DXVECTOR3 fanToPlayer;	//���v���C���[�܂ł̃x�N�g��
		D3DXVECTOR3 playerPos;		//�v���C���[�̈ʒu
		float fLength;				//����
		int nNumber;				//�ԍ�
	};

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
	CJailerView();	//�R���X�g���N�^
	~CJailerView();	//�f�X�g���N�^

	static CJailerView *Create(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rRot,
		const int& rnPolygonNum, const D3DXCOLOR& rCol);	//�N���G�C�g����

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//����������
	void Uninit(void);								//�I������
	void Update(void);								//�X�V����
	void Draw(void);								//�`�揈��
	
	void ResetDetection(void) { m_bIsDetection = false; }		//���o���̃��Z�b�g
	bool GetIsDetection(void)const { return m_bIsDetection; }	//���o���̎擾
	D3DXVECTOR3 GetDetectionPos(void) { return m_detectedPos; }	//���o�����ʒu�̎擾
	void CautionJailer(const bool bIsCaution);					//�x�����̒����ύX

private:
	void DetectionPlayer(void);										//�v���C���[�̌��o
	bool MapCollision(const D3DXVECTOR3 playerPos);					//�}�b�v�Ƃ̔���
	void ChangeColor(void);											//�F�̕ύX����
	HRESULT CreateOBBData(OBB_DATA *pOBB, const D3DXVECTOR3 pos, 
		const D3DXVECTOR3 rot, const LPD3DXMESH pMesh);				//OBB���̍쐬

	//=========================================================================
	//�����o�ϐ��錾
	//=========================================================================
	bool m_bIsDetection;		//���o�������ǂ���
	D3DXVECTOR3 m_detectedPos;	//���o�����ʒu
};
#endif // !_JAILER_H_
