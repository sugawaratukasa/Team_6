//=============================================================================
// �A�C�e���I�u�W�F�N�g [item_object.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Nikaido Taichi
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "character.h"
#include "collision.h"
#include "game.h"
#include "player.h"
#include "item_object.h"
#include "game.h"
#include "model_collision_box.h"
#include "keyboard.h"
#include "joypad.h"
#include "scene.h"
#include "manager.h"
#include "resource_manager.h"
#include "sound.h"

//=============================================================================
// �}�N����`
// Author : Nikaido Taichi
//=============================================================================
#define COLLISION_SIZE (D3DXVECTOR3(550.0f,550.0f,550.0f))
//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CItemObject::CItemObject(PRIORITY Priority) : CScene(Priority)
{
	m_Position = ZeroVector3;		// �ʒu
	m_Size = ZeroVector3;			// �T�C�Y
	m_Rotation = ZeroVector3;		// ����
	m_Type = ITEM_OBJECT_NONE;		// �^�C�v
}
//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CItemObject::~CItemObject()
{
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CItemObject::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_Position = pos;
	m_Rotation = rot;
	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CItemObject::Uninit(void)
{
	Release();
}

//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CItemObject::Update(void)
{
	// �Փˏ����֐��Ăяo��
	Collision();
}
//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CItemObject::Draw(void)
{
}

//=============================================================================
// �Փˏ����֐�
// Author : Nikaido Taichi
//=============================================================================
void CItemObject::Collision(void)
{
	// �L�[�{�[�h�擾
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	// �p�b�h�擾
	CInputJoypad * pJoypad = CManager::GetJoypad();
	// �v���C���[�̈ʒu
	D3DXVECTOR3 PlayerPosition[MAX_PLAYER];
	// �v���C���[�̃T�C�Y
	D3DXVECTOR3 PlayerSize[MAX_PLAYER];
	// �v���C���[�̃|�C���^
	CPlayer * apPlayer[MAX_PLAYER];
	CSound * pSound = GET_SOUND_PTR;
	// �v���C���[�̍ő吔����
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		// �v���C���[�̃|�C���^���擾����
		apPlayer[nCount] = CManager::GetModePtr()->GetPlayer(nCount);
		// !nullcheck
		if (apPlayer[nCount] != nullptr)
		{
			// �v���C���[�̈ʒu���擾����
			PlayerPosition[nCount] = apPlayer[nCount]->GetPos();
			// �v���C���[�̃T�C�Y���擾����
			PlayerSize[nCount] = apPlayer[nCount]->GetSize();
			// �A�C�e���ƃv���C���[�̋�`�^�̓����蔻��
			if (CCollision::CollisionRectangleAndRectangle(m_Position, PlayerPosition[nCount], COLLISION_SIZE, PlayerSize[nCount]) == true)
			{
				if (nCount == CPlayer::PLAYER_1 && pKeyboard->GetTrigger(DIK_U) || nCount == CPlayer::PLAYER_2 && pKeyboard->GetTrigger(DIK_H))
				{
					if (apPlayer[nCount]->GetItemCount() < MAX_ITEM && apPlayer[nCount]->GetbGuidCreate() == false)
					{
						// �v���C���[�ɃA�C�e����ݒ肷��
						apPlayer[nCount]->SetAddbGetItem(this->GetType(), true);
						apPlayer[nCount]->SetbGuidCreate(this->GetType());
						pSound->CSound::Play(CSound::SOUND_SE_GET_ITEM);
						// �I�������֐��Ăяo��
						Uninit();
						return;
					}
				}
			}
		}
	}
}