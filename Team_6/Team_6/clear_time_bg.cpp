//=============================================================================
// �N���A�^�C���w�i [clear_time_bg.cpp]
// Author : SugawaraTsuksa
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "clear_time_bg.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"
//=============================================================================
// �}�N����`
// Author : SugawaraTsuksa
//=============================================================================
#define SIZE_VALUE	(D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f))
//=============================================================================
// �R���X�g���N�^
// Author : SugawaraTsuksa
//=============================================================================
CClear_Time_bg::CClear_Time_bg()
{
}

//=============================================================================
// �f�X�g���N�^
// Author : SugawaraTsuksa
//=============================================================================
CClear_Time_bg::~CClear_Time_bg()
{
}
//=============================================================================
// �C���X�^���X��������
// Author : SugawaraTsuksa
//=============================================================================
CClear_Time_bg * CClear_Time_bg::Create(D3DXVECTOR3 pos)
{
	// CClear_Time_bg�̃|�C���^
	CClear_Time_bg *pClear_Time_bg = nullptr;

	// nullptr�̏ꍇ
	if (pClear_Time_bg == nullptr)
	{
		// �������m��
		pClear_Time_bg = new CClear_Time_bg;

		// !nullcheck
		if (pClear_Time_bg != nullptr)
		{
			pClear_Time_bg->Init(pos);
		}
	}
	// �|�C���^��Ԃ�
	return pClear_Time_bg;
}
//=============================================================================
// ����������
// Author : SugawaraTsuksa
//=============================================================================
HRESULT CClear_Time_bg::Init(D3DXVECTOR3 pos)
{
	CScene2D::Init(pos, SIZE_VALUE);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_CLEAR_TIME_BG));

	return S_OK;
}

//=============================================================================
// �I������
// Author : SugawaraTsuksa
//=============================================================================
void CClear_Time_bg::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
// Author : SugawaraTsuksa
//=============================================================================
void CClear_Time_bg::Update(void)
{
	CScene2D::Update();
}

//=============================================================================
// �`�揈��
// Author : SugawaraTsuksa
//=============================================================================
void CClear_Time_bg::Draw(void)
{
	CScene2D::Draw();
}