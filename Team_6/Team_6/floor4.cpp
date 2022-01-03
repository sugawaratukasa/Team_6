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
#include "floor4.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define COL (D3DCOLOR_RGBA(255, 255, 255, 255))	// �F
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CFloor4::CFloor4(PRIORITY Priority) : CScene3D(Priority)
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CFloor4::~CFloor4()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CFloor4 * CFloor4::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CFloor�̃|�C���^
	CFloor4 *pFloor = nullptr;

	// nullcheck
	if (pFloor == nullptr)
	{
		// �������m��
		pFloor = new CFloor4;

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
HRESULT CFloor4::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CScene3D::Init(pos, size);

	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_FLOOR_4));

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
void CFloor4::Uninit(void)
{
	// �I������
	CScene3D::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CFloor4::Update(void)
{
	// �X�V����
	CScene3D::Update();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CFloor4::Draw(void)
{
	// �`�揈��
	CScene3D::Draw();
}