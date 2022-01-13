#ifndef _BOOKBOX_H_
#define _BOOKBOX_H_
//=============================================================================
// �{�I [bookbox.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// �{�I�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CBookBox : public CObject
{
public:
	CBookBox(PRIORITY Priority = PRIORITY_MAP);					// �R���X�g���N�^
	~CBookBox();													// �f�X�g���N�^
	static CBookBox*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
private:
};
#endif
