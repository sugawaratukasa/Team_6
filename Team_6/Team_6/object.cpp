//=============================================================================
// �I�u�W�F�N�g [object.cpp]
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
#include "game.h"
#include "player.h"
#include "object.h"
#include "model_collision_box.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CObject::CObject(PRIORITY Priority) : CModel(Priority)
{
	m_Type = TYPE_NONE;
	m_pObb = nullptr;
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CObject::~CObject()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CObject * CObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CObject�̃|�C���^
	CObject *pObject = nullptr;

	// nullcheck
	if (pObject == nullptr)
	{
		// �������m��
		pObject = new CObject;

		// !nullcheck
		if (pObject != nullptr)
		{
			// ����������
			pObject->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pObject;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CObject::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ����������
	CModel::Init(pos, rot);

	CModelCollisionBox::Create(pos, rot, this);
	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CObject::Uninit(void)
{
	if (m_pObb != nullptr)
	{
		//OBB�̏I��
		m_pObb->Uninit();
	}
	
	// �I������
	CModel::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CObject::Update(void)
{
	// �X�V����
	CModel::Update();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CObject::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}