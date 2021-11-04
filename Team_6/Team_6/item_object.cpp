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

//=============================================================================
// �}�N����`
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CItemObject::CItemObject(PRIORITY Priority) : CModel(Priority)
{
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
	// ����������
	CModel::Init(pos, rot);
	CModelCollisionBox::Create(pos, rot, this);
	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CItemObject::Uninit(void)
{
	// �I������
	CModel::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CItemObject::Update(void)
{
	// �X�V����
	CModel::Update();
	// �Փˏ����֐��Ăяo��
	Collision();
}
//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CItemObject::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=============================================================================
// �Փˏ����֐�
// Author : Nikaido Taichi
//=============================================================================
void CItemObject::Collision(void)
{
	// �ʒu���擾����
	D3DXVECTOR3 Position = GetPos();
	// �T�C�Y���擾����
	D3DXVECTOR3 Size = GetSize();
	// �v���C���[�̃|�C���^
	CPlayer * apPlayer[MAX_PLAYER];
	// �v���C���[�̍ő吔����
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		// �v���C���[�̃|�C���^���擾����
		apPlayer[nCount] = CManager::GetModePtr()->GetPlayer(nCount);
		// !nullcheck
		if (apPlayer[nCount] != nullptr)
		{
			//�����v���C���[�̃A�C�e���̎擾�����ő�l�ȉ��̏ꍇ
			if (apPlayer[nCount]->GetItemCount() < MAX_ITEM)
			{
				// �v���C���[�̈ʒu���擾����
				D3DXVECTOR3 PlayerPosition = apPlayer[nCount]->GetPos();
				// �v���C���[�̃T�C�Y���擾����
				D3DXVECTOR3 PlayerSize = apPlayer[nCount]->GetSize();
				// �A�C�e���ƃv���C���[�̋�`�^�̓����蔻��
				if (CCollision::CollisionRectangleAndRectangle(Position, PlayerPosition, Size, PlayerSize) == true)
				{
					// �v���C���[�ɃA�C�e����ݒ肷��
					apPlayer[nCount]->SetItem(this->GetType(), this);
					// �I�������֐��Ăяo��
					Uninit();
					return;
				}
			}
		}
	}
}