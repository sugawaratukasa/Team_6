//=============================================================================
//
// �e�N�X�`���̊Ǘ��N���X [texture.cpp]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "texture.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTexture::CTexture()
{
	memset(m_apTexture, 0, sizeof(m_apTexture));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTexture::~CTexture()
{
	for (int nCount = 0; nCount < TEXTURE_TYPE_NUM_MAX; nCount++)
	{
		// ���O�f�[�^�̃N���A
		m_aTexFileName[nCount].clear();
	}
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CTexture * CTexture::Create(void)
{
	// �������m��
	CTexture *pTexture = new CTexture;

	// nullcheck
	if (pTexture)
	{
		// �����l
		pTexture->SetTextureName();
		return pTexture;
	}
	return pTexture;
}

//=============================================================================
// �e�N�X�`���̖��O��ݒ�
//=============================================================================
HRESULT CTexture::SetTextureName(void)
{
	// �ʏ�e�N�X�`��
	m_aTexFileName[TEXTURE_TYPE_NUM_NORMAL] =
	{
		{ "data/Texture/Floor_texture1.png" },
		{ "data/Texture/Sceneframe.png" },
		{ "data/Texture/SecCamFrame.png" },
		{ "data/Texture/camera_change.png" },
		{ "data/Texture/time_UI_frame.png" },
		{ "data/Texture/time_UI_guage.png" },
		{ "data/Texture/time_UI_guage2.png" },
		{ "data/Texture/number_01.png" },
		{ "data/Texture/UI_frameI.png" },
		{ "data/Texture/baton.png" },
		{ "data/Texture/Key_Item_PCroom.png" },
		{ "data/Texture/Key_Item_Warehouse.png" },
		{ "data/Texture/Key_Item_Prison.png" },
		{ "data/Texture/Key_Item_Jailer_room.png" },
		{ "data/Texture/Map_ItemUI.png" },
		{ "data/Texture/Button_Start.png" },		// �X�^�[�g�{�^��
		{ "data/Texture/Button_Ranking.png" },		// �����L���O�{�^��
		{ "data/Texture/Button_Exit.png" },			// �I���{�^��
		{ "data/Texture/Button_ReturnGame.png" },	// �Q�[���ɖ߂�{�^��
		{ "data/Texture/Button_ReturnTitle.png" },	// �^�C�g���ɖ߂�{�^��
		{ "data/Texture/Button_HowTo.png" },		// ��������{�^��
		{ "data/Texture/bg_title.png" },			// �^�C�g���w�i
		{ "data/Texture/title_logo.png" },			// �^�C�g�����S
		{ "data/Texture/UI_frameI_Select.png" },
		{ "data/Texture/map_texture.png" },
		{ "data/Texture/y.png" },
		{ "data/Texture/Ranking_bg.png" },
		{ "data/Texture/ui_number.png" },
		{ "data/Texture/jailer_key_guid.png" },
		{ "data/Texture/pc_room_key_guid.png" },
		{ "data/Texture/electrical_key_guid.png" },
		{ "data/Texture/storage_key_guid.png" },
		{ "data/Texture/baton_guid_texture.png" },
		{ "data/Texture/map_guid_texture.png" },
		{ "data/Texture/pause_logo.png" },
		{ "data/Texture/black.png" },
		{ "data/Texture/log_01_player1.png" },
		{ "data/Texture/log_01_player2.png" },
		{ "data/Texture/control_key.png" },
		{ "data/Texture/control_key_guid.png" },
		{ "data/Texture/electrical_key.png" },
		{ "data/Texture/map1.png" },
		{ "data/Texture/map2.png" },
		{ "data/Texture/guid_bg.png" },
		{ "data/Texture/gameover.png" },
		{ "data/Texture/Player_Log/Player_1/log_01_player1.png" },
		{ "data/Texture/Player_Log/Player_1/log_02_player1.png" },
		{ "data/Texture/Player_Log/Player_1/log_03_player1.png" },
		{ "data/Texture/Player_Log/Player_1/log_04_player1.png" },
		{ "data/Texture/Player_Log/Player_1/log_05_player1.png" },
		{ "data/Texture/Player_Log/Player_1/log_06_player1.png" },
		{ "data/Texture/Player_Log/Player_1/log_07_player1.png" },
		{ "data/Texture/Player_Log/Player_1/log_08_player1.png" },
		{ "data/Texture/Player_Log/Player_2/log_01_player2.png" },
		{ "data/Texture/Player_Log/Player_2/log_02_player2.png" },
		{ "data/Texture/Player_Log/Player_2/log_03_player2.png" },
		{ "data/Texture/Player_Log/Player_2/log_04_player2.png" },
		{ "data/Texture/Player_Log/Player_2/log_05_player2.png" },
		{ "data/Texture/Player_Log/Player_2/log_06_player2.png" },
		{ "data/Texture/Player_Log/Player_2/log_07_player2.png" },
		{ "data/Texture/Player_Log/Player_2/log_08_player2.png" },
		{ "data/Texture/Floor_Texture2.png" },
		{ "data/Texture/Floor_Texture3.png" },
		{ "data/Texture/Floor_Texture4.png" },
		{ "data/Texture/Clear_Time_BG.png" },
		{ "data/Texture/caveatbar.png" },
		{ "data/Texture/Question.png" },
		{ "data/Texture/Anger.png" },
		};

	// �����e�N�X�`��
	m_aTexFileName[TEXTURE_TYPE_NUM_SEPARATE] =
	{

	};

	return E_NOTIMPL;
}

//=============================================================================
// �S�Ẵe�N�X�`�����[�h
//=============================================================================
void CTexture::LoadAll(void)
{
	// �ʏ�e�N�X�`��
	NormalTexLoad();

	// �����e�N�X�`��
	SeparateTexLoad();
}

//=============================================================================
// �S�Ẵe�N�X�`���A�����[�h
//=============================================================================
void CTexture::UnLoadAll(void)
{
	// �ʏ�e�N�X�`��
	NormalTexUnLoad();

	// �����e�N�X�`��
	SeparateTexUnLoad();
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CTexture::NormalTexLoad(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	size_t size = m_aTexFileName[TEXTURE_TYPE_NUM_NORMAL].size();

	// �e�N�X�`���̓ǂݍ���
	for (size_t nCount = 0; nCount < size; nCount++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aTexFileName[TEXTURE_TYPE_NUM_NORMAL][nCount].data(), &m_apTexture[nCount]);
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CTexture::NormalTexUnLoad(void)
{
	for (int nCount = 0; nCount < TEXTURE_NUM_MAX; nCount++)
	{
		if (m_apTexture[nCount] != nullptr)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = nullptr;
		}
	}
}

//=============================================================================
// �����e�N�X�`���̃��[�h
//=============================================================================
HRESULT CTexture::SeparateTexLoad(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	size_t size = m_aTexFileName[TEXTURE_TYPE_NUM_SEPARATE].size();

	// �����e�N�X�`���̓ǂݍ���
	for (size_t nCount = 0; nCount < size; nCount++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aTexFileName[TEXTURE_TYPE_NUM_SEPARATE][nCount].data(), &m_apSeparateTexture[nCount].pSeparateTexture);
	}
	return S_OK;
}

//=============================================================================
// �����e�N�X�`���̃A�����[�h
//=============================================================================
void CTexture::SeparateTexUnLoad(void)
{
	// �e�N�X�`���̉��
	for (int nCount = 0; nCount < SEPARATE_TEX_MAX; nCount++)
	{
		if (m_apSeparateTexture[nCount].pSeparateTexture != nullptr)
		{
			m_apSeparateTexture[nCount].pSeparateTexture->Release();
			m_apSeparateTexture[nCount].pSeparateTexture = nullptr;
		}
	}
}

//=============================================================================
// �e�N�X�`�����
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEXTURE_TYPE Tex_Num)
{
	if (Tex_Num < TEXTURE_NUM_MAX)
	{
		if (m_apTexture[Tex_Num] != nullptr)
		{
			return m_apTexture[Tex_Num];
		}
	}

	return nullptr;
}

//=============================================================================
// �����e�N�X�`�����
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetSeparateTexture(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// �z���菬����������
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// NULLcheck
		if (m_apSeparateTexture[SepaTex_Type].pSeparateTexture != nullptr)
		{
			// �e�N�X�`�����
			return m_apSeparateTexture[SepaTex_Type].pSeparateTexture;
		}
	}

	return nullptr;
}

//=============================================================================
// �����e�N�X�`���̏��
//=============================================================================
D3DXVECTOR2 CTexture::GetSparateTexInfo(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// �z���菬����������
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// �e�N�X�`�����
		return m_apSeparateTexture[SepaTex_Type].m_TexInfo;
	}

	return D3DXVECTOR2(0.0f, 0.0f);
}

//=============================================================================
// �����e�N�X�`���̃��[�v�t���O
//=============================================================================
bool CTexture::GetSparateTexLoop(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// �z���菬����������
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// �e�N�X�`�����
		return m_apSeparateTexture[SepaTex_Type].bLoop;
	}

	return false;
}