#include "item_get_ui_baton.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"

CItemGetUIBaton::CItemGetUIBaton()
{
}

CItemGetUIBaton::~CItemGetUIBaton()
{
}

CItemGetUIBaton * CItemGetUIBaton::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	// CItemGetUIBaton�̃|�C���^
	CItemGetUIBaton *pItemGetUIBaton = nullptr;

	// nullcheck
	if (pItemGetUIBaton == nullptr)
	{
		// �������m��
		pItemGetUIBaton = new CItemGetUIBaton;

		// !nullcheck
		if (pItemGetUIBaton != nullptr)
		{
			// ����������
			pItemGetUIBaton->Init(Pos, Size);
		}
	}
	// �|�C���^��Ԃ�
	return pItemGetUIBaton;
}

HRESULT CItemGetUIBaton::Init(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	CItemGetUI::Init(Pos, Size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_Y));
	return S_OK;
}

void CItemGetUIBaton::Uninit(void)
{
	CItemGetUI::Uninit();
}

void CItemGetUIBaton::Draw(void)
{
	CItemGetUI::Draw();
}

void CItemGetUIBaton::Update(void)
{
	CItemGetUI::Update();
}
