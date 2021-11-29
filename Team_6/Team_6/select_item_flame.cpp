#include "select_item_flame.h"
#include "texture.h"
#include "manager.h"
#include "resource_manager.h"

CSelectItemFlame::CSelectItemFlame(PRIORITY Priority)
{
}

CSelectItemFlame::~CSelectItemFlame()
{
}

CSelectItemFlame * CSelectItemFlame::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CSelectItemFlame�̃|�C���^
	CSelectItemFlame *pSelectItemFlame = nullptr;

	// nullcheck
	if (pSelectItemFlame == nullptr)
	{
		// �������m��
		pSelectItemFlame = new CSelectItemFlame;

		// !nullcheck
		if (pSelectItemFlame != nullptr)
		{
			// ����������
			pSelectItemFlame->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pSelectItemFlame;
}

HRESULT CSelectItemFlame::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_SELECT_ITEM_FLAME));
	return S_OK;
}

void CSelectItemFlame::Uninit(void)
{
	CScene2D::Uninit();
}

void CSelectItemFlame::Update(void)
{
	CScene2D::Update();
}

void CSelectItemFlame::Draw(void)
{
	CScene2D::Draw();
}
