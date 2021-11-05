//=============================================================================
// �v���C���[ [player.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "player.h"
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "input.h"
#include "joypad.h"
#include "camera.h"
#include "game.h"
#include "sound.h"
#include "time.h"
#include "collision.h"
#include "fade.h"
#include "texture.h"
#include "resource_manager.h"
#include "motion.h"
#include "character_collision_box.h"
#include "object.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define PLAYER_SPEED			(50.0f)									// �v���C���[�̈ړ���
#define STICK_SENSITIVITY		(50.0f)									// �X�e�B�b�N���x
#define PLAYER_ROT_SPEED		(0.1f)									// �L�����N�^�[�̉�]���鑬�x
#define SIZE					(D3DXVECTOR3 (100.0f,200.0f,100.0f))	// �T�C�Y
#define STICK_INPUT_ZONE		(100)									// �X�e�B�b�N�̓��͔͈�
#define STICK_INPUT_ZONE_2		(1000)									// �X�e�B�b�N�̓��͔͈�
#define STICK_INPUT_ZERO		(0)										// �X�e�B�b�N�̓��͒l0
#define MIN_LIFE				(0)										// ���C�t�̍ŏ�
#define LIFE					(100)									// ���C�t
#define ANGLE_45				(D3DXToRadian(45.0f))					// �p�x45
#define ANGLE_90				(D3DXToRadian(90.0f))					// �p�x90
#define ANGLE_135				(D3DXToRadian(135.0f))					// �p�x90
#define ANGLE_180				(D3DXToRadian(180.0f))					// �p�x180
#define ANGLE_270				(D3DXToRadian(270.0f))					// �p�x270
#define PARENT_NUM				(0)										// �e�̃i���o
#define MOVE_MIN				(0.0f)									// �ړ��ʂ̍ŏ�
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer::CPlayer(PRIORITY Priority) : CCharacter(Priority)
{
	// �A�C�e�����X�g�̍ő吔����
	for (int nCount = 0; nCount < CItemObject::ITEM_OBJECT_MAX; nCount++)
	{
		m_apItem[nCount] = nullptr;		// �A�C�e���̃|�C���^
	}
	m_nIncapacitatedTimeCount = 0;		// �s���s�\���ԃJ�E���g
	m_nItemCount = 0;					// �A�C�e���̏�����
	m_bIncapacitated = false;			// �s���s�\���z
}

//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ����������
	CCharacter::Init(pos, rot);

	// �T�C�Y�ݒ�
	SetSize(SIZE);

	// ���C�t�ݒ�
	SetLife(LIFE);

	// �X�s�[�h�ݒ�
	SetSpeed(PLAYER_SPEED);

	// �e
	SetUseShadow();

	// �e�̌���
	SetShadowRotCalculation();

	CCharacterCollisionBox::Create(pos, rot, this);

	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::Uninit(void)
{
	// �I��
	CCharacter::Uninit();
}

//=============================================================================
// �X�V�֐������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::Update(void)
{
	// �X�V
	CCharacter::Update();
	// �����s���s�\��Ԃ̏ꍇ
	if (m_bIncapacitated == true)
	{
		// �����s���s�\���ԃJ�E���g���w�莞�Ԃ�艺�̏ꍇ
		if (m_nIncapacitatedTimeCount <= INCAPACITATED_TIME)
		{
			// ���Z����
			m_nIncapacitatedTimeCount++;
		}
		else
		{
			// �s���s�\����������
			m_bIncapacitated = false;
		}
	}
}

//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::Draw(void)
{
	// �`��
	CCharacter::Draw();
}
//=============================================================================
// �}�b�v�Ƃ̓����蔻�菈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer::MapCollision(void)
{
	// CScene�̃|�C���^
	CScene *pScene = nullptr;

	// ���f���̏��擾
	CModelAnime *pAnime = GetModelAnime(PARENT_NUM);

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
					GetMove().y = MOVE_MIN;

					// �ʒu
					pos.y = (-ObjSize.y / DIVIDE_2 + ObjPos.y) - (size.y / DIVIDE_2);

					// �ʒu�ݒ�
					SetPos(pos);
				}
				// ��
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, ObjPos, size, ObjSize) == CCollision::SURFACE_UP)
				{
					// �ړ���0
					GetMove().y = MOVE_MIN;

					// �ʒu
					pos.y = (ObjSize.y / DIVIDE_2 + ObjPos.y) + (size.y / DIVIDE_2);

					// �ʒu�ݒ�
					SetPos(pos);
				}
				// ��
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, ObjPos, size, ObjSize) == CCollision::SURFACE_LEFT)
				{
					// �ړ���0
					GetMove().x = MOVE_MIN;

					// �ʒu
					pos.x = (-ObjSize.x / DIVIDE_2 + ObjPos.x) - (size.x / DIVIDE_2);

					// �ʒu�ݒ�
					SetPos(pos);
				}
				// �E
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, ObjPos, size, ObjSize) == CCollision::SURFACE_RIGHT)
				{
					// �ړ���0
					GetMove().x = MOVE_MIN;

					// �ʒu
					pos.x = (ObjSize.x / DIVIDE_2 + ObjPos.x) + (size.x / DIVIDE_2);

					// �ʒu�ݒ�
					SetPos(pos);
				}
				// ��O
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, ObjPos, size, ObjSize) == CCollision::SURFACE_PREVIOUS)
				{
					// �ړ���0
					GetMove().z = MOVE_MIN;

					// �ʒu
					pos.z = (-ObjSize.z / DIVIDE_2 + ObjPos.z) - (size.z / DIVIDE_2);

					// �ʒu�ݒ�
					SetPos(pos);
				}
				// ��
				else if (CCollision::ActiveCollisionRectangleAndRectangle(pos, posOld, ObjPos, size, ObjSize) == CCollision::SURFACE_BACK)
				{
					// �ړ���0
					GetMove().z = MOVE_MIN;

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