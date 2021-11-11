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
	m_bLock = true;			// ���b�N���
	InitPos = ZeroVector3;
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
	InitPos = pos;

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

	// �h�A���J������
	//Open();

	// �h�A�����
	Close();
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
		if (pos.z <= InitPos.z + size.z)
		{
			// �ʒu�擾
			GetPos().z += ADD_POS;
		}
	}
	else
	{
		// �����l+�T�C�Y�𑫂����ʒu�܂ňړ�
		if (pos.x >= InitPos.x - size.x)
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
		if (pos.z >= InitPos.z)
		{
			// �ʒu�擾
			GetPos().z -= ADD_POS;
		}
	}
	else
	{
		// �����l+�T�C�Y�𑫂����ʒu�܂ňړ�
		if (pos.x <= InitPos.x)
		{
			// �ʒu�擾
			GetPos().x += ADD_POS;
		}
	}
}