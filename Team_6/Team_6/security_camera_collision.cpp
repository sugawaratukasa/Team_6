//=============================================================================
// �Ď��J�����̔��� [security_camera_collision.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "security_camera_collision.h"
#include "manager.h"
#include "renderer.h"
#include "model_collision_box.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define COL_SIZE	(D3DXVECTOR3(600.0f,500.0f,100.0f))
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CSecurity_Camera_Collision::CSecurity_Camera_Collision(PRIORITY Priority) : CModel(Priority)
{
}
//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CSecurity_Camera_Collision::~CSecurity_Camera_Collision()
{
}
//=============================================================================
// ���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
CSecurity_Camera_Collision * CSecurity_Camera_Collision::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CSecurity_Camera_Collision�̃|�C���^
	CSecurity_Camera_Collision * pSecurity_Camera_Collision = nullptr;

	// nullptr�̏ꍇ
	if (pSecurity_Camera_Collision == nullptr)
	{
		// �������m��
		pSecurity_Camera_Collision = new CSecurity_Camera_Collision;

		// nullptr�łȂ��ꍇ
		if (pSecurity_Camera_Collision != nullptr)
		{
			// ����������
			pSecurity_Camera_Collision->Init(pos, rot);
		}
	}
	return nullptr;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CSecurity_Camera_Collision::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ����������
	CModel::Init(pos, rot);

	// �T�C�Y�ݒ�
	SetSize(COL_SIZE);

	// ����m�F�p
	//CModelCollisionBox::Create(pos, rot, this);
	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CSecurity_Camera_Collision::Uninit(void)
{
	// �I������
	CModel::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CSecurity_Camera_Collision::Update(void)
{

}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CSecurity_Camera_Collision::Draw(void)
{

}
//=============================================================================
// �J�����g�p�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CSecurity_Camera_Collision::CameraUse(int nPlayer)
{
	// �����_���[�擾
	CRenderer *pRenderer = CManager::GetRenderer();

	// nullptr�łȂ��ꍇ
	if (pRenderer != nullptr)
	{
		// �J�����g�p����
		pRenderer->SwitchCam(nPlayer);
	}
}