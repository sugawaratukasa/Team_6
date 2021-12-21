//=============================================================================
// ���߂�p�̍����|���S�� [black_fill_polygon.h]
// Author : Sugawara Tsukasa
//=============================================================================
#ifndef _BLACK_FILL_POLYGON_H_
#define _BLACK_FILL_POLYGON_H_
//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "scene3D.h"
//=============================================================================
// �}�b�v�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CBlack_Fill_Polygon : public CScene3D
{
public:
	CBlack_Fill_Polygon(PRIORITY Priority = PRIORITY_1);					// �R���X�g���N�^
	~CBlack_Fill_Polygon();													// �f�X�g���N�^
	static CBlack_Fill_Polygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);						// ����������
	void Uninit(void);														// �I������
	void Update(void);														// �X�V����
	void Draw(void);														// �`�揈��
private:
};
#endif