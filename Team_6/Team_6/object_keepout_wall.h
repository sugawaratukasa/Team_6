#ifndef _OBJECT_KEEPOUT_WALL_H_
#define _OBJECT_KEEPOUT_WALL_H_
//=============================================================================
//	�J���Ȃ��h�A [object_keepout_wall.h]
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
class CKeepOut_Wall : public CObject
{
public:
	CKeepOut_Wall(PRIORITY Priority = PRIORITY_MAP);				// �R���X�g���N�^
	~CKeepOut_Wall();												// �f�X�g���N�^
	static CKeepOut_Wall*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
private:
};
#endif