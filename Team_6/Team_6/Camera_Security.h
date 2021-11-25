#ifndef _CAMERA_SECURITY_H_
#define _CAMERA_SECURITY_H_
//=============================================================================
//
// �Ď��J�������Ǘ����� [Camera_Security.cpp]
// Author : ��{ ��
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "game.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SECCAM_ANGLE_MAX D3DXToRadian(45)
#define SECCAM_RETURN_LENGTH	60

//=============================================================================
// �J�����N���X
//=============================================================================
class CCameraSecurity
{
public:
	CCameraSecurity();					// �R���X�g���N�^
	~CCameraSecurity();					// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, float fDir);					// ����������
	void Update(void);					// �X�V����
	static CCameraSecurity*Create(D3DXVECTOR3 pos, float fDir);	// �N���G�C�g

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	float GetAngle(void) { return m_fAngle; }

private:
	D3DXVECTOR3 m_pos;
	float		m_fDir;
	float		m_fAngle;
	float		m_fAngleMoveRate;
	int			m_nCamReturnCount;
};
#endif 