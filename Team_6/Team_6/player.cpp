//=============================================================================
// �v���C���[ [player.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Nikaido Taichi
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
#include "item_baton.h"
#include "item_jailer_room_key.h"
#include "item_map.h"
#include "item_pc_room_key.h"
#include "item_prison_key.h"
#include "item_storage_key.h"

#include "ui_player2_item.h"
#include "door_collision.h"
#include "item_guid_prison_key.h"
#include "item_control_room_key.h"
#include "door_collision.h"
#include "duct_collision.h"

//=============================================================================
// �}�N����`
// Author : Nikaido Taichi
//=============================================================================

#define PLAYER_SPEED			(25.0f)									// �v���C���[�̈ړ���
#define STICK_SENSITIVITY		(50.0f)									// �X�e�B�b�N���x
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
#define DUCT_POS_LEFT			(D3DXVECTOR3(DuctPos.x + 100.0f,DuctPos.y,DuctPos.z))	// ���_�N�g�ʒu
#define DUCT_POS_RIGHT			(D3DXVECTOR3(DuctPos.x - 100.0f,DuctPos.y,DuctPos.z))	// �E�_�N�g�ʒu
//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CPlayer::CPlayer(PRIORITY Priority) : CCharacter(Priority)
{
	m_nItemCount = ZERO_INT;								// �A�C�e���̏�����
	m_nItemSortCount = ZERO_INT;							// �A�C�e���\�[�g�p�J�E���g
	m_nIncapacitatedTimeCount = ZERO_INT;					// �s���s�\���ԃJ�E���g
	m_bGoal = false;										// �S�[�����
	m_bIncapacitated = false;								// �s���s�\���
	memset(m_abGetItem, false, sizeof(m_abGetItem));		// �A�C�e�����擾���Ă邩
	memset(m_bItempCreate, false, sizeof(m_bItempCreate));	// �A�C�e���|�C���^����������

	memset(m_bUICreate, false, sizeof(m_bUICreate));		// UI�������
	m_bGuidCreate = false;
	m_Type = PLAYER_NONE;
	for (int nCount = ZERO_INT; nCount < ITEM_MAX; nCount++)
	{
		m_pItemGetUI[nCount] = nullptr;
	}
	m_pUI = nullptr;										// UI�|�C���^

	for (int nCount = ZERO_INT; nCount < MAX_ITEM; nCount++)
	{
		m_pItem[nCount] = nullptr;							// �A�C�e���|�C���^
	}

}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
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

	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayer::Uninit(void)
{
	// �I��
	CCharacter::Uninit();
	// UI�|�C���^��nullptr�`�F�b�N
	if (m_pUI != nullptr)
	{
		// UI�|�C���^�̏I�������֐��Ăяo��
		m_pUI->Uninit();
	}
}

//=============================================================================
// �X�V�֐������֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayer::Update(void)
{
	// �X�V
	CCharacter::Update();
	D3DXVECTOR3 Position = GetPos();
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
			// �s���s�\���ԃJ�E���g������������
			m_nIncapacitatedTimeCount = ZERO_INT;
		}
	}
	// �}�b�v�Ƃ̓����蔻��
	MapCollision();

	// �����J������
	DoorOpen();

	// �A�C�e���_�N�g�󂯓n������
	Item_DuctPass();
	// UI�|�C���^��nullptr�`�F�b�N
	if (m_pUI != nullptr)
	{
		// UI�|�C���^�̍X�V�����֐��Ăяo��
		m_pUI->Update();
	}
	// �ő�A�C�e������������

	for (int nCount = ZERO_INT; nCount < MAX_ITEM; nCount++)
	{
		// �A�C�e���|�C���^��nullptr�`�F�b�N
		if (m_pItem[nCount] != nullptr)
		{
			// �A�C�e���̍X�V�����֐��Ăяo��
			m_pItem[nCount]->Update();
		}

	}
}

//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayer::Draw(void)
{
	// �`��
	CCharacter::Draw();
}

