#include "item_get_ui_jailer_key.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"

CItemGetUIJailerKey::CItemGetUIJailerKey()
{
}

CItemGetUIJailerKey::~CItemGetUIJailerKey()
{
}

CItemGetUIJailerKey * CItemGetUIJailerKey::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	// CItemGetUIMap�̃|�C���^
	CItemGetUIJailerKey *pItemGetUIJailerKey = nullptr;

	// nullcheck
	if (pItemGetUIJailerKey == nullptr)
	{
		// �������m��
		pItemGetUIJailerKey = new CItemGetUIJailerKey;

		// !nullcheck
		if (pItemGetUIJailerKey != nullptr)
		{
			// ����������
			pItemGetUIJailerKey->Init(Pos, Size);
		}
	}
	// �|�C���^��Ԃ�
	return pItemGetUIJailerKey;
}

HRESULT CItemGetUIJailerKey::Init(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	CItemGetUI::Init(Pos, Size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_Y));
	return S_OK;
}

void CItemGetUIJailerKey::Uninit(void)
{
	CItemGetUI::Uninit();
}

void CItemGetUIJailerKey::Draw(void)
{
	CItemGetUI::Draw();
}

void CItemGetUIJailerKey::Update(void)
{
	CItemGetUI::Update();
}
