//=============================================================================
//
// �Ŏ�N���X [jailer.cpp]
// Author : Yamada Ryota
//
//=============================================================================
#include "jailer.h"
#include "manager.h"
#include "resource_manager.h"
#include "xfile.h"
#include "debug_proc.h"
#include "keyboard.h"
#include "player.h"
#include "jailer_State.h"
#include "fan3d.h"
#include "mode_base.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define JAILER_SPEED (10.0f)	//����

const D3DXVECTOR3 posdest[CJailer::POS_DEST_MAX] =
{
	D3DXVECTOR3(-1000.0f, 0.0f, 1000.0f),
	D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f),
	D3DXVECTOR3(1000.0f, 0.0f, -1000.0f),
	D3DXVECTOR3(1000.0f, 0.0f, 1000.0f),
};

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CJailer::CJailer()
{
	m_rotDest = ZeroVector3;
	m_posDest = ZeroVector3;
	m_posDestOld = ZeroVector3;
	m_nIndex = 0;
	m_SwitchingTimer = 0;
	m_cStateName.clear();		//�f�o�b�N�p��Ԗ���
	m_pFan3d = nullptr;		//��N���X�̃|�C���^�ϐ�
	m_pState = nullptr;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CJailer::~CJailer()
{
}

//=============================================================================
//�N���G�C�g����
//=============================================================================
CJailer * CJailer::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CJailer *pJailer = nullptr;

	//�C���X�^���X����
	pJailer = new CJailer;

	if (pJailer != nullptr)
	{
		//����������
		pJailer->Init(pos, rot);

		return pJailer;
	}

	return nullptr;
}

//=============================================================================
//����������
//=============================================================================
HRESULT CJailer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//X�t�@�C���N���X�̎擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	if (pXfile != nullptr)
	{
		//�Ŏ烂�f���̃N���G�C�g
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_JAILER);
	}

	//�L�����N�^�[�̏���������
	CCharacter::Init(pos, rot);

	//�A�C�h�����[�V�����Đ�
	SetMotion(JAILER_MOTION_IDOL);

	//�����̐ݒ�
	SetSpeed(JAILER_SPEED);

	SetUseShadow();

	// �e�̌���
	SetShadowRotCalculation();
	m_posDest = posdest[0];

	SetPos(m_posDest);

	//���E�̃N���G�C�g
	m_pFan3d = CFan3D::Create(D3DXVECTOR3(m_posDest.x, 20.0f, m_posDest.z), ZeroVector3, 8, D3DCOLOR_RGBA(255, 0, 0, 255));

	//��Ԑݒ�
	m_pState = CWaitState::GetInstance();

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CJailer::Uninit(void)
{
	//�L�����N�^�[�̏I������
	CCharacter::Uninit();
}

//=============================================================================
//�X�V����
//=============================================================================
void CJailer::Update(void)
{
	//�L�����N�^�[�̍X�V����
	CCharacter::Update();

	//�ʒu�̎擾
	D3DXVECTOR3 pos = GetPos();

	//�O��ʒu�̐ݒ�
	SetPosOld(pos);

	//�A�j���[�V�����̍X�V
	ModelAnimeUpdate();

	DebugpPrint();

	Rotation();
	m_pState->Update(this, m_pFan3d);
	
	if (m_pFan3d)
	{
		m_pFan3d->SetRotation(GetRot());							//��̌����̐ݒ�
		m_pFan3d->SetPosition(D3DXVECTOR3(pos.x, 500.0f, pos.z));	//��̈ʒu�̐ݒ�
	}
}

//=============================================================================
//�`�揈��
//=============================================================================
void CJailer::Draw(void)
{
	//�L�����N�^�[�̕`�揈��
	CCharacter::Draw();
}


void CJailer::UpdateState(void)
{

}

//=============================================================================
//�U������
//=============================================================================
void CJailer::Attack(void)
{
}

//=============================================================================
//��]�֐�
//=============================================================================
void CJailer::Rotation(void)
{	
	D3DXVECTOR3	nor = ZeroVector3;


	//�ړ������̃x�N�g���̐��K��
	D3DXVec3Normalize(&nor, &m_Distance);

	//�ړ������ɑ΂��Ẳ�]�p�����߂�
	float angle = atan2f(-nor.x, -nor.z);

	//�ړI�̊p�x�֐ݒ�
	m_rotDest.y = angle;

	//�������擾
	D3DXVECTOR3 rot = GetRot();

	// �������
	while (m_rotDest.y - rot.y > D3DXToRadian(180))
	{
		m_rotDest.y -= D3DXToRadian(360);
	}

	while (m_rotDest.y - rot.y < -D3DXToRadian(180))
	{
		m_rotDest.y += D3DXToRadian(360);
	}


	//�����̉�]
	rot += (m_rotDest - rot)*0.05f;

	//�����ݒ�
	SetRot(rot);
}

//=============================================================================
//���S����
//=============================================================================
void CJailer::Death(void)
{

}

