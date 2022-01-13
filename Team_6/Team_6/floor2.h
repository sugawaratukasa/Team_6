//=============================================================================
// �� [floor.h]
// Author : Sugawara Tsukasa
//=============================================================================
#ifndef _FLOOR2_H_
#define _FLOOR2_H_
//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "scene3D.h"
//=============================================================================
// �}�b�v�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CFloor2 : public CScene3D
{
public:
	CFloor2(PRIORITY Priority = PRIORITY_1);					// �R���X�g���N�^
	~CFloor2();													// �f�X�g���N�^
	static CFloor2 *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��
private:
};
#endif