//=============================================================================
// �A�C�e�����ʐ��������֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayer::ItemEffectCreate(int ItemGetList)
{
	switch (ItemGetList)
	{
		// �S���̌�
	case ITEM_KEY_ELECTRICAL_ROOM:
		if (m_abGetItem[ItemGetList] == true)
		{
			// �S���̌��̃|�C���^�𐶐�����
			m_pItem[m_nItemCount] = CPrisonKey::Create();
			// �A�C�e���J�E���g�����Z����
			m_nItemCount++;
		}
		break;
		// �q�ɂ̌�
	case ITEM_KEY_STORAGE:
		if (m_abGetItem[ItemGetList] == true)
		{
			// �q�Ɍ��ʂ̃|�C���^�𐶐�����
			m_pItem[m_nItemCount] = CStorageKey::Create();
			// �A�C�e���J�E���g�����Z����
			m_nItemCount++;
		}
		break;
		// �Ŏ玺�̌�
	case ITEM_KEY_JAILER_ROOM:
		if (m_abGetItem[ItemGetList] == true)
		{
			// �Ŏ玺���ʂ̃|�C���^�𐶐�����
			m_pItem[m_nItemCount] = CJailerRoomKey::Create();
			// �A�C�e���J�E���g�����Z����
			m_nItemCount++;
		}
		break;
		// PC���̌�

		if (m_abGetItem[ItemGetList] == true)
		{
			// PC�����ʂ̃|�C���^�𐶐�����
			m_pItem[m_nItemCount] = CPCRoomKey::Create();
			// �A�C�e���J�E���g�����Z����
			m_nItemCount++;
		}
		break;
	case ITEM_KEY_CONTROL_ROOM:
		if (m_abGetItem[ItemGetList] == true)
		{
			// PC�����ʂ̃|�C���^�𐶐�����
			m_pItem[m_nItemCount] = CControlRoomKey::Create();
			// �A�C�e���J�E���g�����Z����
			m_nItemCount++;
		}
		break;
		// �x�_
	case ITEM_BATON:
		if (m_abGetItem[ItemGetList] == true)
		{
			// �x�_���ʂ̃|�C���^�𐶐�����
			m_pItem[m_nItemCount] = CItemBaton::Create();
			// �A�C�e���J�E���g�����Z����
			m_nItemCount++;
		}
		break;
		// �}�b�v
	case ITEM_MAP:
		if (m_abGetItem[ItemGetList] == true)
		{
			// �n�}���ʂ̃|�C���^�𐶐�����
			m_pItem[m_nItemCount] = CItemMap::Create();
			// �A�C�e���J�E���g�����Z����
			m_nItemCount++;
		}
		break;
	default:
		break;
	}
}

//=============================================================================
// �A�C�e�����ʏ����������֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayer::ItemEffectUninit(void)
{

	for (int nCount = ZERO_INT; nCount < MAX_ITEM; nCount++)
	{
		// �A�C�e���|�C���^��nullptr�`�F�b�N
		if (m_pItem[nCount] != nullptr)
		{
			// �A�C�e���̏I�������֐��Ăяo��
			m_pItem[nCount]->Uninit();
			// �A�C�e���|�C���^������������
			m_pItem[nCount] = nullptr;
		}
	}
	// �A�C�e���J�E���g������������
	m_nItemCount = ZERO_INT;
}

