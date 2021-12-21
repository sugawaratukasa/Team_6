//=============================================================================
// �� [enemy_attack_point_polygon.cpp]
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
#include "black_fill_polygon.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define COL (D3DCOLOR_RGBA(255, 255, 255, 255))	// �F
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CBlack_Fill_Polygon::CBlack_Fill_Polygon(PRIORITY Priority) : CScene3D(Priority)
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CBlack_Fill_Polygon::~CBlack_Fill_Polygon()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CBlack_Fill_Polygon * CBlack_Fill_Polygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CBlack_Fill_Polygon�̃|�C���^
	CBlack_Fill_Polygon *pBlack_Fill_Polygon = nullptr;

	// nullcheck
	if (pBlack_Fill_Polygon == nullptr)
	{
		// �������m��
		pBlack_Fill_Polygon = new CBlack_Fill_Polygon;

		// !nullcheck
		if (pBlack_Fill_Polygon != nullptr)
		{
			// ����������
			pBlack_Fill_Polygon->Init(pos, size);
		}
	}
	// �|�C���^��Ԃ�
	return pBlack_Fill_Polygon;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CBlack_Fill_Polygon::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CScene3D::Init(pos, size);

	// �e�N�X�`���̐ݒ�
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_BLACK_FILL));

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
void CBlack_Fill_Polygon::Uninit(void)
{
	// �I������
	CScene3D::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBlack_Fill_Polygon::Update(void)
{
	// �X�V����
	CScene3D::Update();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CBlack_Fill_Polygon::Draw(void)
{
	// �`�揈��
	CScene3D::Draw();
}