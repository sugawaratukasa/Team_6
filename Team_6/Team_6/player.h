#ifndef _PLAYER_H_
#define _PLAYER_H_
//=============================================================================
//
// �v���C���[�N���X�w�b�_�[ [player.h]
// Author : Nikaido Taichi
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "character.h"
#include "model_anime.h"
#include "item_object.h"
#include "player_action_ui.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define ANGLE_45                (D3DXToRadian(45.0f))                    // �p�x45
#define ANGLE_90                (D3DXToRadian(90.0f))                    // �p�x90
#define ANGLE_135                (D3DXToRadian(135.0f))                  // �p�x90
#define ANGLE_180                (D3DXToRadian(180.0f))                  // �p�x180
#define ANGLE_270                (D3DXToRadian(270.0f))                  // �p�x270
#define PLAYER_ROT_SPEED        (1.0f)                                   // �L�����N�^�[�̉�]���鑬�x

#define INCAPACITATED_TIME		(600)									 // �s���s�\����
#define MAX_PLAYER (2)													 // �v���C���[�̍ő吔
#define MAX_ITEM (3)													 // �v���C���[���擾�ł���A�C�e���̍ő吔

//=============================================================================
// �O���錾
//=============================================================================
class CItemGetUI;
class CItem;

class CPlayerItemUI;
class CPlayer_Action_UI;
//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CPlayer : public CCharacter
{
public:
	//=============================================================================
	//�@���[�V������Ԃ̗񋓌^
	//=============================================================================
	enum MOTION_STATE
	{
		MOTION_NONE = -1,
		MOTION_IDOL,				// �A�C�h�����[�V����
		MOTION_WALK,				// ���s���[�V����
		MOTION_MAX					// ���[�V�����ő吔
	};
	enum ITEM_GET_LIST
	{
		ITEM_NONE = -1,
		ITEM_KEY_STORAGE,			// �q�ɂ̌�
		ITEM_KEY_JAILER_ROOM,		// �Ŏ玺�̌�
		ITEM_KEY_CONTROL_ROOM,		// ���䎺�̌�
		ITEM_KEY_ELECTRICAL_ROOM,	// �d�C���̌�
		ITEM_KEY_PC_ROOM,			// PC���̌�
		ITEM_BATON,					// �x�_
		ITEM_MAP,					// �}�b�v
		ITEM_MAX
	};
	enum TYPE
	{
		PLAYER_NONE = -1,
		PLAYER_1,
		PLAYER_2,
	};
	CPlayer(PRIORITY Priority = PRIORITY_CHARACTER);				// �R���X�g���N�^
	~CPlayer();														// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �v���C���[�̐���
	void Draw(void);												// �`�揈��
	void ItemEffectCreate(int ItemGetList);							// �A�C�e�����ʏ���
	void ItemEffectUninit(void);									// �A�C�e�����ʍ폜����
	void ItemDelete(int nPlayer);									// �A�C�e���폜����
	void MapCollision(void);										// �}�b�v�Ƃ̓����蔻��

	virtual void InputMove(float fSpeed, float fAngle) = 0;			// �L�[�{�[�h�ړ�����
	virtual void PrisonWarp(void) = 0;								// �Ɩ[���[�v����
	virtual void SetbGuidCreate(CItemObject::ITEM_OBJECT_LIST Type) = 0;							// �A�C�e�������e�N�X�`����������
	void DoorOpen(int nPlayer);										// �����J������
	void Item_DuctPass(int nPlayer);								// �_�N�g�A�C�e���󂯓n��
	void UseSecurity_Cam(int nPlayer);								// �Ď��J�����̎g�p����
	void Action_UI_Create(void);
	//=============================================================================
	//�@Set�֐�
	//=============================================================================

	void SetAddbGetItem(int nItem, bool bGet);											// �A�C�e���̎擾�󋵂�ݒ�
	void SetSubbGetItem(int nItem, bool bGet);											// �A�C�e���̎擾�󋵂�ݒ�
	void SetUI(CPlayerItemUI * pUI) { m_pUI = pUI; }									// UI�ݒ�
	void SetbGoal(bool bGoal) { m_bGoal = bGoal; }										// �S�[����Ԑݒ�
	void SetbIncapacitated(bool bIncapacitated) { m_bIncapacitated = bIncapacitated; }	// �s���s�\��Ԑݒ�
	void SetbItemGuidCreate(bool bGuid) { m_bGuidCreate = bGuid; }						// �A�C�e�������e�N�X�`���̐������
	void SetbItemGet(bool bItemGet, D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void SetType(TYPE type) { m_Type = type; }
	//=============================================================================
	//�@Get�֐�
	//=============================================================================

	int GetItemCount(void) { return m_nItemCount; }				// �A�C�e���̎擾�������֐�
	bool GetbItem(int nItem) { return m_abGetItem[nItem]; }		// �A�C�e���̎擾�󋵎擾�֐�
	bool GetbGoal(void) { return m_bGoal; }						// �S�[����ԏ����֐�
	bool GetbIncapacitated(void) { return m_bIncapacitated; }	// �s���s�\��Ԏ擾�֐�
	int &GetIncapacitatedTimeCount(void) { return m_nIncapacitatedTimeCount; }    // �s���s�\�J�E���g�擾
	bool GetbGuidCreate(void) { return m_bGuidCreate; }			// �A�C�e�������e�N�X�`���̐�����Ԏ擾�֐�
	TYPE GetType(void) { return m_Type; }
	bool bGetItem(void) { return m_bGetItem; }
private:

	int m_nItemCount;						// �A�C�e���̏�����
	int m_nItemSortCount;					// �A�C�e���\�[�g�p�J�E���g
	int m_nIncapacitatedTimeCount;			// �s���s�\���ԃJ�E���g
	bool m_bGoal;							// �S�[�����
	bool m_bIncapacitated;					// �s���s�\���
	bool m_abGetItem[ITEM_MAX];				// �A�C�e�����擾���Ă邩
	bool m_bItempCreate[ITEM_MAX];			// �A�C�e���|�C���^����������
	bool m_bUICreate[ITEM_MAX];				// UI�������
	bool m_bGuidCreate;
	bool m_bInteract;						// �h�A�̔���
	bool m_bGetItem;						// �A�C�e��
	TYPE m_Type;
	CItemGetUI * m_pItemGetUI[ITEM_MAX];	// UI�̃|�C���^
	CPlayerItemUI * m_pUI;					// UI�|�C���^
	CItem * m_pItem[3];						// �A�C�e���|�C���^
	CPlayer_Action_UI *m_pAction_UI;		// �A�N�V����UI
	D3DXVECTOR3 m_InteractPos;				// �C���^���N�g�ʒu
	D3DXVECTOR3 m_InteractSize;				// �C���^���N�g�T�C�Y
	D3DXVECTOR3 m_ItemPos;					// �A�C�e���ʒu
	D3DXVECTOR3 m_ItemSize;					// �A�C�e���T�C�Y
};
#endif
