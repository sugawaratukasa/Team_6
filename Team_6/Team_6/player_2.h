#ifndef _PLAYER_2_H_
#define _PLAYER_2_H_
//=============================================================================
//
// �v���C���[1 [player_1.h]
// Author : Nikaido Taichi
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "player.h"

//=============================================================================
// �O���錾
//=============================================================================

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CPlayer2 : public CPlayer
{
public:
	CPlayer2(PRIORITY Priority = PRIORITY_CHARACTER);									// �R���X�g���N�^
	~CPlayer2();																		// �f�X�g���N�^
	static CPlayer2*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);							// �N���G�C�g
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);										// ����������
	void Uninit(void);																	// �I������
	void Update(void);																	// �v���C���[�̐���
	void Draw(void);																	// �`�揈��
private:
	void KeyboardMove(float fSpeed, float fAngle);
	void PadMove(float fSpeed, float fAngle);
	void UpdateRot(void);
	D3DXVECTOR3 m_rotDest;
};
#endif