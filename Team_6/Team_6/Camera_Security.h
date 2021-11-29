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
#include "jailer_view.h"
#include "scene.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SECCAM_ANGLE_MAX D3DXToRadian(45)
#define SECCAM_RETURN_LENGTH	60

//=============================================================================
// �J�����N���X
//=============================================================================
class CCameraSecurity : public CScene
{
public:
	CCameraSecurity();					// �R���X�g���N�^
	~CCameraSecurity();					// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Update(void);					// �X�V����
	void Draw(void);
	void Uninit(void);
	void SearchPlayer(void);
	static CCameraSecurity*Create(D3DXVECTOR3 pos, float fDir);	// �N���G�C�g

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	float GetAngle(void) { return m_fAngle; }
	CCameraSecurity * GetTop(void) { return m_pTop; }
	CCameraSecurity * GetNext(void) { return m_pNext; }
	CCameraSecurity * GetPrev(void) { return m_pPrev; }
	CCameraSecurity * GetBottom(void) { return m_pBot; }

private:
	D3DXVECTOR3 m_pos;
	float		m_fDir;
	float		m_fAngle;
	float		m_fAngleMoveRate;
	int			m_nCamReturnCount;
	CJailerView	*m_pView;
	static CCameraSecurity *m_pTop;
	static CCameraSecurity *m_pCur;
	static CCameraSecurity *m_pBot;
	CCameraSecurity *m_pPrev;
	CCameraSecurity *m_pNext;
};
#endif 