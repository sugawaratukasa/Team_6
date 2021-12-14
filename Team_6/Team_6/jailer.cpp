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
#include "jailer_spot.h"
#include "Jalier_MoveState.h"
#include "Jalier_MoveState.h"
#include "object.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define JAILER_NORMAL_SPEED (10.0f)							//�ʏ펞�̈ړ����x
#define JAILER_CHASE_SPEED (20.0f)							//�ǐՎ��̈ړ����x
#define JAILER_ROTSTION_RATE (0.1f)							//��]�̌W��
#define VIEW_POS_Y (70.0f)									//�����̍���
#define VIEW_POLYGON_NUM (8)								//�����̃|���S����
#define JAILER_SIZE (D3DXVECTOR3 (100.0f,200.0f,100.0f))	// �T�C�Y

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
	m_nSwitchingTimer = ZERO_INT;
	m_nNumber = ZERO_INT;
	m_fDestinationRange = ZERO_FLOAT;
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
	SetSpeed(0.0f);

	SetUseShadow();

	// �e�̌���
	SetShadowRotCalculation();

	//�����̔ԍ���ݒ�
	m_nNumber = m_nJailerTotal;

	//�X�|�b�g�N���X�̃N���G�C�g
	m_pSpot = CJailerSpot::Create(m_nNumber);

	//�ʒu�̐ݒ�
	SetPos(m_pSpot->GetSpotPos());

	//�ړI�n��ݒ�
	m_posDest = m_pSpot->ChangeTarget();

	//���E�̃N���G�C�g
	m_pView = CJailerView::Create(D3DXVECTOR3(m_posDest.x, VIEW_POS_Y, m_posDest.z), 
		ZeroVector3, VIEW_POLYGON_NUM, D3DCOLOR_RGBA(255, 0, 0, 255));

	//��Ԑݒ�
	m_pJailerState = CMoveState::GetInstance();

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

	MapCollision();
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

	if (m_fDestinationRange <= 5.0f)
	{
		//�ړI�n�̍Đݒ�
		SettingPosDest();
	}
}

//=============================================================================
// ���񃋁[�g�֖߂�
//=============================================================================
void CJailer::RetrunRoute(void)
{
	D3DXVECTOR3 move = ZeroVector3;

	//�P�ʃx�N�g��
	D3DXVECTOR3 nor = ZeroVector3;

	//���݈ʒu�ƌ��o�����ʒu�܂ł̃x�N�g�����v�Z
	m_Distance = (m_posDest - GetPos());

	//�ړI�n�Ǝ����̋������v�Z
	m_fDestinationRange = sqrtf((m_Distance.x * m_Distance.x) + (m_Distance.z * m_Distance.z));

	if (m_fDestinationRange > 5.0f)
	{
		//�X�e�[�g���ړ��ɕύX
		ChangeState(CMoveState::GetInstance());

		return;
	}

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
		m_pView->JailerCaution(true);
	}

	//���݈ʒu�ƌ��o�����ʒu�܂ł̃x�N�g�����v�Z
	m_Distance = (detectedPos - GetPos());

	//�ړI�n�Ǝ����̋������v�Z
	m_fDestinationRange = sqrtf((m_Distance.x * m_Distance.x) + (m_Distance.z * m_Distance.z));

	if (m_fDestinationRange > 5.0f)
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

		//���[�g�̌���
		m_posDest = m_pSpot->RouteSearch(GetPos(), detectedPos);
	}

	//�ړ��ʂ̐ݒ�
	SetMove(move);
}

//=============================================================================
// �x�����
//=============================================================================
void CJailer::Caution(void)
{
}

