//=============================================================================
//
// �|�[�Y�{�^���}�l�[�W���[ [pause_button_manager.h]
// Author : ��K������
//
//=============================================================================
#ifndef _PAUSE_BUTTON_MANAGER_H_
#define _PAUSE_BUTTON_MANAGER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "button.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CButton;
class CPauseBG;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPauseButtonManager
{
public:
	CPauseButtonManager();
	~CPauseButtonManager();
	static CPauseButtonManager * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
private:
	typedef enum
	{
		BUTTON_NONE = -1,
		BUTTON_QUIT_GAME,
		BUTTON_BACK_TO_TITLE,
		BUTTON_GUID,
		BUTTON_MAX
	}BUTTON;
	void Input(void);
	void Select(void);
	void InitCreateAll(void);
	CButton * m_apButton[BUTTON_MAX];	//�{�^���̃|�C���^
	CPauseBG *m_pPauseBG;				//�|�[�Y�̃|�C���^
	int m_nButton;						//�{�^��
};
#endif