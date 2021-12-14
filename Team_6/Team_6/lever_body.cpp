//=============================================================================
// ���o�[�{�f�B [lever_body.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "lever_body.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CLever_Body::CLever_Body(PRIORITY Priority) : CModel(Priority)
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CLever_Body::~CLever_Body()
{
}
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
CLever_Body * CLever_Body::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CLever_Body�̃|�C���^
	CLever_Body *pLever_Body = nullptr;

	// nullcheck
	if (pLever_Body == nullptr)
	{
		// �������m��
		pLever_Body = new CLever_Body;

		// !nullcheck
		if (pLever_Body != nullptr)
		{
			// ����������
			pLever_Body->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pLever_Body;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CLever_Body::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ����������
	CModel::Init(pos, rot);

	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f�����擾
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_LEVER_BODY);

		// ���f���̏���n��
		BindModel(model);
	}
	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CLever_Body::Uninit(void)
{
	// �I������
	CModel::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CLever_Body::Update(void)
{
	// �X�V����
	CModel::Update();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CLever_Body::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}