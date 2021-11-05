//=============================================================================
// �v���C���[UI�}�l�[�W���[ [player_ui_manager.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Nikaido Taichi
//=============================================================================
#include "main.h"
#include "manager.h"
#include "mode_base.h"
#include "player_ui_manager.h"
#include "ui_flame_texture.h"
#include "player.h"
#include "player_1.h"
#include "player_2.h"
#include "item_object.h"
#include "baton_texture.h"
#include "map_texture.h"
#include "key_texture.h"

//=============================================================================
// �}�N����`
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CPlayerUIManager::CPlayerUIManager()
{
	for (int nCount = 0; nCount < 2; nCount++)
	{
		m_anItemTextureCount[nCount] = 0;
	}
	for (int nCountPlayer = 0; nCountPlayer < 2; nCountPlayer++)
	{
		for (int nCountTexture = 0; nCountTexture < CItemObject::ITEM_OBJECT_MAX; nCountTexture++)
		{
			m_apItemTexture[nCountPlayer][nCountTexture] = nullptr;
		}
	}
}
//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CPlayerUIManager::~CPlayerUIManager()
{
}

CPlayerUIManager * CPlayerUIManager::Create(void)
{
	// CPlayerUIManager�̃|�C���^
	CPlayerUIManager *pPlayerUIManager = nullptr;

	// nullcheck
	if (pPlayerUIManager == nullptr)
	{
		// �������m��
		pPlayerUIManager = new CPlayerUIManager;

		// !nullcheck
		if (pPlayerUIManager != nullptr)
		{
			// ����������
			pPlayerUIManager->Init();
		}
	}
	// �|�C���^��Ԃ�
	return pPlayerUIManager;
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CPlayerUIManager::Init(void)
{
	CUIFlameTexture::Create(D3DXVECTOR3(110.0f, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(200.0f, 60.0f, 0.0f));
	CUIFlameTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 110.0f, SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(200.0f, 60.0f, 0.0f));
	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayerUIManager::Uninit(void)
{
}

//=============================================================================
// �X�V�֐������֐�
// Author : Nikaido Taichi
//=============================================================================
void CPlayerUIManager::Update(void)
{
	UICreate();
}

void CPlayerUIManager::UICreate(void)
{
	// �v���C���[�̃|�C���^
	CPlayer * apPlayer[MAX_PLAYER];
	// �v���C���[�̃A�C�e�����
	CItemObject *  apPlayerItem[MAX_PLAYER][CItemObject::ITEM_OBJECT_MAX];
	// �v���C���[�J�E���g
	int nCountPlayer = 0;
	// �A�C�e���J�E���g
	int nCountItem = 0;
	// �v���C���[�̍ő吔����
	for (nCountPlayer = 0; nCountPlayer < MAX_PLAYER; nCountPlayer++)
	{
		// �v���C���[�̃|�C���^���擾����
		apPlayer[nCountPlayer] = CManager::GetModePtr()->GetPlayer(nCountPlayer);
		// �A�C�e���̍ő吔����
		for (nCountItem = 0; nCountItem < CItemObject::ITEM_OBJECT_MAX; nCountItem++)
		{
			// �v���C���[�̃A�C�e�������擾����
			apPlayerItem[nCountPlayer][nCountItem] = apPlayer[nCountPlayer]->GetItem(nCountItem);
			if (apPlayerItem[nCountPlayer][nCountItem] != nullptr)
			{
				switch (nCountItem)
				{
				case CItemObject::ITEM_OBJECT_KEY_PRISON:
					if (nCountPlayer == 0)
					{
						if (m_apItemTexture[0][CItemObject::ITEM_OBJECT_KEY_PRISON] == nullptr)
						{
							m_apItemTexture[0][CItemObject::ITEM_OBJECT_KEY_PRISON] = CKeyTexture::Create(D3DXVECTOR3(50 + 65.0f * m_anItemTextureCount[0], SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
							m_anItemTextureCount[0]++;
						}
					}
					if (nCountPlayer == 1)
					{
						{
							if (m_apItemTexture[1][CItemObject::ITEM_OBJECT_KEY_PRISON] == nullptr)
							{
								m_apItemTexture[1][CItemObject::ITEM_OBJECT_KEY_PRISON] = CKeyTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_anItemTextureCount[1], SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
								m_anItemTextureCount[1]++;
							}
						}
					}
					break;
				case CItemObject::ITEM_OBJECT_KEY_STORAGE:
					if (nCountPlayer == 0)
					{
						if (m_apItemTexture[0][CItemObject::ITEM_OBJECT_KEY_STORAGE] == nullptr)
						{
							m_apItemTexture[0][CItemObject::ITEM_OBJECT_KEY_STORAGE] = CKeyTexture::Create(D3DXVECTOR3(50 + 65.0f * m_anItemTextureCount[0], SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
							m_anItemTextureCount[0]++;
						}
					}
					if (nCountPlayer == 1)
					{
						if (m_apItemTexture[1][CItemObject::ITEM_OBJECT_KEY_STORAGE] == nullptr)
						{
							m_apItemTexture[1][CItemObject::ITEM_OBJECT_KEY_STORAGE] = CKeyTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_anItemTextureCount[1], SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
							m_anItemTextureCount[1]++;
						}
					}
					break;
				case CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM:
					if (nCountPlayer == 0)
					{
						if (m_apItemTexture[0][CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM] == nullptr)
						{
							m_apItemTexture[0][CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM] = CKeyTexture::Create(D3DXVECTOR3(50 + 65.0f * m_anItemTextureCount[0], SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
							m_anItemTextureCount[0]++;
						}
					}
					if (nCountPlayer == 1)
					{
						if (m_apItemTexture[1][CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM] == nullptr)
						{
							m_apItemTexture[1][CItemObject::ITEM_OBJECT_KEY_JAILER_ROOM] = CKeyTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_anItemTextureCount[1], SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
							m_anItemTextureCount[1]++;
						}
					}
					break;
				case CItemObject::ITEM_OBJECT_KEY_PC_ROOM:
					if (nCountPlayer == 0)
					{
						if (m_apItemTexture[0][CItemObject::ITEM_OBJECT_KEY_PC_ROOM] == nullptr)
						{
							m_apItemTexture[0][CItemObject::ITEM_OBJECT_KEY_PC_ROOM] = CKeyTexture::Create(D3DXVECTOR3(50 + 65.0f * m_anItemTextureCount[0], SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
							m_anItemTextureCount[0]++;
						}
					}
					if (nCountPlayer == 1)
					{
						if (m_apItemTexture[1][CItemObject::ITEM_OBJECT_KEY_PC_ROOM] == nullptr)
						{
							m_apItemTexture[1][CItemObject::ITEM_OBJECT_KEY_PC_ROOM] = CKeyTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_anItemTextureCount[1], SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
							m_anItemTextureCount[1]++;
						}
					}
					break;
				case CItemObject::ITEM_OBJECT_BATON:
					if (nCountPlayer == 0)
					{
						if (m_apItemTexture[0][CItemObject::ITEM_OBJECT_BATON] == nullptr)
						{
							m_apItemTexture[0][CItemObject::ITEM_OBJECT_BATON] = CBatonTexture::Create(D3DXVECTOR3(50 + 65.0f * m_anItemTextureCount[0], SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
							m_anItemTextureCount[0]++;
						}
					}
					if (nCountPlayer == 1)
					{
						if (m_apItemTexture[1][CItemObject::ITEM_OBJECT_BATON] == nullptr)
						{
							m_apItemTexture[1][CItemObject::ITEM_OBJECT_BATON] = CBatonTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_anItemTextureCount[1], SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
							m_anItemTextureCount[1]++;
						}
					}
					break;
				case CItemObject::ITEM_OBJECT_MAP:
					if (nCountPlayer == 0)
					{
						if (m_apItemTexture[0][CItemObject::ITEM_OBJECT_MAP] == nullptr)
						{
							m_apItemTexture[0][CItemObject::ITEM_OBJECT_MAP] = CMapTexture::Create(D3DXVECTOR3(50 + 65.0f * m_anItemTextureCount[0], SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
							m_anItemTextureCount[0]++;
						}
					}
					if (nCountPlayer == 1)
					{
						if (m_apItemTexture[1][CItemObject::ITEM_OBJECT_MAP] == nullptr)
						{
							m_apItemTexture[1][CItemObject::ITEM_OBJECT_MAP] = CMapTexture::Create(D3DXVECTOR3(SCREEN_WIDTH - 45.0f - 65.0f * m_anItemTextureCount[1], SCREEN_HEIGHT - 40.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
							m_anItemTextureCount[1]++;
						}
					}
					break;
				default:
					break;
				}
			}
		}
	}
}