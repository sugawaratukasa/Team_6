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
#include "spot.h"
#include "game.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define JAILER_NORMAL_SPEED (10.0f)	//�ʏ펞�̈ړ����x
#define JAILER_CHASE_SPEED (20.0f)	//�ǐՎ��̈ړ����x
#define JAILER_ROTSTION_RATE (0.1f)	//��]�̌W��
#define VIEW_POS_Y (70.0f)			//�����̍���
#define VIEW_POLYGON_NUM (8)		//�����̃|���S����

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
	m_fDestinationRange = ZERO_FLOAT;
	m_pView = nullptr;		//��N���X�̃|�C���^�ϐ�
	m_pJailerState = nullptr;
	m_pSpot = nullptr;
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

	//�e�̎g�p�ݒ�
	SetUseShadow();

	// �e�̌����̐ݒ�
	SetShadowRotCalculation();

	//�����̔ԍ���ݒ�
	m_nNumber = m_nJailerTotal;
	//m_nNumber = 1;
	//�X�|�b�g�N���X�̃N���G�C�g
	m_pSpot = CSpot::Create();

	//�Ŏ�̈ړ��X�|�b�g���̎擾
	m_MoveSpot = m_pSpot->GetJailerMoveSpotList(m_nNumber);

	m_nIndex = 1;
	
	D3DXVECTOR3 posTest = m_MoveSpot[ZERO_INT];
	//�ʒu�̐ݒ�
	SetPos(posTest);

	//�ړI�n��ݒ�
	m_posDest = m_MoveSpot[m_nIndex];

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
	//�ʒu�̎擾
	D3DXVECTOR3 pos = GetPos();

	//�O��ʒu�̐ݒ�
	SetPosOld(pos);

	//�L�����N�^�[�̍X�V����
	CCharacter::Update();

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
	D3DXVECTOR3 move = ZeroVector3;

	//�P�ʃx�N�g��
	D3DXVECTOR3 nor = ZeroVector3;

	//���ݒn�ƖړI�n�܂ł̃x�N�g�����v�Z
	m_Distance = m_posDest - GetPos();

	//�ړI�n�Ǝ����̋������v�Z
	m_fDestinationRange = sqrtf((m_Distance.x * m_Distance.x) + (m_Distance.z * m_Distance.z));

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
	//�O��̌����֊m�F
	m_Distance = (m_posDestOld - GetPos());

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
	D3DXVECTOR3 move = ZeroVector3;
	//�P�ʃx�N�g��
	D3DXVECTOR3 nor = ZeroVector3;

	//���o�����ʒu
	D3DXVECTOR3 detectedPos = ZeroVector3;
	
	if (m_pView)
	{
		//���o�����ʒu�̎擾
		detectedPos = m_pView->GetDetectionPos();
	}
	
	//���݈ʒu�ƌ��o�����ʒu�܂ł̃x�N�g�����v�Z
	m_Distance = (detectedPos - GetPos());

	//�ړI�n�Ǝ����̋������v�Z
	m_fDestinationRange = sqrtf((m_Distance.x * m_Distance.x) + (m_Distance.z * m_Distance.z));

	if (m_fDestinationRange > 10.0f)
	{
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
	}

	//�ړ��ʂ̐ݒ�
	SetMove(move);
}

//=============================================================================
// �x�����
//=============================================================================
void CJailer::Caution(void)
{
	const D3DXVECTOR3 rot = GetRot();
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
	//�ړ��X�|�b�g�̗v�f�����擾
	int nSpotNum = m_MoveSpot.size();

	//�O��̖ړI�n��ۑ�
	m_posDestOld = m_posDest;

	//�C���f�b�N�X����i�߂�
	m_nIndex++;
	
	//�C���f�b�N�X���v�f�����傫���Ȃ����Ƃ��͏C��
	if (m_nIndex >= nSpotNum)
	{
		m_nIndex = ZERO_INT;
	}

	//�ړI�n�̍X�V
	m_posDest = m_MoveSpot[m_nIndex];	
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
}
#endif