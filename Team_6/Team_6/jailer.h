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
#include "fan3d.h"
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

	CJailer();
	~CJailer();

	static CJailer *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void UpdateState(void);								// ��Ԃ̍X�V
	void Attack(void);									// �U���̏���
	void Move(void);									// �ړ��֐�
	void Death(void);									// ���񂾂Ƃ��̏���
	void Rotation(void);//��]
	//��ԑJ��
	void ChangeState(CJailerState *jailerstate);

	//�ҋ@
	void Wait(void);
	//�ǐ�
	void Chase(void);

	//�^�C�}�[�Q�b�g
	int GetTimer(void) { return m_SwitchingTimer; }
	//�^�C�}�[�Z�b�g
	void SetTimer(int time) { m_SwitchingTimer = time; }
	//�b�����Z
	int AddTimer(int add);

	//�C���f�b�N�X�̉��Z
	void AddIndex(void);

	//�f�o�b�N�p
	//��Ԗ���
	void DebugpPrint(void);

private:
	D3DXVECTOR3 m_rotDest;		//�����̖ړI�n
	D3DXVECTOR3 m_posDest;		//�ʒu�̖ړI�n
	D3DXVECTOR3 m_posDestOld;	//�O��̈ʒu�̖ړI�n
	D3DXVECTOR3 m_Distance;		//�ړI�n�܂ł̋���
	int m_nIndex;				//�C���f�b�N�X
	int m_SwitchingTimer;		//��Ԃ̐؂�ւ��^�C�}�[

	std::string m_cStateName;		//�f�o�b�N�p��Ԗ���
	CFan3D *m_pFan3d;		//��N���X�̃|�C���^�ϐ�
	CJailerState *m_pState;		//��Ԃ̃|�C���^
};
#endif // !_JAILER_H_
