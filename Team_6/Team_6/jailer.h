#ifndef JAILER_H_
#define JAILER_H_
//=============================================================================
//
// �Ŏ�N���X�w�b�_�[ [jailer.h]
// Author : Yamada Ryota
//
//=============================================================================
class CJailerState;

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "character.h"
#include "jailer_view.h"
#include "jailer_WaitState.h"

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

	enum POS_DEST
	{
		POS_DEST_LEFT_TOP = 0,
		POS_DEST_LEFT_BOTTOM,
		POS_DEST_RIGHT_BOTTOM,
		POS_DEST_RIGHT_TOP,
		POS_DEST_MAX,
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

	void UpdateState(void);							// ��Ԃ̍X�V
	void Attack(void);								// �U���̏���
	void Move(void);								// �ړ��֐�
	void Death(void);								// ���񂾂Ƃ��̏���
	void Rotation(void);							//��]
	void ChangeState(CJailerState *jailerstate);	//��ԑJ��
	void Wait(void);								//�ҋ@
	void Chase(void);								//�ǐ�
	void Caution(void);								//�x�����
	int AddTimer(int add);							//�b�����Z
	void SettingPosDest(void);						//�ړI�n�̐ݒ�
	void SetRotDest();
	//public�Z�b�^�[
	void SetTimer(int time) { m_nSwitchingTimer = time; }//�^�C�}�[�Z�b�g

	//public�Q�b�^�[
	int GetTimer(void) { return m_nSwitchingTimer; }	//�^�C�}�[�Q�b�g
	
#ifdef _DEBUG
	void DebugpPrint(void);	//��Ԗ���
#endif

private:
	//=========================================================================
	//�����o�ϐ��錾
	//=========================================================================
	static int m_nJailerTotal;		//�Ŏ�̑���
	D3DXVECTOR3 m_rotDest;			//�����̖ړI�n
	D3DXVECTOR3 m_posDest;			//�ʒu�̖ړI�n
	D3DXVECTOR3 m_posDestOld;		//�O��̈ʒu�̖ړI�n
	D3DXVECTOR3 m_Distance;			//�ړI�n�܂ł̋���
	int m_nIndex;					//�C���f�b�N�X
	int m_nSwitchingTimer;			//��Ԃ̐؂�ւ��^�C�}�[
	int m_nNumber;					//�����̔ԍ�		
	CJailerView *m_pView;			//�Ŏ�̎����N���X�̃|�C���^�ϐ�
	CJailerState *m_pJailerState;	//��Ԃ̃|�C���^
};
#endif // !_JAILER_H_
