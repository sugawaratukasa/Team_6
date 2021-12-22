//=============================================================================
// �S���̔� [object_prison_door_right.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "object_prison_door_left.h"
#include "object.h"
#include "manager.h"
#include "resource_manager.h"
#include "prison_door_collision.h"
#include "sound.h"
//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================

#define COLLISION_SIZE	(D3DXVECTOR3(180.0f,450.0f,50.0f))	// �T�C�Y
#define COLLISION_SIZE2	(D3DXVECTOR3(50.0f,450.0f,180.0f))	// �T�C�Y
#define ROT_90			(D3DXToRadian(89.0f))				// ����
#define ROT_90			(D3DXToRadian(89.0f))				// ����
#define ADD_POS			(10.0f)								// �ʒu���Z
#define CLOSE_COUNT		(600)								// �������J�E���g
//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CPrison_Door_Left::CPrison_Door_Left(PRIORITY Priority)
{
}
//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CPrison_Door_Left::~CPrison_Door_Left()
{
}
//=============================================================================
// ���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
CPrison_Door_Left * CPrison_Door_Left::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CPrison_Door_Left�̃|�C���^
	CPrison_Door_Left *pPrison_Door = nullptr;

	// nullcheck
	if (pPrison_Door == nullptr)
	{
		// �������m��
		pPrison_Door = new CPrison_Door_Left;

		// !nullcheck
		if (pPrison_Door != nullptr)
		{
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
HRESULT CPrison_Door_Left::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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
		CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_PRISON_DOOR_LEFT);

		// ���f���̏���n��
		BindModel(model);
	}

	// 90�ȏ�̏ꍇ
	if (rot.y >= ROT_90)
	{
		// �T�C�Y
		SetSize(COLLISION_SIZE2);
	}

	//OBB�̍쐬
	SetObb(CObb::Create(pos, rot, GetMesh()));

	// ����p�I�u�W�F�N�g����
	CPrison_Door_Collision::Create(pos, rot, this);
	return S_OK;
}
//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPrison_Door_Left::Uninit(void)
{
	// �h�A�̏I�������֐��Ăяo��
	CDoor::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPrison_Door_Left::Update(void)
{
	// �h�A�̍X�V�����֐��Ăяo��
	CDoor::Update();

	// �J�����
	Open();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CPrison_Door_Left::Draw(void)
{
	// �h�A�̕`�揈���֐��Ăяo��
	CDoor::Draw();
}
//=============================================================================
// �h�A���J�������֐�
// Author : Nikaido Taichi
//=============================================================================
void CPrison_Door_Left::Open(void)
{
	// �����擾
	D3DXVECTOR3 rot = GetRot();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �����ʒu�擾
	D3DXVECTOR3 Initpos = GetInitPos();

	if (rot.y >= ROT_90)
	{
		// �����l+�T�C�Y�𑫂����ʒu�܂ňړ�
		if (pos.z <= Initpos.z + size.z)
		{
			// �ʒu�擾
			GetPos().z += ADD_POS;
		}
	}
	else
	{
		// �����l+�T�C�Y�𑫂����ʒu�܂ňړ�
		if (pos.x >= Initpos.x - size.x)
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
void CPrison_Door_Left::Close(void)
{
	// �����ʒu�擾
	D3DXVECTOR3 Initpos = GetInitPos();

	// �����擾
	D3DXVECTOR3 rot = GetRot();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	CSound * pSound = GET_SOUND_PTR;
	// 90�ȏ�̏ꍇ
	if (rot.y >= ROT_90)
	{
		// �����ʒu�܂ňړ�
		if (pos.z >= Initpos.z)
		{
			// �ʒu�擾
			GetPos().z -= ADD_POS;
		}
		else
		{
			// ���b�N��Ԃ�
			SetLock(true);
			pSound->CSound::Play(CSound::SOUND_SE_OPEN_PRISON);
			// 0��
			GetCloseCnt() = ZERO_INT;
		}
	}
	else
	{
		// �����l+�T�C�Y�𑫂����ʒu�܂ňړ�
		if (pos.x <= Initpos.x)
		{
			// �ʒu�擾
			GetPos().x += ADD_POS;
		}
		else
		{
			pSound->CSound::Play(CSound::SOUND_SE_OPEN_PRISON);
			// 0��
			GetCloseCnt() = ZERO_INT;

			// ���b�N��Ԃ�
			SetLock(true);
		}
	}
}
