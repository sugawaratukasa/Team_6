//=============================================================================
// �� [floor2.cpp]
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
#include "floor2.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define COL (D3DCOLOR_RGBA(255, 255, 255, 255))	// �F
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CFloor2::CFloor2(PRIORITY Priority) : CScene3D(Priority)
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CFloor2::~CFloor2()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CFloor2 * CFloor2::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CFloor�̃|�C���^
	CFloor2 *pFloor = nullptr;

	// nullcheck
	if (pFloor == nullptr)
	{
		// �������m��
		pFloor = new CFloor2;

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
HRESULT CFloor2::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CScene3D::Init(pos, size);

	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_FLOOR_2));

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
void CFloor2::Uninit(void)
{
	// �I������
	CScene3D::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CFloor2::Update(void)
{
	// �X�V����
	CScene3D::Update();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CFloor2::Draw(void)
{
	// �`�揈��
	CScene3D::Draw();
}