//=============================================================================
// �L�����N�^�[�����蔻��`�F�b�N�p�� [character_collision_box.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "character.h"
#include "collision.h"
#include "character_collision_box.h"

//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define PARENT_NUM	(0)		// �e�̃i���o�[

// �L�����N�^�[�̈ʒu
#define POS			(D3DXVECTOR3(pAnime->GetMtxWorld()._41, pAnime->GetMtxWorld()._42, pAnime->GetMtxWorld()._43))
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CCharacterCollisionBox::CCharacterCollisionBox(PRIORITY Priority)
{
	m_pCharacter = nullptr;
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CCharacterCollisionBox::~CCharacterCollisionBox()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CCharacterCollisionBox * CCharacterCollisionBox::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CCharacter *pCharacter)
{
	// CCharacter_Box�̃|�C���^
	CCharacterCollisionBox *pBox = nullptr;

	// nullcheck
	if (pBox == nullptr)
	{
		// �������m��
		pBox = new CCharacterCollisionBox;

		// !nullcheck
		if (pBox != nullptr)
		{
			// �|�C���^���
			pBox->m_pCharacter = pCharacter;

			// ����������
			pBox->Init(pos, ZeroVector3);
		}
	}
	// �|�C���^��Ԃ�
	return pBox;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CCharacterCollisionBox::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f�����擾
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_BOX);

		// ���f���̏���n��
		BindModel(model);
	}

	// �T�C�Y�擾
	D3DXVECTOR3 size = m_pCharacter->GetSize();

	// �g�嗦�̐ݒ�
	SetScale(size);

	// ����������
	CModel::Init(pos, rot);

	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CCharacterCollisionBox::Uninit(void)
{
	// �I������
	CModel::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CCharacterCollisionBox::Update(void)
{
	// �X�V����
	CModel::Update();

	// ���S��Ԃ̏ꍇ
	if (m_pCharacter->GetState() == CCharacter::STATE_DEAD)
	{
		// �I��
		Uninit();

		return;
	}

	// �|�C���^�擾
	CModelAnime *pAnime = m_pCharacter->GetModelAnime(PARENT_NUM);

	// �ʒu�ݒ�
	SetPos(POS);
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CCharacterCollisionBox::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}