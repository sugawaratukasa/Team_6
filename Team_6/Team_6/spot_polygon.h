#ifndef _SPOT_POLYGON_H_
#define _SPOT_POLYGON_H_
//=============================================================================
//
// �X�|�b�g�|���S���w�b�_�[ [spot_polygon.h]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "scene3d.h"

//=============================================================================
//�X�|�b�g�|���S���N���X
//=============================================================================
class CSpotPolygon :public CScene3D
{
public:
	//=========================================================================
	//�_�ŏ��̗�
	//=========================================================================
	enum FLASHING
	{
		FLASHING_NONE = 0,	//�������Ȃ�
		FLASHING_ADD,		//���Z
		FLASHING_SUB,		//���Z
		FLASHING_MAX,
	};

	//=========================================================================
	//�����o�֐��錾
	//=========================================================================
	CSpotPolygon(PRIORITY Priority = PRIORITY_FADE);	//�R���X�g���N�^
	~CSpotPolygon();									//�f�X�g���N�^

	static CSpotPolygon *Create(D3DXVECTOR3 pos, int nNumber);	//�N���G�C�g

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//����������
	void Uninit(void);									//�I������
	void Update(void);									//�X�V����
	void Draw(void);									//�`�揈��
	void SetFlashing(void);								//�_�ŊJ�n
	void EndFlashing(void);								//�_�ŏI��
	
	//public�Z�b�^�[
	void SetIsDraw(const bool bIsDraw) { m_bIsDraw = bIsDraw; }	//�`��t���O�̐ݒ�
	void SetNumber(int nNumber) { m_nNumber = nNumber; }		//�ԍ��̐ݒ�

private:
	void Flasing(void);		//�_�ŏ���

	//=========================================================================
	//�����o�ϐ��錾
	//=========================================================================
	FLASHING m_eFlashing;	//�_�ŏ��
	bool m_bIsDraw;			//�`�悷�邩�ǂ���
	int m_nNumber;			//�ԍ�
};
#endif // !_SPOT_POLYGON_H_
