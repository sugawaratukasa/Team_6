//=============================================================================
// �X�C�b�`�N���X [object_switch.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(150.0f,450.0f,50.0f))	// �T�C�Y
#define COLLISION_SIZE2	(D3DXVECTOR3(50.0f,450.0f,150.0f))	// �T�C�Y
#define ROT_180			(D3DXToRadian(179.0f))				// ����
#define ROT_270			(D3DXToRadian(269.0f))				// ����
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "object_switch.h"
#include "resource_manager.h"
#include "object_switch_collision.h"
#include "input.h"
#include "keyboard.h"
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CSwitch::CSwitch(PRIORITY Priority) : CObject(Priority)
{
	m_pPrison_Cell_Door = nullptr;
}

//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CSwitch::~CSwitch()
{
}
//=============================================================================
// ���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
CSwitch * CSwitch::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CPrison_Cell_Door *pPrison_Cell_Door)
{
	// CSwitch�̃|�C���^
	CSwitch *pSwitch = nullptr;

	// nullcheck
	if (pSwitch == nullptr)
	{
		// �������m��
		pSwitch = new CSwitch;

		// !nullcheck
		if (pSwitch != nullptr)
		{
			// ����������
			pSwitch->Init(pos, rot);

			// �Ɩ[�̃h�A�̃|�C���^���
			pSwitch->m_pPrison_Cell_Door = pPrison_Cell_Door;
		}
	}
	// �|�C���^��Ԃ�
	return pSwitch;
}

//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CSwitch::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���萶��
	CSwitch_Collision::Create(pos, rot, this);

	// ����������
	CObject::Init(pos, rot);

	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f�����擾
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_SWITCH);

		// ���f���̏���n��
		BindModel(model);
	}

	// ��ސݒ�
	SetType(TYPE_SWITCH);

	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CSwitch::Uninit(void)
{
	// �I������
	CObject::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CSwitch::Update(void)
{
	// �X�V����
	CObject::Update();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CSwitch::Draw(void)
{
	// �`�揈��
	CObject::Draw();
}
//=============================================================================
// �{�^���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CSwitch::Push(void)
{
	// �����J��
	m_pPrison_Cell_Door->SetLock(false);
}