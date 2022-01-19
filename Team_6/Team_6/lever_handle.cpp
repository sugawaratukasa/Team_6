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
#define DOWN_Y		(40.0f)	// ���o�[�̉�����ʒu7
#define MOVE_Y		(2.0f)	// �ړ�
#define UP_COUNT	(150)	// �J�E���g
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CLever_Handle::CLever_Handle(PRIORITY Priority) : CModel(Priority)
{
	m_InitPos = ZeroVector3;
	m_bDown = false;
	m_bOpen = false;
	m_nDownCnt = ZERO_INT;
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
	// �����ʒu���
	m_InitPos = pos;

	// ����������
	CModel::Init(pos, rot);

	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != nullptr)
	{
		// ���f�����擾
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_LEVER_SWITCH_HANDLE);

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

	// ���o�[���������Ă��邩
	if (m_bDown == true)
	{
		// �����鏈��
		Down();
		
		// �����J���Ă��Ȃ��ꍇ
		if (m_bOpen == false)
		{
			// �C���N�������g
			m_nDownCnt++;

			// ���o�[�̏オ��J�E���g�����傫���Ȃ����ꍇ
			if (m_nDownCnt > UP_COUNT)
			{
				// 0��
				m_nDownCnt = ZERO_INT;

				// �オ���Ă����Ԃ�
				m_bDown = false;
			}
		}
	}
	// ���o�[���グ���Ă���ꍇ
	if (m_bDown == false)
	{
		// �オ�鏈��
		Up();
	}
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
//=============================================================================
// �����鏈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CLever_Handle::Down(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �ʒu�����̈ʒu�̏ꍇ
	if (pos.y >= m_InitPos.y - DOWN_Y)
	{
		// �ړ�
		pos.y -= MOVE_Y;

		// �ʒu�ݒ�
		SetPos(pos);
	}
}
//=============================================================================
// �グ�鏈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CLever_Handle::Up(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �ʒu�����̈ʒu�̏ꍇ
	if (pos.y <= m_InitPos.y)
	{
		// �ړ�
		pos.y += MOVE_Y;

		// �ʒu�ݒ�
		SetPos(pos);
	}
}