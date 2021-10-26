#ifndef JAILER_H_
#define JAILER_H_
//=============================================================================
//
// �Ŏ�N���X�w�b�_�[ [jailer.h]
// Author : Yamada Ryota
//
//=============================================================================
class CJailerState;
class CPlayer;

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

	CJailer(float pos_x, float pos_z, CPlayer *player) :
		m_posX(pos_x),
		m_posZ(pos_z),
		m_pPlayer(player),
		m_pState(CWaitState::GetInstance())
	{};

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

	//�v���C���[�Ƃ̋����`�F�b�N
	bool IsDistanceToPlayer(float distance, bool out_side = false);

	//��ԑJ��
	void ChangeState(CJailerState *state);

	//�ǐ�
	void Chase();
	int GetTimer() { return m_Timer; }
	void SetTimer(int time) { m_Timer = time; }
	int AddTimer(int add) 
	{
		m_Timer += add;
		return m_Timer;
	};

private:
	//�v���C���[�Ƃ̋����擾
	float GetDistance();

private:
	D3DXVECTOR3 m_rotDest;
	int m_nIndex;
	D3DXVECTOR3 m_posDest;
	CFan3D *m_pFan3d;		//��N���X�̃|�C���^�ϐ�
	int m_Timer;
	CPlayer *m_pPlayer;
	CJailerState *m_pState;
	float m_posX;
	float m_posZ;
};
#endif // !_JAILER_H_
