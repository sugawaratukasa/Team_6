#ifndef _PLAYER_H_
#define _PLAYER_H_
//=============================================================================
//
// �v���C���[�N���X�w�b�_�[ [player.h]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "character.h"
#include "model_anime.h"
#include "item_object.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define ANGLE_45                (D3DXToRadian(45.0f))                    // �p�x45
#define ANGLE_90                (D3DXToRadian(90.0f))                    // �p�x90
#define ANGLE_135                (D3DXToRadian(135.0f))                  // �p�x90
#define ANGLE_180                (D3DXToRadian(180.0f))                  // �p�x180
#define ANGLE_270                (D3DXToRadian(270.0f))                  // �p�x270
#define PLAYER_ROT_SPEED        (0.1f)                                   // �L�����N�^�[�̉�]���鑬�x
#define PLAYER_SPEED            (50.0f)                                  // �v���C���[�̈ړ���
#define INCAPACITATED_TIME		(1200)									 // �s���s�\����
#define MAX_PLAYER (2)
#define MAX_ITEM (3)

//=============================================================================
// �O���錾
//=============================================================================
class CItem;
class CPlayerUI;

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
		MOTION_MAX					// ���[�V�����ő吔
	};
	enum ITEM_GET_LIST
	{
		ITEM_NONE = -1,
		ITEM_KEY_PRISON,
		ITEM_KEY_STORAGE,
		ITEM_KEY_JAILER_ROOM,
		ITEM_KEY_PC_ROOM,
		ITEM_BATON,
		ITEM_MAP,
		ITEM_MAX
	};
	CPlayer(PRIORITY Priority = PRIORITY_CHARACTER);				// �R���X�g���N�^
	~CPlayer();														// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �v���C���[�̐���
	void Draw(void);												// �`�揈��
	bool GetbIncapacitated(void) { return m_bIncapacitated; }		// �s���s�\��Ԏ擾����
	virtual void KeyboardMove(float fSpeed, float fAngle) = 0;
	virtual void PadMove(float fSpeed, float fAngle) = 0;
	void MapCollision(void);										// �}�b�v�Ƃ̓����蔻��
	void ItemEffectCreate(int ItemGetList);
	void ItemEffectUninit(void);

	void ItemDelete(void);
	//=============================================================================
	//�@Set�֐�
	//=============================================================================
	void SetAddbGetItem(int nItem, bool bGet);	//�A�C�e���̎擾�󋵂�ݒ�
	void SetSubbGetItem(int nItem, bool bGet);	//�A�C�e���̎擾�󋵂�ݒ�
	void SetUI(CPlayerUI * pUI) { m_pUI = pUI; }
	//=============================================================================
	//�@Get�֐�
	//=============================================================================
	bool GetbItem(int nItem) { return m_abGetItem[nItem]; }		// �A�C�e���̎擾�󋵂��擾
	int GetItemCount(void) { return m_nItemCount; }
private:
	int m_nItemCount;					// �A�C�e���̏�����
	int m_nIncapacitatedTimeCount;		// �s���s�\���ԃJ�E���g
	bool m_bIncapacitated;				// �s���s�\���
	bool m_abGetItem[ITEM_MAX];			// �A�C�e�����擾���Ă邩
	bool m_bItempCreate[ITEM_MAX];		// �A�C�e���|�C���^����������


	int m_nItemSortCount;
	CItem * m_pItem[3];
	CPlayerUI * m_pUI;
	int m_test;
};
#endif
