#include "item_get_ui_map.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"

CItemGetUIMap::CItemGetUIMap()
{
}

CItemGetUIMap::~CItemGetUIMap()
{
}

CItemGetUIMap * CItemGetUIMap::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	// CItemGetUIMap�̃|�C���^
	CItemGetUIMap *pItemGetUIMap = nullptr;

	// nullcheck
	if (pItemGetUIMap == nullptr)
	{
		// �������m��
		pItemGetUIMap = new CItemGetUIMap;

		// !nullcheck
		if (pItemGetUIMap != nullptr)
		{
			// ����������
			pItemGetUIMap->Init(Pos, Size);
		}
	}
	// �|�C���^��Ԃ�
	return pItemGetUIMap;
}

HRESULT CItemGetUIMap::Init(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	CItemGetUI::Init(Pos, Size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_Y));
	return S_OK;
}

void CItemGetUIMap::Uninit(void)
{
	CItemGetUI::Uninit();
}

void CItemGetUIMap::Draw(void)
{
	CItemGetUI::Draw();
}

void CItemGetUIMap::Update(void)
{
	CItemGetUI::Update();
}
