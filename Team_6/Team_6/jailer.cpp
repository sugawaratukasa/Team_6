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

//=============================================================================
//�}�N����`
//=============================================================================
#define JAILER_SPEED (10.0f)	//����
#define MOVE_TEST D3DXVECTOR3(0.0f, 0.0f, -2.0f)

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
	m_nIndex = 0;
	m_posDest = ZeroVector3;
	m_pFan3d = nullptr;
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
	SetMotion(JAILER_MOTION_MOVE);

	//�����̐ݒ�
	SetSpeed(JAILER_SPEED);

	SetUseShadow();

	// �e�̌���
	SetShadowRotCalculation();
	m_posDest = posdest[0];

	SetPos(m_posDest);

	//���E�̃N���G�C�g
	m_pFan3d = CFan3D::Create(D3DXVECTOR3(m_posDest.x, 20.0f, m_posDest.z), ZeroVector3, 8, D3DCOLOR_RGBA(255, 0, 0, 255));

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

	//�ړ�����
	Move();

	//m_pState->Update(this);
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

	D3DXVECTOR3 postodest = (m_posDest - pos);

	/*if (postodest.x < 0.0f)
	{
		if (postodest.z > 0.0f)
		{
				m_nIndex++;

				if (m_nIndex >= CJailer::POS_DEST_MAX)
				{
					m_nIndex = CJailer::POS_DEST_LEFT_TOP;
				}

				m_posDest = posdest[m_nIndex];
			
		}
	}*/
	if (postodest == ZeroVector3)
	{
		m_nIndex++;

		if (m_nIndex >= CJailer::POS_DEST_MAX)
		{
			m_nIndex = CJailer::POS_DEST_LEFT_TOP;
		}

		m_posDest = posdest[m_nIndex];
	}
	
	//�ړ������̃x�N�g���̐��K��
	D3DXVec3Normalize(&nor, &postodest);

	//�ړ������ɑ΂��Ẳ�]�p�����߂�
	angle = atan2f(-nor.x, -nor.z);

	//�ړI�̊p�x�֐ݒ�
	m_rotDest.y = angle;

	//�ړ��ʂ�ݒ�
	move.x = nor.x * GetSpeed();
	move.z = nor.z * GetSpeed();

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
	rot += (m_rotDest - rot)*0.1f;

	//�����ݒ�
	SetRot(rot);

	//�ړ��ʂ̐ݒ�
	SetMove(move);
	
	if (m_pFan3d)
	{
		m_pFan3d->SetRotation(rot);									//��̌����̐ݒ�
		m_pFan3d->SetPosition(D3DXVECTOR3(pos.x, 500.0f, pos.z));	//��̈ʒu�̐ݒ�
	}

	CDebugProc::Print("=====================Jailer=====================\n");
	CDebugProc::Print("�y�����z X:%f,Y:%f,Z:%f\n", rot.x, rot.y, rot.z);
	CDebugProc::Print("�y�ړI�̌����i�x���@�j�z %f\n", D3DXToDegree(m_rotDest.y));
	CDebugProc::Print("�y���݂̌����i�x���@�j�z %f\n", D3DXToDegree(rot.y));
	CDebugProc::Print("�y�ʒu�z X:%f,Y:%f,Z:%f\n", pos.x, pos.y, pos.z);
	CDebugProc::Print("�y�ړI�̈ʒu�z X:%f,Y:%f,Z:%f\n", posdest[m_nIndex].x, posdest[m_nIndex].y, posdest[m_nIndex].z);
	CDebugProc::Print("�y�ړI-�ʒu�z X:%f,Y:%f,Z:%f\n", postodest.x, postodest.y, postodest.z);
	CDebugProc::Print("�yIndex�z %d\n", m_nIndex);
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
void CJailer::ChangeState(CJailerState * state)
{
	m_pState = state;
	m_pState->Init(this);
}

//=============================================================================
// �ǐ�
//=============================================================================
void CJailer::Chase()
{
}

bool CJailer::IsDistanceToPlayer(float distance, bool outside)
{
	if (outside == true)
	{
		return GetDistance() <= distance ? true : false;
	}
	return GetDistance() >= distance ? true : false;
}

//�v���C���[�Ƃ̋�����
float CJailer::GetDistance()
{
	float X = (m_posX - m_pPlayer->GetPos().x)*(m_posX - m_pPlayer->GetPos().x);
	float Z = (m_posZ - m_pPlayer->GetPos().z)*(m_posZ - m_pPlayer->GetPos().z);

	return sqrt(X+Z);
}
