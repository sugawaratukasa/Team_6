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
#define JAILER_NORMAL_SPEED (10.0f)	//�ʏ펞�̈ړ����x
#define JAILER_CHASE_SPEED (20.0f)	//�ǐՎ��̈ړ����x
#define JAILER_ROTSTION_RATE (0.1f)	//��]�̌W��
#define VIEW_POS_Y (70.0f)			//�����̍���
#define VIEW_POLYGON_NUM (8)		//�����̃|���S����

const D3DXVECTOR3 aMoveSpot[CJailer::POS_DEST_MAX] =
{
	D3DXVECTOR3(-1000.0f, 0.0f, 1000.0f),
	D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f),
	D3DXVECTOR3(1000.0f, 0.0f, -1000.0f),
	D3DXVECTOR3(1000.0f, 0.0f, 1000.0f),
};

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
int CJailer::m_nJailerTotal = -1;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CJailer::CJailer()
{
	m_rotDest = ZeroVector3;
	m_posDest = ZeroVector3;
	m_posDestOld = ZeroVector3;
	m_nIndex = ZERO_INT;
	m_nSwitchingTimer = ZERO_INT;
	m_nNumber = ZERO_INT;
	m_pView = nullptr;		//��N���X�̃|�C���^�ϐ�
	m_pJailerState = nullptr;

	//�����̉��Z
	m_nJailerTotal++;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CJailer::~CJailer()
{
	//�����̌��Z
	m_nJailerTotal--;
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
	SetSpeed(JAILER_NORMAL_SPEED);

	SetUseShadow();

	// �e�̌���
	SetShadowRotCalculation();

	//�����̔ԍ���ݒ�
	m_nNumber = m_nJailerTotal;

	m_nIndex = m_nNumber;
	
	//�ړI�n��ݒ�
	m_posDest = aMoveSpot[m_nIndex];

	//�ʒu�̐ݒ�
	SetPos(m_posDest);

	//���E�̃N���G�C�g
	m_pView = CJailerView::Create(D3DXVECTOR3(m_posDest.x, VIEW_POS_Y, m_posDest.z), 
		ZeroVector3, VIEW_POLYGON_NUM, D3DCOLOR_RGBA(255, 0, 0, 255));

	//��Ԑݒ�
	m_pJailerState = CWaitState::GetInstance();

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

	//��]����
	Rotation();

	//��ԏ����̍X�V
	if (m_pJailerState != nullptr)
	{
		m_pJailerState->Update(this, m_pView);
	}
	
	if (m_pView)
	{
		m_pView->SetRotation(GetRot());									//��̌����̐ݒ�
		m_pView->SetPosition(D3DXVECTOR3(pos.x, VIEW_POS_Y, pos.z));	//��̈ʒu�̐ݒ�
	}

#ifdef _DEBUG
	// �L�[�{�[�h�擾
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_NUMPAD7))
	{
		SettingPosDest();
	}

	//DebugpPrint();
#endif
}

//=============================================================================
//�`�揈��
//=============================================================================
void CJailer::Draw(void)
{
	//�L�����N�^�[�̕`�揈��
	CCharacter::Draw();
}

//=============================================================================
//�L�����N�^�[�̏��
//=============================================================================
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
	//�������擾
	D3DXVECTOR3 rot = GetRot();

	// �������
	while ((m_rotDest.y - rot.y) > D3DXToRadian(180.0f))
	{
		m_rotDest.y -= D3DXToRadian(360.0f);
	}

	while ((m_rotDest.y - rot.y) < -D3DXToRadian(180.0f))
	{
		m_rotDest.y += D3DXToRadian(360.0f);
	}

	//�����̉�]
	rot += (m_rotDest - rot) * JAILER_ROTSTION_RATE;

	if (rot.y > D3DXToRadian(360.0f))
	{
		rot.y = D3DXToRadian(0.0f);
	}
	if (rot.y < D3DXToRadian(0.0f))
	{
		rot.y = D3DXToRadian(360.0f);
	}

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
	m_pJailerState = jailerstate;
	m_pJailerState->Init(this, m_pView);
}

