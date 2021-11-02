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
	CPlayer(PRIORITY Priority = PRIORITY_CHARACTER);				// �R���X�g���N�^
	~CPlayer();														// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �v���C���[�̐���
	void Draw(void);												// �`�揈��
	bool GetbIncapacitated(void) { return m_bIncapacitated; }		// �s���s�\��Ԏ擾����
	virtual void KeyboardMove(float fSpeed, float fAngle) = 0;
	virtual void PadMove(float fSpeed, float fAngle) = 0;
	//=============================================================================
	//�@Set�֐�
	//=============================================================================
	void SetItem(CItemObject::ITEM_OBJECT_LIST ItemList, CItemObject * pItem) { m_apItem[ItemList] = pItem;}	// �A�C�e���ݒ菈��
private:
	CItemObject *  m_apItem[CItemObject::ITEM_OBJECT_MAX];	// �A�C�e���̃|�C���^
	int m_nItemCount;										// �A�C�e���̏�����
	int m_nIncapacitatedTimeCount;							// �s���s�\���ԃJ�E���g
	bool m_bIncapacitated;									// �s���s�\���
};
#endif
