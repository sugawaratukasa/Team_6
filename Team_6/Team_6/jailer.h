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
#include "jailer_return_routeState.h"

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
	void Move(void);								//�ړ��֐�
	void RetrunRoute(void);								//�ҋ@
	void Chase(void);								//�ǐ�
	void Caution(void);								//�x�����
	void Attack(void);								//�U�����

	int AddTimer(int add);		//�b�����Z
	void SettingPosDest(void);	//�ړI�n�̐ݒ�
	void SetRotDest();			//�����̖ړI�̒l�̐ݒ�
	bool IsHitPlayer(void);		//�v���C���[�Ƃ̏Փ˔���
	void MapCollision(void);										// �}�b�v�Ƃ̓����蔻��
	void SetRetrunData(void);
	//public�Z�b�^�[
	void SetTimer(int time) { m_nSwitchingTimer = time; }	//�^�C�}�[�Z�b�g
	
	//public�Q�b�^�[
	int GetTimer(void) { return m_nSwitchingTimer; }					//�^�C�}�[�Q�b�g
	float GetDistanceRange(void)const { return m_fDestinationRange; }	//�ړI�n�̋����̒����̎擾

private:
	//=========================================================================
	//�����o�ϐ��錾
	//=========================================================================
	static int m_nJailerTotal;		//�Ŏ�̑���
	CJailerView *m_pView;			//�Ŏ�̎����N���X�̃|�C���^�ϐ�
	CJailerState *m_pJailerState;	//��Ԃ̃|�C���^
	D3DXVECTOR3 m_rotDest;			//�����̖ړI�n
	D3DXVECTOR3 m_posDest;			//�ʒu�̖ړI�n
	D3DXVECTOR3 m_posDestOld;		//�O��̈ʒu�̖ړI�n
	D3DXVECTOR3 m_Distance;			//�ړI�n�܂ł̋���
	int m_nSwitchingTimer;			//��Ԃ̐؂�ւ��^�C�}�[
	int m_nNumber;					//�����̔ԍ�	
	float m_fDestinationRange;		//�ړI�n�Ǝ����̋����̒���
	CJailerSpot *m_pSpot;

	
};
#endif // !_JAILER_H_
