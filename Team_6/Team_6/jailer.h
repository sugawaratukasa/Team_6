#ifndef JAILER_H_
#define JAILER_H_
//=============================================================================
//
// �Ŏ�N���X�w�b�_�[ [jailer.h]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//�O���錾
//=============================================================================
class CJailerState;
class CJailerSpot;
class CJailer_Emotion;

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "character.h"
#include "jailer_view.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_JAILER (1)

//=============================================================================
//�Ŏ�N���X
//=============================================================================
class CJailer :public CCharacter
{
public:
	//=========================================================================
	//���[�V�����̎��
	//=========================================================================
	enum JAILER_MOTION
	{
		JAILER_MOTION_IDOL = 0,
		JAILER_MOTION_MOVE,
		JAILER_MOTION_MAX,
	};
	
	enum AROUND_CONFIRMATION
	{
		AROUND_CONFIRMATION_NONE = 0,
		AROUND_CONFIRMATION_LEFT,
		AROUND_CONFIRMATION_RIGHT,
		AROUND_CONFIRMATION_MAX
	};

	//=========================================================================
	//�����o�֐��錾
	//=========================================================================
	CJailer(int nJailerNumber);	//�R���X�g���N�^
	~CJailer();	//�f�X�g���N�^

	static CJailer *Create(const int nJailerNumber);	//�N���G�C�g����

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//����������
	void Uninit(void);								//�I������
	void Update(void);								//�X�V����
	void Draw(void);								//�`�揈��
	void Rotation(void);							//��]����

	//�Ŏ�AI�̂��ꂼ���Ԃ̏����֐�
	void ChangeState(CJailerState *jailerstate);	//��ԑJ��
	void Patrol(void);								//����֐�
	void RetrunRoute(void);							//�ҋ@
	void ChasePlayer(void);							//�v���C���[��ǐ�
	void GuardSurrounding(void);					//���͌x�����
	void Notice(void);
	void Attack(void);								//�U�����
	void Damage(void);

	int AddTime(int add);			//�b�����Z
	void ChangePosDest(void);		//�ړI�n�̐ݒ�
	void ChangeRotDest(void);		//�����̖ړI�̒l�̐ݒ�
	bool IsHitPlayer(void);			//�v���C���[�Ƃ̏Փ˔���
	void CheckMapCollision(void);	// �}�b�v�Ƃ̓����蔻��
	
	void TurnAround(void);

	//public�Z�b�^�[
	void SetRetrunData(void);	//���[�g���A�̏��ݒ�
	void SetGuardBaseDir(void);//�x�����̊�̕����̐ݒ�
	void SetTime(int time) { m_nStateTimer = time; }	//�^�C�}�[�Z�b�g
	void SetNotice(const D3DXVECTOR3 pos);	//�ʕ�
	void SetReceiptNotice(const bool bIsReceipt) { m_bIsReceiptNotice = bIsReceipt; }
	void ReSetHitPlayer(void) { m_bIsHitPlayer = false; }

	//public�Q�b�^�[
	int GetTime(void) { return m_nStateTimer; }				//�^�C�}�[�Q�b�g
	float GetDestLength(void)const { return m_fDestLength; }	//�ړI�n�̋����̒����̎擾
	AROUND_CONFIRMATION GetAround(void) { return m_eAroud; }
	CJailerSpot *GetJailerSpot(void) { return m_pSpot; }
	CJailer_Emotion *GetEmotion(void) { return m_pEmotion; }
	bool GetReceiptNotice(void) { return m_bIsReceiptNotice; }
	bool GetHitPlayer(void) { return m_bIsHitPlayer; }

private:
	//=========================================================================
	//�����o�ϐ��錾
	//=========================================================================
	CJailerView *m_pView;			//�Ŏ�̎����N���X�̃|�C���^�ϐ�
	CJailerState *m_pJailerState;	//��Ԃ̃|�C���^
	CJailerSpot *m_pSpot;			//�X�|�b�g�̃|�C���^
	CJailer_Emotion *m_pEmotion;	//����N���X�̃|�C���^
	D3DXVECTOR3 m_rotDest;			//�����̖ړI�l
	D3DXVECTOR3 m_posDest;			//�ʒu�̖ړI�l
	D3DXVECTOR3 m_posDestOld;		//�O��̈ʒu�̖ړI�l
	D3DXVECTOR3 m_distance;			//�ړI�n�܂ł̋���
	D3DXVECTOR3 m_GuardBaseDir;		//�x�����̊�̕���
	int m_nStateTimer;				//��Ԃ̐؂�ւ��^�C�}�[
	int m_nMapHitTime;				//�}�b�v�ɐG�ꑱ��������
	const int m_nNumber;			//�����̔ԍ�	
	float m_fDestLength;			//�ړI�n�Ǝ����̋����̒���
	float m_TurnSpeed;				//�U��������x
	bool m_bIsReceiptNotice;		//�ʕ����M�ł��邩�ǂ���
	bool m_bIsHitPlayer;			//�v���C���[�Ɠ����������ǂ���
	bool m_bHitMap;
	AROUND_CONFIRMATION m_eAroud;	//���͌x���̏��
};
#endif // !_JAILER_H_
