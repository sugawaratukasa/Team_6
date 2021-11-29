#include "item_get_ui_prison_key.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"

CItemGetUIPrisonKey::CItemGetUIPrisonKey()
{
}

CItemGetUIPrisonKey::~CItemGetUIPrisonKey()
{
}

CItemGetUIPrisonKey * CItemGetUIPrisonKey::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	// CItemGetUIPrisonKey�̃|�C���^
	CItemGetUIPrisonKey *pItemGetUIPrisonKey = nullptr;

	// nullcheck
	if (pItemGetUIPrisonKey == nullptr)
	{
		// �������m��
		pItemGetUIPrisonKey = new CItemGetUIPrisonKey;

		// !nullcheck
		if (pItemGetUIPrisonKey != nullptr)
		{
			// ����������
			pItemGetUIPrisonKey->Init(Pos,Size);
		}
	}
	// �|�C���^��Ԃ�
	return pItemGetUIPrisonKey;
}

HRESULT CItemGetUIPrisonKey::Init(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	CItemGetUI::Init(Pos, Size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_Y));
	return S_OK;
}

void CItemGetUIPrisonKey::Uninit(void)
{
	CItemGetUI::Uninit();
}

void CItemGetUIPrisonKey::Draw(void)
{
	CItemGetUI::Draw();
}

void CItemGetUIPrisonKey::Update(void)
{
	CItemGetUI::Update();
}