//=============================================================================
// ��Ԑ؂�ւ��֐�
//=============================================================================
void CJailer::ChangeState(CJailerState * jailerstate)
{
	m_pState = jailerstate;
	m_pState->Init(this, m_pFan3d);
}
//=============================================================================
//�ړ�����
//=============================================================================
void CJailer::Move(void)
{
	D3DXVECTOR3 move = ZeroVector3;
	//�P�ʃx�N�g��
	D3DXVECTOR3 nor = ZeroVector3;
	float angle = 0.0f;
	//�ʒu�̎擾
	D3DXVECTOR3 pos = GetPos();

	m_Distance = (m_posDest - pos);

	//�A�C�h�����[�V�����Đ�
	SetMotion(JAILER_MOTION::JAILER_MOTION_MOVE);

	//�����̐ݒ�
	SetSpeed(JAILER_SPEED);

	//�ړ������̃x�N�g���̐��K��
	D3DXVec3Normalize(&nor, &m_Distance);

	//�ړ��ʂ�ݒ�
	move.x = nor.x * GetSpeed();
	move.z = nor.z * GetSpeed();

	//�ړ��ʂ̐ݒ�
	SetMove(move);
}

//=============================================================================
// �ҋ@
//=============================================================================
void CJailer::Wait(void)
{
	//�ʒu�̎擾
	D3DXVECTOR3 pos = GetPos();

	//�O��̌����֊m�F
	m_Distance = (m_posDestOld - pos);

	//�����̐ݒ�
	SetSpeed(ZERO_FLOAT);

	//�ړ��ʂ̐ݒ�
	SetMove(ZeroVector3);

	//�A�C�h�����[�V�����Đ�
	SetMotion(JAILER_MOTION::JAILER_MOTION_IDOL);
}

//=============================================================================
// �ǐ�
//=============================================================================
void CJailer::Chase()
{
	D3DXVECTOR3 move = ZeroVector3;
	//�P�ʃx�N�g��
	D3DXVECTOR3 nor = ZeroVector3;

	//�ʒu�̎擾
	D3DXVECTOR3 pos = GetPos();
	
	m_Distance = (GET_PLAYER_PTR->GetPos() - pos);

	//�A�C�h�����[�V�����Đ�
	SetMotion(JAILER_MOTION::JAILER_MOTION_MOVE);

	//�����̐ݒ�
	SetSpeed(5);

	//�ړ������̃x�N�g���̐��K��
	D3DXVec3Normalize(&nor, &m_Distance);

	//�ړ��ʂ�ݒ�
	move.x = nor.x * GetSpeed();
	move.z = nor.z * GetSpeed();

	//�ړ��ʂ̐ݒ�
	SetMove(move);
}


//=============================================================================
// �b�����Z
//=============================================================================
int CJailer::AddTimer(int add)
{
	m_SwitchingTimer += add;
	return m_SwitchingTimer;
}

//=============================================================================
// �C���f�b�N�X�̉��Z
//=============================================================================
void CJailer::AddIndex(void)
{
	m_nIndex++;
	
	//�C���f�b�N�X���ő�l�ȏ�̏ꍇ
	if (m_nIndex >= CJailer::POS_DEST_MAX)
	{
		m_nIndex = CJailer::POS_DEST_LEFT_TOP;
	}
	//���̖ړI�̈ʒu��ݒ�
	m_posDest = posdest[m_nIndex];

	//�O��̃C���f�b�N�X���v�Z
	int IndexOld = m_nIndex - 1;

	//�O��̃C���f�b�N�X���ŏ��l��菬�����Ȃ����ꍇ
	if (IndexOld < CJailer::POS_DEST_LEFT_TOP)
	{
		IndexOld = POS_DEST_RIGHT_TOP;
	}

	//�O��̖ړI�n��ݒ肷��
	m_posDestOld = posdest[IndexOld];
}


//=============================================================================
//�f�o�b�N���
//=============================================================================
void CJailer::DebugpPrint(void)
{
	//�ϐ�
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 move = GetMove();
	float Speed = GetSpeed();

	CDebugProc::Print("=====================Jailer=====================\n");
	CDebugProc::Print("�y�����z X:%f,Y:%f,Z:%f\n", rot.x, rot.y, rot.z);
	CDebugProc::Print("�y�ړI�̌����i�x���@�j�z %f\n", D3DXToDegree(m_rotDest.y));
	CDebugProc::Print("�y���݂̌����i�x���@�j�z %f\n", D3DXToDegree(rot.y));
	CDebugProc::Print("�y�ʒu�z X:%f,Y:%f,Z:%f\n", pos.x, pos.y, pos.z);
	CDebugProc::Print("�y�ړI�̈ʒu�z X:%f,Y:%f,Z:%f\n", posdest[m_nIndex].x, posdest[m_nIndex].y, posdest[m_nIndex].z);
	CDebugProc::Print("�yIndex�z %d\n", m_nIndex);
	CDebugProc::Print("�y�ړ��ʁz X:%f,Y:%f,Z:%f\n", move.x, move.y, move.z);
	CDebugProc::Print("�ySpeed�z %f\n", Speed);
	CDebugProc::Print("�y�J�E���g�z %d\n", m_SwitchingTimer);
}