//=============================================================================
// �A�C�e���폜�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayer::ItemDelete(int nPlayer)
{
	// �L�[�{�[�h�擾
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	// �p�b�h�擾
	CInputJoypad * pJoypad = CManager::GetJoypad();
	CSound * pSound = GET_SOUND_PTR;
	// 1P�̃A�C�e���I����͏���

	if (nPlayer == PLAYER_1 && pKeyboard->GetTrigger(DIK_I) || pJoypad != nullptr && pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_L_TRIGGER, nPlayer))
	{

		if (nPlayer == PLAYER_1 && m_nItemSortCount > 0)
		{
			// �A�C�e���\�[�g�p�J�E���g�����Z����
			m_nItemSortCount--;
		}
	}
	// 1P�̃A�C�e���I����͏���

	if (nPlayer == PLAYER_1 && pKeyboard->GetTrigger(DIK_O) || pJoypad != nullptr && pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R_TRIGGER, nPlayer))
	{

		if (nPlayer == PLAYER_1 && m_nItemSortCount < 2)
		{
			// �A�C�e���\�[�g�p�J�E���g�����Z����
			m_nItemSortCount++;
		}
	}
	// 1P&2P�̃A�C�e���폜���͏���

	if (nPlayer == PLAYER_1 && pKeyboard->GetTrigger(DIK_P) || nPlayer == PLAYER_2 && pKeyboard->GetTrigger(DIK_L) || pJoypad != nullptr && pJoypad->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_Y,nPlayer))
	{
		// �A�C�e���|�C���^��nullptr�`�F�b�N
		if (m_pItem[m_nItemSortCount] != nullptr)
		{

			// UI������	
			m_pUI->Uninit();
			// �I�����Ă���A�C�e���̎�ނ��擾����
			int nItemType = m_pItem[m_nItemSortCount]->GetItemType();
			// �I�����Ă���A�C�e���̎擾��Ԃ�false�ɂ���
			SetSubbGetItem(nItemType, false);
			pSound->Play(CSound::SOUND_SE_RELEASE_ITEM);
			// �A�C�e���𐶐�����
			m_pItem[m_nItemSortCount]->ItemCreate(nPlayer);
			// �A�C�e�����ʏ����������֐��Ăяo��
			ItemEffectUninit();
			// �A�C�e���̍ő吔����

			for (int nCount = ZERO_INT; nCount < ITEM_MAX; nCount++)
			{
				// �A�C�e�����ʐ��������֐��Ăяo��
				ItemEffectCreate(nCount);
			}
		}
	}
}


//=============================================================================
// �擾�A�C�e�����Z�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayer::SetAddbGetItem(int nItem, bool bGet)
{
	// �v���C���[�̃A�C�e���������
	m_abGetItem[nItem] = bGet;
	// �A�C�e�����ʂ𐶐�
	ItemEffectCreate(nItem);
}

//=============================================================================
// �擾�A�C�e�����Z�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayer::SetSubbGetItem(int nItem, bool bGet)
{
	// �v���C���[�̃A�C�e���������
	m_abGetItem[nItem] = bGet;
}