//=============================================================================
//�U������
//=============================================================================
void CJailer::Attack(void)
{
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
	//�ړI�n�̍X�V
	m_posDest = m_pSpot->ChangeTarget();
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
		bIsHit = false;
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

			bIsHit = true;
		}
		//�E
		else if (nHitSurface == CCollision::SURFACE_RIGHT)
		{
			pos.x = ((playerSize.x / 2) + playerPos.x) + (size.x / 2);

			SetPos(pos);
			bIsHit = true;
		}
		//��
		else if (nHitSurface == CCollision::SURFACE_PREVIOUS)
		{
			pos.z = ((-playerSize.z / 2) + playerPos.z) - (size.z / 2);

			SetPos(pos);

			bIsHit = true;
		}
		//��O
		else if (nHitSurface == CCollision::SURFACE_BACK)
		{
			pos.z = ((playerSize.z / 2) + playerPos.z) + (size.z / 2);

			SetPos(pos);

			bIsHit = true;
		}

		if (bIsHit)
		{
			//�v���C���[�ɑ΂��A�N�V��������
			pPlayer->PrisonWarp();
		}
	}

	return bIsHit;
}

void CJailer::MapCollision(void)
{
	// CScene�̃|�C���^
	CScene *pScene = nullptr;

	// ���f���̏��擾
	CModelAnime *pAnime = GetModelAnime(0);

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �ʒu�擾
	D3DXVECTOR3 posOld = GetOldPos();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// nullcheck
	if (pScene == nullptr)
	{
		// �擪�̃|�C���^�擾
		pScene = GetTop(CScene::PRIORITY_MAP);

		// !nullcheck
		if (pScene != nullptr)
		{
			// Map�I�u�W�F�N�g�̓����蔻��
			while (pScene != nullptr) // nullptr�ɂȂ�܂ŉ�
			{
				// ���݂̃|�C���^
				CScene *pSceneCur = pScene->GetNext();

				// �ʒu�擾
				D3DXVECTOR3 ObjPos = ((CObject*)pScene)->GetPos();

				// �T�C�Y�擾
				D3DXVECTOR3 ObjSize = ((CObject*)pScene)->GetSize();

				//�ǂ��̖ʂɓ����������擾
				//��
				if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, ObjPos, size, ObjSize) == CCollision::SURFACE_DOWN)
				{
					// �ړ���0
					GetMove().y = 0.0f;

					// �ʒu
					pos.y = (-ObjSize.y / DIVIDE_2 + ObjPos.y) - (size.y / DIVIDE_2);

					// �ʒu�ݒ�
					SetPos(pos);
				}
				// ��
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, ObjPos, size, ObjSize) == CCollision::SURFACE_UP)
				{
					// �ړ���0
					GetMove().y = 0.0f;

					// �ʒu
					pos.y = (ObjSize.y / DIVIDE_2 + ObjPos.y) + (size.y / DIVIDE_2);

					// �ʒu�ݒ�
					SetPos(pos);
				}
				// ��
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, ObjPos, size, ObjSize) == CCollision::SURFACE_LEFT)
				{
					// �ړ���0
					GetMove().x = 0.0f;

					// �ʒu
					pos.x = (-ObjSize.x / DIVIDE_2 + ObjPos.x) - (size.x / DIVIDE_2);

					// �ʒu�ݒ�
					SetPos(pos);
				}
				// �E
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, ObjPos, size, ObjSize) == CCollision::SURFACE_RIGHT)
				{
					// �ړ���0
					GetMove().x = 0.0f;

					// �ʒu
					pos.x = (ObjSize.x / DIVIDE_2 + ObjPos.x) + (size.x / DIVIDE_2);

					// �ʒu�ݒ�
					SetPos(pos);
				}
				// ��O
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, ObjPos, size, ObjSize) == CCollision::SURFACE_PREVIOUS)
				{
					// �ړ���0
					GetMove().z = 0.0f;

					// �ʒu
					pos.z = (-ObjSize.z / DIVIDE_2 + ObjPos.z) - (size.z / DIVIDE_2);

					// �ʒu�ݒ�
					SetPos(pos);
				}
				// ��
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, ObjPos, size, ObjSize) == CCollision::SURFACE_BACK)
				{
					// �ړ���0
					GetMove().z = 0.0f;

					// �ʒu
					pos.z = (ObjSize.z / DIVIDE_2 + ObjPos.z) + (size.z / DIVIDE_2);

					// �ʒu�ݒ�
					SetPos(pos);
				}

				// ���̃|�C���^�擾
				pScene = pSceneCur;
			}
		}
	}
}

void CJailer::SetRetrunData(void)
{
	m_posDest = m_pSpot->BackToRoute(GetPos());
}
