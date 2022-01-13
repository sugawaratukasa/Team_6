#ifndef _LOCKER_H_
#define _LOCKER_H_
//=============================================================================
// ���b�J�[ [locker.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// ���b�J�[�N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CLocker : public CObject
{
public:
	CLocker(PRIORITY Priority = PRIORITY_MAP);					// �R���X�g���N�^
	~CLocker();													// �f�X�g���N�^
	static CLocker*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
private:
};
#endif
