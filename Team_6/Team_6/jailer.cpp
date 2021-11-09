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
#include "collision.h"
#include "character_collision_box.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define JAILER_NORMAL_SPEED (10.0f)	//�ʏ펞�̈ړ����x
#define JAILER_CHASE_SPEED (20.0f)	//�ǐՎ��̈ړ����x
#define JAILER_ROTSTION_RATE (0.1f)	//��]�̌W��
#define VIEW_POS_Y (70.0f)			//�����̍���
#define VIEW_POLYGON_NUM (8)		//�����̃|���S����
#define JAILER_SIZE (D3DXVECTOR3 (100.0f,200.0f,100.0f))	// �T�C�Y
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
	m_pView = nullptr;		//��N���X�̃|�C���^�ϐ�
	m_pJailerState = nullptr;
	m_rotDest = ZeroVector3;
	m_posDest = ZeroVector3;
	m_posDestOld = ZeroVector3;
	m_nIndex = ZERO_INT;
	m_nSwitchingTimer = ZERO_INT;
	m_nNumber = ZERO_INT;
	m_fDestinationRange = ZERO_FLOAT;
	
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

	//�T�C�Y�̐ݒ�
	SetSize(JAILER_SIZE);

	CCharacterCollisionBox::Create(GetPos(), GetRot(), this);

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

#ifdef _DEBUG
	CDebugProc::Print("�y�ړI�ʒu�Ƃ̋����zX:%f\n",m_fDestinationRange);
	CDebugProc::Print("�y�ړI�ʒu�zX:%f,Y:%f,Z:%f\n", m_Distance.x, m_Distance.y, m_Distance.z);

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

	//���ݒn�ƖړI�n�܂ł̃x�N�g�����v�Z
	m_Distance = m_posDest - GetPos();

	//�ړI�n�Ǝ����̋����̒������v�Z
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
#ifdef _DEBUG
	CDebugProc::Print("�ҋ@���\n");
#endif

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
#ifdef _DEBUG
	CDebugProc::Print("�ǐՏ��\n");
#endif
	D3DXVECTOR3 move = ZeroVector3;
	//�P�ʃx�N�g��
	D3DXVECTOR3 nor = ZeroVector3;

	//���o�����ʒu
	D3DXVECTOR3 detectedPos = ZeroVector3;
	
	if (m_pView)
	{
		//���o�����ʒu�̎擾
		detectedPos = m_pView->GetDetectionPos();
#ifdef _DEBUG
		CDebugProc::Print("�y�v���C���[�����o�����ʒu�zX:%f,Y:%f,Z:%f\n", detectedPos.x, detectedPos.y, detectedPos.z);
#endif
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
#ifdef _DEBUG
	CDebugProc::Print("�x�����\n");
#endif
	const D3DXVECTOR3 rot = GetRot();
}

//=============================================================================
//�U������
//=============================================================================
void CJailer::Attack(void)
{
#ifdef _DEBUG
	CDebugProc::Print("�U�����\n");
#endif
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
	//���݂̖ړI�n��O��̖ړI�n�Ƃ��ĕۑ�
	m_posDestOld = aMoveSpot[m_nIndex];

	//�ړI�n�̃C���f�b�N�X�����Z
	m_nIndex++;
	
	//�C���f�b�N�X���ő�l�ȏ�̏ꍇ
	if (m_nIndex >= CJailer::POS_DEST_MAX)
	{
		//�ŏ��̃C���f�b�N�X�֖߂�
		m_nIndex = CJailer::POS_DEST_LEFT_TOP;
	}

	//���̖ړI�̈ʒu��ݒ�
	m_posDest = aMoveSpot[m_nIndex];
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

//=============================================================================
// �v���C���[�Ƃ̓����蔻��
//=============================================================================
bool CJailer::IsHitPlayer(void)
{
	//�ʒu�̎擾
	D3DXVECTOR3 pos = GetPos();

	//�O��ʒu�̎擾
	D3DXVECTOR3 posOld = GetOldPos();

	//�T�C�Y�̎擾
	D3DXVECTOR3 size = GetSize();
	
	bool bIsHit = false;	//�����������ǂ����̃t���O

	for (int nCntPlayer = ZERO_INT; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		//�v���C���[�̃|�C���^���擾
		CPlayer *pPlayer = CManager::GetModePtr()->GetPlayer(nCntPlayer);

		//�v���C���[�̈ʒu�̎擾
		D3DXVECTOR3 playerPos = pPlayer->GetPos();

		//�v���C���[�̃T�C�Y�̎擾
		D3DXVECTOR3 playerSize = pPlayer->GetSize();

		//�v���C���[�Ƃ̔���
		int nHitSurface = CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, playerPos, size, playerSize);

		//��
		if (nHitSurface == CCollision::SURFACE_LEFT)
		{
			pos.x = ((-playerSize.x / 2) + playerPos.x) - (size.x / 2);

			SetPos(pos);

#ifdef _DEBUG
			CDebugProc::Print("�v���C���[%d�ƍ�������������\n", nCntPlayer);
#endif

			bIsHit = true;
		}
		//�E
		else if (nHitSurface == CCollision::SURFACE_RIGHT)
		{
			pos.x = ((playerSize.x / 2) + playerPos.x) + (size.x / 2);

			SetPos(pos);
#ifdef _DEBUG
			CDebugProc::Print("�v���C���[%d�ƉE������������\n", nCntPlayer);
#endif
			bIsHit = true;
		}
		//��
		else if (nHitSurface == CCollision::SURFACE_PREVIOUS)
		{
			pos.z = ((-playerSize.z / 2) + playerPos.z) - (size.z / 2);

			SetPos(pos);

#ifdef _DEBUG
			CDebugProc::Print("�v���C���[%d�Ɖ�������������\n", nCntPlayer);
#endif
			bIsHit = true;
		}
		//��O
		else if (nHitSurface == CCollision::SURFACE_BACK)
		{
			pos.z = ((playerSize.z / 2) + playerPos.z) + (size.z / 2);

			SetPos(pos);

#ifdef _DEBUG
			CDebugProc::Print("�v���C���[%d�Ǝ�O������������\n", nCntPlayer);
#endif
			bIsHit = true;
		}
		else
		{
#ifdef _DEBUG
			CDebugProc::Print("�v���C���[%d�Ƃ͓������Ă��Ȃ�\n", nCntPlayer);
#endif
		}

		if (bIsHit)
		{
			//�v���C���[�ɑ΂��A�N�V��������
			//pPlayer->
		}
	}

	return bIsHit;
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