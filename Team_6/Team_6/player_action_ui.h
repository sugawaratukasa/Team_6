#ifndef _PLAYER_ACTION_UI_H_
#define _PLAYER_ACTION_UI_H_
//=============================================================================
// �v���C���[�s��UI [player_action_ui_1.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h
// Author : Sugawara Tsukasa
//=============================================================================
#include "player.h"
#include "scene_2d.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �O���錾
// Author : Sugawara Tsukasa
//=============================================================================
class CScene2D;
//=============================================================================
// �S�[���̔��N���X
// Author : Sugawara Tsukasa
//=============================================================================
class CPlayer_Action_UI
{
public:
	// �v���C���[�^�C�v�̗񋓌^
	enum PLAYER_TYPE
	{
		PLYER_TYPE_NONE = -1,
		PLYER_TYPE_1,
		PLYER_TYPE_2
	};
	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_X,
		TYPE_A,
		TYPE_MAX
	};

	CPlayer_Action_UI();								// �R���X�g���N�^
	~CPlayer_Action_UI();								// �f�X�g���N�^
	static CPlayer_Action_UI *Create(int player_type);	// ��������
	HRESULT Init(void);									// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void UI_Create_Management(void);					// UI�����Ǘ�
	//=============================================================================
	// Set�֐�
	//=============================================================================
	void SetInteract(bool bCameraInteract);	//{ m_bInteract = bCameraInteract; }
	void SetbItemGet(bool bItemGet);		//{ m_bItemGet = bItemGet; }
private:
	CScene2D *m_apScene2D[TYPE_MAX];	// 2D�̃|�C���^
	bool m_bInteract;				// �J�����ɃC���^���N�g�ł��邩�̔���
	bool m_bItemGet;					// �A�C�e�����E�������ł��邩�̔���
	int m_nPlayer_Type;					// �v���C���[�^�C�v
};
#endif