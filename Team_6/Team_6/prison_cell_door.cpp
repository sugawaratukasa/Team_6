//=============================================================================
// �S���̔� [object_prison_door_right.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "prison_cell_door.h"
#include "object.h"
#include "manager.h"
#include "resource_manager.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define COLLISION_SIZE		(D3DXVECTOR3(130.0f,330.0f,25.0f))	// �T�C�Y
#define COLLISION_SIZE2		(D3DXVECTOR3(25.0f,330.0f,130.0f))	// �T�C�Y
#define ROT_90				(D3DXToRadian(89.0f))				// ����
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CPrison_Cell_Door::CPrison_Cell_Door(PRIORITY Priority)
{
	m_pPlayer = nullptr;
}
//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CPrison_Cell_Door::~CPrison_Cell_Door()
{
}
//=============================================================================
// ���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
CPrison_Cell_Door * CPrison_Cell_Door::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CPlayer *pPlayer)
{
	// CPrison_Cell_Door�̃|�C���^
	CPrison_Cell_Door *pPrison_Door = nullptr;

	// nullcheck
	if (pPrison_Door == nullptr)
	{
		// �������m��
		pPrison_Door = new CPrison_Cell_Door;

		// !nullcheck
		if (pPrison_Door != nullptr)
		{
			// CPlayer�̃|�C���^���
			pPrison_Door->m_pPlayer = pPlayer;

			// ����������
			pPrison_Door->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pPrison_Door;
}
//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CPrison_Cell_Door::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �h�A�̏����������֐��Ăяo��
	CDoor::Init(pos, rot);

	// �T�C�Y
	SetSize(COLLISION_SIZE);

	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f�����擾
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_DOOR);

		// ���f���̏���n��
		BindModel(model);
	}

	// 90�ȏ�̏ꍇ
	if (rot.y >= ROT_90)
	{
		// �T�C�Y
		SetSize(COLLISION_SIZE2);
	}
	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPrison_Cell_Door::Uninit(void)
{
	// �h�A�̏I�������֐��Ăяo��
	CDoor::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPrison_Cell_Door::Update(void)
{
	// �h�A�̍X�V�����֐��Ăяo��
	CDoor::Update();

	// !nullcheck
	if (m_pPlayer != nullptr)
	{
		// �߂܂��Ă��邩�擾
		bool bIncapacitated = m_pPlayer->GetbIncapacitated();

		// true�̏ꍇ
		if (bIncapacitated == true)
		{
			// �S���J�E���g�̎擾
			int nIncapacitated_Cnt = m_pPlayer->GetIncapacitatedTimeCount();

			// �S���J�E���g��INCAPACITATED_TIME�̏ꍇ
			if (nIncapacitated_Cnt >= INCAPACITATED_TIME)
			{
				// �J��
				SetLock(false);
			}
		}
	}
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPrison_Cell_Door::Draw(void)
{
	// �h�A�̕`�揈���֐��Ăяo��
	CDoor::Draw();
}
//=============================================================================
// �{�^���������������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPrison_Cell_Door::Push(void)
{
	// !nullcheck
	if (m_pPlayer != nullptr)
	{
		// true�̏ꍇ
		if (m_pPlayer->GetbIncapacitated() == true)
		{
			// false��
			m_pPlayer->SetbIncapacitated(false);

			// �J�E���g0��
			m_pPlayer->GetIncapacitatedTimeCount() = ZERO_INT;
		}
	}
}
