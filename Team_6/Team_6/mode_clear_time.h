#ifndef _MODE_CLEAR_TIME_H_
#define _MODE_CLEAR_TIME_H_
//=============================================================================
//
// �N���A�^�C���N���X [mode_clear_time.h]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode_base.h"
#include "time.h"
//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���錾
//=============================================================================
class CTime;
//=============================================================================
// �N���X��`
//=============================================================================
class CMode_Clear_Time : public CModeBase
{
public:
	CMode_Clear_Time();			// �R���X�g���N�^
	~CMode_Clear_Time();		// �f�X�g���N�^

	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��
	void ModeTransition(void);	// �J��
	void ReadPlayerFile(void);	// �v���C���[�̃t�@�C���ǂݍ���
private:
	CTime *m_pTime;				// �^�C���̃|�C���^
	int m_nPlayerTime;			// �v���C���[�̃^�C��
};
#endif