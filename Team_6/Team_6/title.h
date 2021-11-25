#ifndef _TITLE_H_
#define _TITLE_H_
//=============================================================================
//
// �^�C�g���N���X [title.h]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode_base.h"
#include "manager.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;
class CPlayer;
class CCamera;
class CCameraTitle;
class CLight;

//=============================================================================
// �N���X��`
//=============================================================================
class CTitle : public CModeBase
{
public:
	CTitle();					// �R���X�g���N�^
	~CTitle();					// �f�X�g���N�^

	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��
	void Create2DObject(void);	// 2D�I�u�W�F�N�g�̐����֐�
	void Create3DObject(void);	// 3D�ɕK�v�ȏ��𐶐�
	void ModeTransition(CManager::MODE_TYPE mode);	// �J��
								// Get�֐�
	CCamera* GetCamera(void) override { return (CCamera*)m_pCamera; }		// �J�����̃|�C���^
	CLight* GetLight(void) override { return m_pLight; }				// ���C�g�̃|�C���^
private:
	CPlayer *m_pShip;				// �D
	vector<CScene2D*> m_pObject2D;	// 2D�I�u�W�F�N�g
	CCameraTitle *m_pCamera;		// �J�����̃|�C���^
	CLight *m_pLight;				// ���C�g�̃|�C���^
	int		m_nCountToMovie;		// ����Đ��܂ł̑ҋ@����
	bool	m_bCount;				// �J�E���g���邩�ǂ���
};
#endif