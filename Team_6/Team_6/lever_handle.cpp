//=============================================================================
// ���o�[�n���h�� [lever_handle.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "lever_handle.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CLever_Handle::CLever_Handle(PRIORITY Priority) : CModel(Priority)
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CLever_Handle::~CLever_Handle()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CLever_Handle * CLever_Handle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CLever_Handle�̃|�C���^
	CLever_Handle *pLever_Handle = nullptr;

	// nullcheck
	if (pLever_Handle == nullptr)
	{
		// �������m��
		pLever_Handle = new CLever_Handle;

		// !nullcheck
		if (pLever_Handle != nullptr)
		{
			// ����������
			pLever_Handle->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pLever_Handle;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CLever_Handle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ����������
	CModel::Init(pos, rot);

	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f�����擾
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_LEVER_HANDLE);

		// ���f���̏���n��
		BindModel(model);
	}
	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CLever_Handle::Uninit(void)
{
	// �I������
	CModel::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CLever_Handle::Update(void)
{
	// �X�V����
	CModel::Update();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CLever_Handle::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}