#include "item_get_ui_storage_key.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"

CItemGetUIStorageKey::CItemGetUIStorageKey()
{
}

CItemGetUIStorageKey::~CItemGetUIStorageKey()
{
}

CItemGetUIStorageKey * CItemGetUIStorageKey::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	// CItemGetUIStorageKey�̃|�C���^
	CItemGetUIStorageKey *pItemGetUIStorageKey = nullptr;

	// nullcheck
	if (pItemGetUIStorageKey == nullptr)
	{
		// �������m��
		pItemGetUIStorageKey = new CItemGetUIStorageKey;

		// !nullcheck
		if (pItemGetUIStorageKey != nullptr)
		{
			// ����������
			pItemGetUIStorageKey->Init(Pos, Size);
		}
	}
	// �|�C���^��Ԃ�
	return pItemGetUIStorageKey;
}

HRESULT CItemGetUIStorageKey::Init(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	CItemGetUI::Init(Pos, Size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_Y));
	return S_OK;
}

void CItemGetUIStorageKey::Uninit(void)
{
	CItemGetUI::Uninit();
}

void CItemGetUIStorageKey::Draw(void)
{
	CItemGetUI::Draw();
}

void CItemGetUIStorageKey::Update(void)
{
	CItemGetUI::Update();
}
