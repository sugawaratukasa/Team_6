#ifndef _MODE_BASE_H_
#define _MODE_BASE_H_
//==============================================================================
//
// ���[�h�̊��N���X  [mode_base.h]
// Author : Sugawara Tsukasa
//
//==============================================================================

//==============================================================================
// �C���N���[�h
//==============================================================================
#include "main.h"
#include "player.h"
#include "jailer.h"

//=============================================================================
// �O���錾
//=============================================================================
class CLight;
class CCamera;
class CPlayer;
class CJailer;
//==============================================================================
// �N���X��`
//==============================================================================
class CModeBase
{
public:
	CModeBase();				// �R���X�g���N�^
	virtual ~CModeBase() {};	// �f�X�g���N�^

	virtual HRESULT Init(void) = 0;		// ������
	virtual void Update(void) = 0;		// �X�V
	virtual void Draw(void) = 0;		// �`��

										// Get�֐�
	virtual CCamera* GetCamera(void) { return m_pCamera; }				// �J�����̃|�C���^
	virtual CLight* GetLight(void) { return m_pLight; }					// ���C�g�̃|�C���^
	virtual CPlayer* GetPlayer(int nPlayer) { return m_apPlayer[nPlayer]; }	// �v���C���[�̃|�C���^
	virtual CJailer* GetJailer(void) { return m_pJailer; }					// ���C�g�̃|�C���^

private:
	CCamera *m_pCamera;		// �J�����̃|�C���^
	CLight *m_pLight;		// ���C�g�̃|�C���^
	CPlayer *m_apPlayer[MAX_PLAYER];		// �v���C���[�̃|�C���^
	CJailer *m_pJailer;		// �Ŏ�̃|�C���^
};

#endif