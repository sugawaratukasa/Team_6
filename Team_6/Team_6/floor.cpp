//=============================================================================
// �� [floor.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"
#include "collision.h"
#include "player.h"
#include "game.h"
#include "floor.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define COL (D3DCOLOR_RGBA(255, 255, 255, 255))	// �F
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CFloor::CFloor(PRIORITY Priority) : CScene3D(Priority)
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CFloor::~CFloor()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CFloor * CFloor::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CFloor�̃|�C���^
	CFloor *pFloor = nullptr;

	// nullcheck
	if (pFloor == nullptr)
	{
		// �������m��
		pFloor = new CFloor;

		// !nullcheck
		if (pFloor != nullptr)
		{
			// ����������
			pFloor->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pFloor;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CFloor::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CScene3D::Init(pos, size);

	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_FLOOR));

	// �����ݒ�
	SetRot(ZeroVector3);

	// �F�ݒ�
	SetColor(COL);

	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CFloor::Uninit(void)
{
	// �I������
	CScene3D::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CFloor::Update(void)
{
	// �X�V����
	CScene3D::Update();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CFloor::Draw(void)
{
	// �`�揈��
	CScene3D::Draw();
}