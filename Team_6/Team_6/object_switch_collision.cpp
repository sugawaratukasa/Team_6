//=============================================================================
// �X�C�b�`����N���X [object_switch_collision.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// �}�N����`
// Author : Sugawara Tsukasa
//=============================================================================
#define POS				(D3DXVECTOR3(pos.x,pos.y,pos.z + 200.0f))	// �ʒu
#define POS2			(D3DXVECTOR3(pos.x + 200.0f,pos.y,pos.z))	// �ʒu
#define COLLISION_SIZE	(D3DXVECTOR3(150.0f,450.0f,50.0f))			// �T�C�Y
#define COLLISION_SIZE2	(D3DXVECTOR3(50.0f,450.0f,150.0f))			// �T�C�Y
#define ROT_180			(D3DXToRadian(179.0f))						// ����
#define ROT_270			(D3DXToRadian(269.0f))						// ����
//=============================================================================
// �C���N���[�h�t�@�C��
// Author : Sugawara Tsukasa
//=============================================================================
#include "manager.h"
#include "object_switch_collision.h"
#include "resource_manager.h"

//=============================================================================
// �R���X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CSwitch_Collision::CSwitch_Collision(PRIORITY Priority) : CObject(Priority)
{
	m_pSwitch = nullptr;
}

//=============================================================================
// �f�X�g���N�^
// Author : Sugawara Tsukasa
//=============================================================================
CSwitch_Collision::~CSwitch_Collision()
{
}
//=============================================================================
// ���������֐�
// Author : Sugawara Tsukasa
//=============================================================================
CSwitch_Collision * CSwitch_Collision::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CSwitch *pSwitch)
{
	// CSwitch_Collision�̃|�C���^
	CSwitch_Collision *pSwitch_Collision = nullptr;

	// nullcheck
	if (pSwitch_Collision == nullptr)
	{
		// �������m��
		pSwitch_Collision = new CSwitch_Collision;

		// !nullcheck
		if (pSwitch_Collision != nullptr)
		{
			// ����������
			pSwitch_Collision->Init(pos, rot);

			// CSwitch�̃|�C���^���
			pSwitch_Collision->m_pSwitch = pSwitch;
		}
	}
	// �|�C���^��Ԃ�
	return pSwitch_Collision;
}

//=============================================================================
// �����������֐�
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CSwitch_Collision::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ����������
	CObject::Init(pos, rot);

	// 180�ȏ�̏ꍇ
	if (rot.y >= ROT_180 && rot.y <= ROT_270)
	{
		// �ʒu�ݒ�
		SetPos(POS);

		// �T�C�Y
		SetSize(COLLISION_SIZE);
	}

	// 270�ȏ�̏ꍇ
	if (rot.y >= ROT_270)
	{
		// �ʒu�ݒ�
		SetPos(POS2);

		// �T�C�Y
		SetSize(COLLISION_SIZE2);
	}

	// ��ސݒ�
	SetType(TYPE_SWITCH);

	return S_OK;
}

//=============================================================================
// �I�������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CSwitch_Collision::Uninit(void)
{
	// �I������
	CObject::Uninit();
}
//=============================================================================
// �X�V�����֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CSwitch_Collision::Update(void)
{
	// �X�V����
	CObject::Update();
}
//=============================================================================
// �`�揈���֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CSwitch_Collision::Draw(void)
{
}
//=============================================================================
// �{�^�������������֐�
// Author : Sugawara Tsukasa
//=============================================================================
void CSwitch_Collision::Push(void)
{
	// �{�^������������
	m_pSwitch->Push();
}