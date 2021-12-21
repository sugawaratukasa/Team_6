#ifndef _OBJECT_IRON_WINDOW_WALL_H_
#define _OBJECT_IRON_WINDOW_WALL_H_
//=============================================================================
// �S���̕� [object_iron_window_wall.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// �ǃN���X
// Author : Sugawara Tsukasa
//=============================================================================
class CIronWindow_Wall : public CObject
{
public:
	CIronWindow_Wall(PRIORITY Priority = PRIORITY_MAP);					// �R���X�g���N�^
	~CIronWindow_Wall();												// �f�X�g���N�^
	static CIronWindow_Wall*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);						// ����������
	void Uninit(void);													// �I������
	void Update(void);													// �X�V����
	void Draw(void);													// �`�揈��
private:
};
#endif