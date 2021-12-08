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
class CMapSpot;
class CJailerSpot;

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "character.h"
#include "jailer_view.h"

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
	
	//=========================================================================
	//�����o�֐��錾
	//=========================================================================
	CJailer();	//�R���X�g���N�^
	~CJailer();	//�f�X�g���N�^

	static CJailer *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);	//�N���G�C�g����

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
	void Attack(void);								//�U�����

	int AddTime(int add);			//�b�����Z
	void ChangePosDest(void);		//�ړI�n�̐ݒ�
	void ChangeRotDest(void);		//�����̖ړI�̒l�̐ݒ�
	bool IsHitPlayer(void);			//�v���C���[�Ƃ̏Փ˔���
	void CheckMapCollision(void);	// �}�b�v�Ƃ̓����蔻��
	
	//public�Z�b�^�[
	void SetRetrunData(void);	//���[�g���A�̏��ݒ�
	void SetGuardBaseDir(void);//�x�����̊�̕����̐ݒ�
	void SetTime(int time) { m_nSwitchingTime = time; }	//�^�C�}�[�Z�b�g
	
	//public�Q�b�^�[
	int GetTime(void) { return m_nSwitchingTime; }					//�^�C�}�[�Q�b�g
	float GetDestLength(void)const { return m_fDestLength; }	//�ړI�n�̋����̒����̎擾

private:
	//=========================================================================
	//�����o�ϐ��錾
	//=========================================================================
	static int m_nJailerTotal;		//�Ŏ�̑���
	CJailerView *m_pView;			//�Ŏ�̎����N���X�̃|�C���^�ϐ�
	CJailerState *m_pJailerState;	//��Ԃ̃|�C���^
	CJailerSpot *m_pSpot;			//�X�|�b�g�̃|�C���^
	D3DXVECTOR3 m_rotDest;			//�����̖ړI�n
	D3DXVECTOR3 m_posDest;			//�ʒu�̖ړI�n
	D3DXVECTOR3 m_posDestOld;		//�O��̈ʒu�̖ړI�n
	D3DXVECTOR3 m_distance;			//�ړI�n�܂ł̋���
	D3DXVECTOR3 m_GuardBaseDir;		//�x�����̊�̕���
	int m_nSwitchingTime;			//��Ԃ̐؂�ւ��^�C�}�[
	int m_nNumber;					//�����̔ԍ�	
	float m_fDestLength;			//�ړI�n�Ǝ����̋����̒���
	float m_TurnSpeed;				//�U��������x
};
#endif // !_JAILER_H_