//=============================================================================
//�ړ�����
//=============================================================================
void CJailer::Move(void)
{
#ifdef _DEBUG
	CDebugProc::Print("������\n");
#endif
	D3DXVECTOR3 move = ZeroVector3;

	//�P�ʃx�N�g��
	D3DXVECTOR3 nor = ZeroVector3;

	//�ʒu�̎擾
	D3DXVECTOR3 pos = GetPos();

	//���ݒn�ƖړI�n�܂ł̃x�N�g�����v�Z
	m_Distance = (m_posDest - pos);

	//�����̖ړI�̒l�̌v�Z
	SetRotDest();

	//�A�C�h�����[�V�����Đ�
	SetMotion(JAILER_MOTION::JAILER_MOTION_MOVE);

	//�����̐ݒ�
	SetSpeed(JAILER_NORMAL_SPEED);

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
#ifdef _DEBUG
	CDebugProc::Print("�ҋ@���\n");
#endif
	//�ʒu�̎擾
	D3DXVECTOR3 pos = GetPos();

	//�O��̌����֊m�F
	m_Distance = (m_posDestOld - pos);

	//�����̖ړI�̒l�̌v�Z
	SetRotDest();

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
#ifdef _DEBUG
	CDebugProc::Print("�ǐՏ��\n");
#endif
	D3DXVECTOR3 move = ZeroVector3;
	//�P�ʃx�N�g��
	D3DXVECTOR3 nor = ZeroVector3;

	//���o�����ʒu
	D3DXVECTOR3 detectedPos = ZeroVector3;

	//�ʒu�̎擾
	D3DXVECTOR3 pos = GetPos();
	
	if (m_pView)
	{
		//���o�����ʒu�̎擾
		detectedPos = m_pView->GetDetectionPos();
	}

	//���݈ʒu�ƌ��o�����ʒu�܂ł̃x�N�g�����v�Z
	m_Distance = (detectedPos - pos);

	//�����̖ړI�̒l�̌v�Z
	SetRotDest();

	//�A�C�h�����[�V�����Đ�
	SetMotion(JAILER_MOTION::JAILER_MOTION_MOVE);

	//�����̐ݒ�
	SetSpeed(JAILER_CHASE_SPEED);

	//�ړ������̃x�N�g���̐��K��
	D3DXVec3Normalize(&nor, &m_Distance);

	//�ړ��ʂ�ݒ�
	move.x = nor.x * GetSpeed();
	move.z = nor.z * GetSpeed();

	//�ړ��ʂ̐ݒ�
	SetMove(move);
}

//=============================================================================
// �x�����
//=============================================================================
void CJailer::Caution(void)
{
#ifdef _DEBUG
	CDebugProc::Print("�x�����\n");
#endif
	const D3DXVECTOR3 rot = GetRot();

	if (m_nSwitchingTimer <= 30)
	{
		m_rotDest.y = rot.y+D3DXToRadian(10.0f);
	}
	else
	{
		m_rotDest.y = rot.y -D3DXToRadian(10.0f);
	}
	
}

//=============================================================================
// �b�����Z
//=============================================================================
int CJailer::AddTimer(int add)
{
	m_nSwitchingTimer += add;
	return m_nSwitchingTimer;
}

//=============================================================================
// �ړI�n�̐ݒ�
//=============================================================================
void CJailer::SettingPosDest(void)
{
	m_nIndex++;
	
	//�C���f�b�N�X���ő�l�ȏ�̏ꍇ
	if (m_nIndex >= CJailer::POS_DEST_MAX)
	{
		m_nIndex = CJailer::POS_DEST_LEFT_TOP;
	}
	//���̖ړI�̈ʒu��ݒ�
	m_posDest = aMoveSpot[m_nIndex];

	//�O��̃C���f�b�N�X���v�Z
	int IndexOld = m_nIndex - 1;

	//�O��̃C���f�b�N�X���ŏ��l��菬�����Ȃ����ꍇ
	if (IndexOld < CJailer::POS_DEST_LEFT_TOP)
	{
		IndexOld = POS_DEST_RIGHT_TOP;
	}

	//�O��̖ړI�n��ݒ肷��
	m_posDestOld = aMoveSpot[IndexOld];
}

//=============================================================================
// �����̖ړI�̒l�̐ݒ�
//=============================================================================
void CJailer::SetRotDest()
{
	D3DXVECTOR3	nor = ZeroVector3;

	//�ړ������̃x�N�g���̐��K��
	D3DXVec3Normalize(&nor, &m_Distance);

	//�ړ������ɑ΂��Ẳ�]�p�����߂�
	float angle = atan2f(-nor.x, -nor.z);

	//�ړI�̊p�x�֐ݒ�
	m_rotDest.y = angle;
}

#ifdef _DEBUG
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
	CDebugProc::Print("�y�ړI�̈ʒu�z X:%f,Y:%f,Z:%f\n", aMoveSpot[m_nIndex].x, aMoveSpot[m_nIndex].y, aMoveSpot[m_nIndex].z);
	CDebugProc::Print("�yIndex�z %d\n", m_nIndex);
	CDebugProc::Print("�y�ړ��ʁz X:%f,Y:%f,Z:%f\n", move.x, move.y, move.z);
	CDebugProc::Print("�ySpeed�z %f\n", Speed);
	CDebugProc::Print("�y�J�E���g�z %d\n", m_nSwitchingTimer);
}
#endif