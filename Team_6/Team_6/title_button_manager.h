//=============================================================================
//
// �^�C�g���{�^���}�l�[�W���[ [title_button_manager.h]
// Author : ��K������
//
//=============================================================================
#ifndef _TITLE_BUTTON_MANAGER_H_
#define _TITLE_BUTTON_MANAGER_H_

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

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTitleButtonManager
{
public:
	CTitleButtonManager();
	~CTitleButtonManager();
	static CTitleButtonManager * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
private:
	typedef enum
	{
		BUTTON_NONE = -1,
		BUTTON_START,
		BUTTON_RANKING,
		BUTTON_EXIT,
		BUTTON_MAX
	}BUTTON;
	void PlayerItemGet(void);
	void Select(void);
	void InitCreateAll(void);
	CButton * m_apButton[BUTTON_MAX];	//�{�^���̃|�C���^
	int m_nButton;						//�{�^��
};
#endif