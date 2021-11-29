#include "item_get_ui_pc_room_key.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"

CItemGetUIPCRoomKey::CItemGetUIPCRoomKey()
{
}

CItemGetUIPCRoomKey::~CItemGetUIPCRoomKey()
{
}

CItemGetUIPCRoomKey * CItemGetUIPCRoomKey::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	// CItemGetUIPCRoomKey�̃|�C���^
	CItemGetUIPCRoomKey *pItemGetUIPCRoomKey = nullptr;

	// nullcheck
	if (pItemGetUIPCRoomKey == nullptr)
	{
		// �������m��
		pItemGetUIPCRoomKey = new CItemGetUIPCRoomKey;

		// !nullcheck
		if (pItemGetUIPCRoomKey != nullptr)
		{
			// ����������
			pItemGetUIPCRoomKey->Init(Pos, Size);
		}
	}
	// �|�C���^��Ԃ�
	return pItemGetUIPCRoomKey;
}

HRESULT CItemGetUIPCRoomKey::Init(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	CItemGetUI::Init(Pos, Size);
	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_Y));
	return S_OK;
}

void CItemGetUIPCRoomKey::Uninit(void)
{
	CItemGetUI::Uninit();
}

void CItemGetUIPCRoomKey::Draw(void)
{
	CItemGetUI::Draw();
}

void CItemGetUIPCRoomKey::Update(void)
{
	CItemGetUI::Update();
}
