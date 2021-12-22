//=============================================================================
// �_�N�g�̔��� [duct_collision.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "duct_collision.h"
#include "model_collision_box.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE (D3DXVECTOR3(100.0f, 550.0f, 100.0f))	// �T�C�Y
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CDuct_Collision::CDuct_Collision(PRIORITY Priority) : CModel(Priority)
{
}
//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CDuct_Collision::~CDuct_Collision()
{
}
//=============================================================================
// ���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
CDuct_Collision * CDuct_Collision::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type)
{
	// CDuct_Collision�̃|�C���^
	CDuct_Collision *pDuctCollision = nullptr;

	// nullcheck
	if (pDuctCollision == nullptr)
	{
		// �������m��
		pDuctCollision = new CDuct_Collision;

		// !nullcheck
		if (pDuctCollision != nullptr)
		{
			// ��ޑ��
			pDuctCollision->m_Type = type;

			// ����������
			pDuctCollision->Init(pos, rot);
		}
	}
	return nullptr;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CDuct_Collision::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ������
	CModel::Init(pos, rot);

	// �T�C�Y
	SetSize(COLLISION_SIZE);
	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CDuct_Collision::Uninit(void)
{
	// �I������
	CModel::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CDuct_Collision::Update(void)
{
	// �X�V
	CModel::Update();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CDuct_Collision::Draw(void)
{
}
