//=======================================================================================
//
// �A�C�e���������� [item_spawn.cpp]
// Author : Nikaido Taichi
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h�t�@�C��
//=======================================================================================
#include "item_spawn.h"
#include "item_object_map.h"
#include "item_object_baton.h"
#include "item_object_control_room_Key.h"
#include "item_object_electrical_room_key.h"
#include "item_object_jailer_room_key.h"
#include "item_object_pc_room_key.h"
#include "item_object_storage_key.h"

//=======================================================================================
// �}�N����`
//=======================================================================================
#define JAILER_KEY_POSITION1 (D3DXVECTOR3(3813.0f,0.0f,-8800.0f))
#define JAILER_KEY_POSITION2 (D3DXVECTOR3(3797.0f,0.0f,-7726.0f))
#define JAILER_KEY_POSITION3 (D3DXVECTOR3(-846.0f,0.0f,-8775.0f))
#define JAILER_KEY_POSITION4 (D3DXVECTOR3(-1908.0f,0.0f,-7777.0f))
#define MAP_POSITION1 (D3DXVECTOR3(2755.0f,0.0f,-8263.0f))
#define MAP_POSITION2 (D3DXVECTOR3(-855,0.0f,-7679.0f))
#define BATON_POSITION1 (D3DXVECTOR3(3835.0f,0.0f,-953.0f))
#define BATON_POSITION2 (D3DXVECTOR3(-1941.0f,0.0f,189.0f))
#define NEW_CAMERA_POS1 (D3DXVECTOR3(3282.0f,0.0f,-2019.0f))
#define NEW_CAMERA_POS2 (D3DXVECTOR3(605.0f,0.0f,-4000.0f))
#define NEM_CONTROL_POS1 (D3DXVECTOR3(3513.0f,0.0f,-931.0f))
#define NEW_CONTROL_POS2 (D3DXVECTOR3(-1606.0f,0.0f,200.3f))
#define NEW_ELECTRICAL_POS1 (D3DXVECTOR3(1685.0f,0.0f,-3169.9f))
#define NEW_ELECTRICAL_POS2 (D3DXVECTOR3(-1623.0f,0.0f,-2229.9f))
#define NEW_STORAGE_POS1 (D3DXVECTOR3(3275.0f,0.0f,206.0f))
#define NEW_STORAGE_POS2 (D3DXVECTOR3(686.4f,0.0f,-2279.0f))

//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CItemSpawn::CItemSpawn()
{
	m_nJailerNumber = 0;
	m_nCameraNumber = 0;
	m_nControlNumber = 0;
	m_nElectricalNumber = 0;
	m_nStorageNumber = 0;
}

//=======================================================================================
// �f�X�g���N�^
//=======================================================================================
CItemSpawn::~CItemSpawn()
{
}

//=======================================================================================
// ���������֐�
//=======================================================================================
CItemSpawn * CItemSpawn::Create(void)
{
	// CItemSpawn�̃|�C���^
	CItemSpawn *pItemSpawn = nullptr;

	// nullcheck
	if (pItemSpawn == nullptr)
	{
		// �������m��
		pItemSpawn = new CItemSpawn;
	}
	// �|�C���^��Ԃ�
	return pItemSpawn;
}

//=======================================================================================
// �����������֐�
//=======================================================================================
HRESULT CItemSpawn::Init(void)
{
	CMapObject::Create(MAP_POSITION1, ZeroVector3);
	CMapObject::Create(MAP_POSITION2, ZeroVector3);

	CBatonObject::Create(BATON_POSITION1, ZeroVector3);
	CBatonObject::Create(BATON_POSITION2, ZeroVector3);
	JailerKeyCreate();
	CameraKeyCreate();
	ControlKeyCreate();
	ElectricalKeyCreate();
	StorageKeyCreate();
	return S_OK;
}

//=======================================================================================
// �X�V�����֐�
//=======================================================================================
void CItemSpawn::Update(void)
{
}

//=======================================================================================
// �Ŏ�̌����������֐�
//=======================================================================================
void CItemSpawn::JailerKeyCreate(void)
{
	m_nJailerNumber = rand() % 4;
	switch (m_nJailerNumber)
	{
	case 0:
		CJailerKeyObject::Create(JAILER_KEY_POSITION1, ZeroVector3);
		break;
	case 1:
		CJailerKeyObject::Create(JAILER_KEY_POSITION2, ZeroVector3);
		break;
	case 2:
		CJailerKeyObject::Create(JAILER_KEY_POSITION3, ZeroVector3);
		break;
	case 3:
		CJailerKeyObject::Create(JAILER_KEY_POSITION4, ZeroVector3);
		break;
	default:
		break;
	}
}

//=======================================================================================
// �J�������̌����������֐�
//=======================================================================================
void CItemSpawn::CameraKeyCreate(void)
{
	m_nCameraNumber = rand() % 2;
	switch (m_nCameraNumber)
	{
	case 0:
		CPCRoomKeyObject::Create(NEW_CAMERA_POS1, ZeroVector3);
		break;
	case 1:
		CPCRoomKeyObject::Create(NEW_CAMERA_POS2, ZeroVector3);
		break;
	default:
		break;
	}
}

//=======================================================================================
// ���䎺�̌����������֐�
//=======================================================================================
void CItemSpawn::ControlKeyCreate(void)
{
	m_nControlNumber = rand() % 2;
	switch (m_nControlNumber)
	{
	case 0:
		CControlRoomKeyObject::Create(NEM_CONTROL_POS1, ZeroVector3);
		break;
	case 1:
		CControlRoomKeyObject::Create(NEW_CONTROL_POS2, ZeroVector3);
		break;
	default:
		break;
	}
}

//=======================================================================================
// �d�����̌����������֐�
//=======================================================================================
void CItemSpawn::ElectricalKeyCreate(void)
{
	m_nElectricalNumber = rand() % 2;
	switch (m_nElectricalNumber)
	{
	case 0:
		CElectricalRoomKeyObject::Create(NEW_ELECTRICAL_POS1, ZeroVector3);
		break;
	case 1:
		CElectricalRoomKeyObject::Create(NEW_ELECTRICAL_POS2, ZeroVector3);
		break;
	default:
		break;
	}
}

//=======================================================================================
// PC��
//=======================================================================================
void CItemSpawn::StorageKeyCreate(void)
{
	m_nStorageNumber = rand() % 2;
	switch (m_nStorageNumber)
	{
	case 0:
		CStorageKeyObject::Create(NEW_STORAGE_POS1, ZeroVector3);
		break;
	case 1:
		CStorageKeyObject::Create(NEW_STORAGE_POS2, ZeroVector3);
		break;
	default:
		break;
	}
}
