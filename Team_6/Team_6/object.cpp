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
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define SIZE	(D3DXVECTOR3 (1500.0f,2000.0f,1500.0f))	// �T�C�Y
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CObject::CObject(PRIORITY Priority) : CModel(Priority)
{
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
	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f�����擾
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_ROCK);

		// ���f���̏���n��
		BindModel(model);
	}

	// �T�C�Y�ݒ�
	SetSize(SIZE);

	// ������
	//CModel_Box::Create(pos, rot, this);

	// ����������
	CModel::Init(pos, ZeroVector3);

	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CObject::Uninit(void)
{
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