//=============================================================================
// �}�b�v���� [item_map.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Nikaido Taichi
//=============================================================================
#include "main.h"
#include "item_map.h"
#include "map1_texture.h"
#include "map2_texture.h"
#include "player_1.h"
#include "player_2.h"
#include "manager.h"
#include "mode_base.h"
#include "item_object_map.h"
#include "player.h"
#include "game.h"
#include "keyboard.h"
#include "joypad.h"

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CItemMap::CItemMap()
{
	memset(m_abCreateMap,false,sizeof(m_abCreateMap));	// �}�b�v�e�N�X�`���������
	m_pMap1Texture = nullptr;				// �}�b�v1�e�N�X�`���̃|�C���^
	m_pMap2Texture = nullptr;				// �}�b�v2�e�N�X�`���̃|�C���^
}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CItemMap::~CItemMap()
{
}

//=============================================================================
// ���������֐�
// Author : Nikaido Taichi
//=============================================================================
CItemMap * CItemMap::Create(void)
{
	// CBatonTexture�̃|�C���^
	CItemMap *pItemMap = nullptr;

	// nullcheck
	if (pItemMap == nullptr)
	{
		// �������m��
		pItemMap = new CItemMap;

		// !nullcheck
		if (pItemMap != nullptr)
		{
			// ����������
			pItemMap->Init();
		}
	}
	// �|�C���^��Ԃ�
	return pItemMap;
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CItemMap::Init(void)
{
	// �v���C���[�Ƀ}�b�v�擾��Ԃ�^����
	SetPlayerItemGetList(CPlayer::ITEM_MAP);
	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CItemMap::Uninit(void)
{
	if (m_pMap1Texture != nullptr)
	{
		m_pMap1Texture->Uninit();
		m_pMap1Texture = nullptr;
	}
	if (m_pMap2Texture != nullptr)
	{
		m_pMap2Texture->Uninit();
		m_pMap2Texture = nullptr;
	}
}

//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CItemMap::Update(void)
{
	// �v���C���[�A�C�e���擾�����擾����
	PlayerItemGet();
}

//=============================================================================
// �v���C���[�A�C�e���擾���擾�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CItemMap::PlayerItemGet(void)
{
	// �v���C���[�̃|�C���^
	CPlayer * apPlayer[MAX_PLAYER];
	// �v���C���[�̃A�C�e���������
	bool abPlayerGetItem[MAX_PLAYER];
	// �v���C���[�̍ő吔����
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		// �v���C���[�̃|�C���^���擾����
		apPlayer[nCount] = CManager::GetModePtr()->GetPlayer(nCount);
		// �v���C���[�|�C���^��nullptr�`�F�b�N
		if (apPlayer[nCount] != nullptr)
		{
			// �v���C���[�̃A�C�e��������Ԃ��擾����
			abPlayerGetItem[nCount] = apPlayer[nCount]->GetbItem(CPlayer::ITEM_MAP);
			// �}�b�v���������֐�
			MapCreate(nCount, abPlayerGetItem[nCount]);
		}
	}
}

//=============================================================================
// �}�b�v�e�N�X�`�����������֐�
// Author : Nikaido Taichi
//=============================================================================
void CItemMap::MapCreate(int nPlayer, bool bItem)
{
	// �L�[�{�[�h�擾
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	// �p�b�h�擾
	CInputJoypad * pJoypad = CManager::GetJoypad();
	if (bItem == true)
	{
		if (nPlayer == 0 && pKeyboard->GetTrigger(DIK_B))
		{
			// �}�b�v�e�N�X�`���𐶐����ĂȂ��ꍇ
			if (m_abCreateMap[nPlayer] == false)
			{
				// �}�b�v�e�N�X�`���|�C���^��nullptr�`�F�b�N
				if (m_pMap1Texture == nullptr)
				{
					// �}�b�v�e�N�X�`���𐶐�����
					m_pMap1Texture = CMap1Texture::Create(D3DXVECTOR3(SCREEN_WIDTH / 4 + SCREEN_WIDTH / 2 * nPlayer, SCREEN_HEIGHT / 2 + 50.0f , 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2 - 75.0f, SCREEN_HEIGHT - 150.0f, 0.0f));
					// �}�b�v�e�N�X�`��������Ԃ�true�ɂ���
					m_abCreateMap[nPlayer] = true;
				}
			}
			// �}�b�v�e�N�X�`���𐶐����Ă���ꍇ
			else
			{
				if (m_pMap1Texture != nullptr)
				{
					// �}�b�v�e�N�X�`���̏I�������֐��Ăяo��
					m_pMap1Texture->Uninit();
					// �}�b�v�e�N�X�`���̃|�C���^���������ɂ���
					m_pMap1Texture = nullptr;
					// �}�b�v�e�N�X�`��������Ԃ�false�ɂ���
					m_abCreateMap[nPlayer] = false;
				}
			}
		}
		if (nPlayer == 1 && pKeyboard->GetTrigger(DIK_N))
		{
			// �}�b�v�e�N�X�`���𐶐����ĂȂ��ꍇ
			if (m_abCreateMap[nPlayer] == false)
			{
				// �}�b�v�e�N�X�`���|�C���^��nullptr�`�F�b�N
				if (m_pMap2Texture == nullptr)
				{
					// �}�b�v�e�N�X�`���𐶐�����
					m_pMap2Texture = CMap2Texture::Create(D3DXVECTOR3(SCREEN_WIDTH / 4 + SCREEN_WIDTH / 2 * nPlayer, SCREEN_HEIGHT / 2 + 50.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2 - 75.0f, SCREEN_HEIGHT - 150.0f, 0.0f));
					// �}�b�v�e�N�X�`��������Ԃ�true�ɂ���
					m_abCreateMap[nPlayer] = true;
				}
			}
			// �}�b�v�e�N�X�`���𐶐����Ă���ꍇ
			else
			{
				// �}�b�v�e�N�X�`���|�C���^��nullptr�`�F�b�N
				if (m_pMap2Texture != nullptr)
				{
					// �}�b�v�e�N�X�`���̏I�������֐��Ăяo��
					m_pMap2Texture->Uninit();
					// �}�b�v�e�N�X�`���̃|�C���^���������ɂ���
					m_pMap2Texture = nullptr;
					// �}�b�v�e�N�X�`��������Ԃ�false�ɂ���
					m_abCreateMap[nPlayer] = false;
				}
			}
		}
	}
}

//=============================================================================
// �}�b�v�A�C�e�����������֐�
// Author : Nikaido Taichi
//=============================================================================
void CItemMap::ItemCreate(int nPlayer)
{
	CPlayer * pPlayer;
	// �v���C���[�̃|�C���^���擾����
	pPlayer = CManager::GetModePtr()->GetPlayer(nPlayer);
	// �v���C���[�̈ʒu���擾����
	D3DXVECTOR3 PlayerPos;
	PlayerPos = pPlayer->GetPos();
	// �}�b�v�A�C�e���𐶐�����
	CMapObject::Create(PlayerPos, ZeroVector3);
}