//=============================================================================
// �}�b�v�Ƃ̓����蔻�菈���֐�
// Author : Nikaido Taichi
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
//=============================================================================
// �����J������
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::DoorOpen(void)
{
	// CScene�̃|�C���^
	CScene *pScene = nullptr;

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();
	CSound * pSound = GET_SOUND_PTR;
	// nullcheck
	if (pScene == nullptr)
	{
		// �擪�̃|�C���^�擾
		pScene = GetTop(CScene::PRIORITY_OBJ_COLLISION);

		// !nullcheck
		if (pScene != nullptr)
		{
			// ����p�I�u�W�F�擾
			while (pScene != nullptr) // nullptr�ɂȂ�܂ŉ�
			{
				// ���݂̃|�C���^
				CScene *pSceneCur = pScene->GetNext();

				// �ʒu�擾
				D3DXVECTOR3 ObjPos = ((CDoor_Collision*)pScene)->GetPos();

				// �T�C�Y�擾
				D3DXVECTOR3 ObjSize = ((CDoor_Collision*)pScene)->GetSize();

				// �����̂̔���
				if (CCollision::CollisionRectangleAndRectangle(pos, ObjPos, size, ObjSize) == true)
				{
					// �������b�N��Ԃ̏ꍇ
					if (((CDoor_Collision*)pScene)->GetLock() == true)
					{
						// �L�[�{�[�h�擾
						CInputKeyboard *pKeyboard = CManager::GetKeyboard();

						// �h�A�̎�ގ擾
						int nDoorType = ((CDoor_Collision*)pScene)->GetType();

						// �h�A�ɑΉ������A�C�e�����������Ă���ꍇ
						if (m_abGetItem[ITEM_KEY_ELECTRICAL_ROOM] == true && nDoorType == CDoor_Collision::TYPE_ELECTRICAL_ROOM ||
							m_abGetItem[ITEM_KEY_STORAGE] == true && nDoorType == CDoor_Collision::TYPE_STORAGE ||
							m_abGetItem[ITEM_KEY_JAILER_ROOM] == true && nDoorType == CDoor_Collision::TYPE_JAILER_ROOM ||
							m_abGetItem[ITEM_KEY_CONTROL_ROOM] == true && nDoorType == CDoor_Collision::TYPE_CONTROL_ROOM ||
							m_abGetItem[ITEM_KEY_CAMERA_ROOM] == true && nDoorType == CDoor_Collision::TYPE_CAMERA_ROOM ||
							m_abGetItem[ITEM_BATON] == true && nDoorType == CDoor_Collision::TYPE_SWITCH || 
							nDoorType == CDoor_Collision::TYPE_LEVER)
						{
							// F�������ꂽ�ꍇ
							if (pKeyboard->GetTrigger(DIK_F))
							{
								// �S���̃h�A�̏ꍇ
								if (nDoorType == CDoor_Collision::TYPE_ELECTRICAL_ROOM)
								{
									pSound->CSound::Play(CSound::SOUND_SE_OPEN_PRISON);
								}
								else
								{
									pSound->CSound::Play(CSound::SOUND_SE_OPEN_DOOR);
								}
								// �����J��
								((CDoor_Collision*)pScene)->Open();
							}
						}
					}
				}
				// ���̃|�C���^�擾
				pScene = pSceneCur;
			}
		}
	}
}
//=============================================================================
// �_�N�g�̏���
// Author : SugawaraTsukasa
//=============================================================================
void CPlayer::Item_DuctPass(void)
{
	// CScene�̃|�C���^
	CScene *pScene = nullptr;

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// �T�E���h�̃|�C���^
	CSound * pSound = GET_SOUND_PTR;

	// nullcheck
	if (pScene == nullptr)
	{
		// �擪�̃|�C���^�擾
		pScene = GetTop(CScene::PRIORITY_DUCT);

		// !nullcheck
		if (pScene != nullptr)
		{
			// ����p�I�u�W�F�擾
			while (pScene != nullptr) // nullptr�ɂȂ�܂ŉ�
			{
				// ���݂̃|�C���^
				CScene *pSceneCur = pScene->GetNext();

				// �ʒu�擾
				D3DXVECTOR3 DuctPos = ((CDuct_Collision*)pScene)->GetPos();

				// �T�C�Y�擾
				D3DXVECTOR3 DuctSize = ((CDuct_Collision*)pScene)->GetSize();

				// �����̂̔���
				if (CCollision::CollisionRectangleAndRectangle(pos, DuctPos, size, DuctSize) == true)
				{
					// �L�[�{�[�h�擾
					CInputKeyboard *pKeyboard = CManager::GetKeyboard();

					// F�������ꂽ�ꍇ
					if (pKeyboard->GetTrigger(DIK_F))
					{
						// �I�����Ă���A�C�e���̎�ނ��擾����
						int nItemType = m_pItem[m_nItemSortCount]->GetItemType();

						// �������̏ꍇ
						if (nItemType >= ITEM_KEY_ELECTRICAL_ROOM && nItemType <= ITEM_KEY_CAMERA_ROOM)
						{
							// UI������	
							m_pUI->Uninit();

							// �I�����Ă���A�C�e���̎擾��Ԃ�false�ɂ���
							SetSubbGetItem(nItemType, false);

							// ��ގ擾
							int nDuctType = ((CDuct_Collision*)pScene)->GetType();

							// �_�N�g�^�C�v��LEFT�̏ꍇ
							if (nDuctType == CDuct_Collision::TYPE_LEFT)
							{
								// �A�C�e���𐶐�����
								m_pItem[m_nItemSortCount]->DuctPass(DUCT_POS_RIGHT);
							}
							// �_�N�g�^�C�v��RIGHT�̏ꍇ
							if (nDuctType == CDuct_Collision::TYPE_RIGHT)
							{
								// �A�C�e���𐶐�����
								m_pItem[m_nItemSortCount]->DuctPass(DUCT_POS_LEFT);
							}

							// �A�C�e�����ʏ����������֐��Ăяo��
							ItemEffectUninit();

							// �A�C�e���̍ő吔����
							for (int nCount = ZERO_INT; nCount < ITEM_MAX; nCount++)
							{
								// �A�C�e�����ʐ��������֐��Ăяo��
								ItemEffectCreate(nCount);
							}
						}
					}
				}
				// ���̃|�C���^�擾
				pScene = pSceneCur;
			}
		}
	}
}
