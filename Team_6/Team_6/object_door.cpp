//=============================================================================
// �h�A [object_door.cpp]
// Author : Nikaido Taichi
//=============================================================================

//=============================================================================
// �}�N����`
// Author : Nikaido Taichi
//=============================================================================
#define COLLISION_SIZE	(D3DXVECTOR3(200.0f,500.f,25.0f))	// �����蔻��T�C�Y
#define COLLISION_SIZE2	(D3DXVECTOR3(25.0f,500.0f,200.0f))	// �T�C�Y
#define ROT_90			(D3DXToRadian(89.0f))				// ����
#define ADD_POS			(10.0f)								// �ʒu���Z
#define CLOSE_COUNT		(600)								// �������J�E���g
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Nikaido Taichi
//=============================================================================
#include "manager.h"
#include "resource_manager.h"
#include "object_door.h"

//=============================================================================
// �R���X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CDoor::CDoor(PRIORITY Priority) : CObject(Priority)
{
	m_Type = DOOR_NONE;		// �h�A�̎��
	m_bLock = true;			// ���b�N���	m_InitPos = ZeroVector3;
	m_nCloseCnt = ZERO_INT;
}

//=============================================================================
// �f�X�g���N�^
// Author : Nikaido Taichi
//=============================================================================
CDoor::~CDoor()
{
}
//=============================================================================
// ���������֐�
// Author : Nikaido Taichi
//=============================================================================
CDoor * CDoor::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CDoor�̃|�C���^
	CDoor *pDoor = nullptr;

	// nukkcheck
	if (pDoor == nullptr)
	{
		// �������m��
		pDoor = new CDoor;

		// !nullchcek
		if (pDoor != nullptr)
		{
			// ����������
			pDoor->Init(pos, rot);
		}
	}
	// �|�C���^��Ԃ�
	return pDoor;
}

//=============================================================================
// �����������֐�
// Author : Nikaido Taichi
//=============================================================================
HRESULT CDoor::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ����������
	CObject::Init(pos, rot);


	// �����ʒu���
	m_InitPos = pos;

	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();


	// �T�C�Y�ݒ�
	SetSize(COLLISION_SIZE);

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
// Author : Nikaido Taichi
//=============================================================================
void CDoor::Uninit(void)
{
	// �I������
	CObject::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Nikaido Taichi
//=============================================================================
void CDoor::Update(void)
{
	// �X�V����
	CObject::Update();

	// �J����Ԃ̏ꍇ
	if (m_bLock == false)
	{
		// �C���N�������g
		m_nCloseCnt++;

		// CLOSE_COUNT��菬�����ꍇ
		if (m_nCloseCnt <= CLOSE_COUNT)
		{
			// �h�A���J������
			Open();
		}

		// CLOSE_COUNT���傫���Ȃ����ꍇ
		if (m_nCloseCnt >= CLOSE_COUNT)
		{
			// ������鏈��
			Close();
		}
	}
}
//=============================================================================
// �`�揈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CDoor::Draw(void)
{
	// �`�揈��
	CObject::Draw();

}
//=============================================================================
// �h�A���J�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CDoor::Open(void)
{
	// �����擾
	D3DXVECTOR3 rot = GetRot();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// 90�ȏ�̏ꍇ
	if (rot.y >= ROT_90)
	{
		// �����l+�T�C�Y�𑫂����ʒu�܂ňړ�
		if (pos.z <= m_InitPos.z + size.z)
		{
			// �ʒu�擾
			GetPos().z += ADD_POS;
		}
	}
	else
	{
		// �����l+�T�C�Y�𑫂����ʒu�܂ňړ�
		if (pos.x >= m_InitPos.x - size.x)
		{
			// �ʒu�擾
			GetPos().x -= ADD_POS;
		}
	}
}
//=============================================================================
// �h�A����鏈���֐�
// Author : Nikaido Taichi
//=============================================================================
void CDoor::Close(void)
{
	// �����擾
	D3DXVECTOR3 rot = GetRot();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// 90�ȏ�̏ꍇ
	if (rot.y >= ROT_90)
	{
		// �����ʒu�܂ňړ�
		if (pos.z >= m_InitPos.z)
		{
			// �ʒu�擾
			GetPos().z -= ADD_POS;
		}
		else
		{
			// ���b�N��Ԃ�
			m_bLock = true;

			// 0��
			m_nCloseCnt = ZERO_INT;
		}
	}
	else
	{
		// �����l+�T�C�Y�𑫂����ʒu�܂ňړ�
		if (pos.x <= m_InitPos.x)
		{
			// �ʒu�擾
			GetPos().x += ADD_POS;
		}
		else
		{
			// 0��
			m_nCloseCnt = ZERO_INT;

			// ���b�N��Ԃ�
			m_bLock = true;
		}
	}
}