#include "item_spawn.h"
#include "item_object_map.h"
#include "item_object_baton.h"
#include "item_object_control_room_Key.h"
#include "item_object_electrical_room_key.h"
#include "item_object_jailer_room_key.h"
#include "item_object_pc_room_key.h"
#include "item_object_storage_key.h"

#define PC_ELECTRICAL_POSITION1 (D3DXVECTOR3(1400.0f,0.0f,-3190.0f))
#define PC_ELECTRICAL_POSITION2 (D3DXVECTOR3(3488.0f,0.0f,-894.0f))
#define PC_ELECTRICAL_POSITION3 (D3DXVECTOR3(-1869.0f,0.0f,-2233.0f))
#define PC_ELECTRICAL_POSITION4 (D3DXVECTOR3(-1288.0f,0.0f,378.0f))

#define CONTROL_STORAGE_POSITION1 (D3DXVECTOR3(3732.0f,0.0f,-4096.0f))
#define CONTROL_STORAGE_POSITION2 (D3DXVECTOR3(3512.0f,0.0f,246.0f))
#define CONTROL_STORAGE_POSITION3 (D3DXVECTOR3(-1497.0f,0.0f,-3233.0f))
#define CONTROL_STORAGE_POSITION4 (D3DXVECTOR3(759.0f,0.0f,-2330.0f))

#define JAILER_KEY_POSITION1 (D3DXVECTOR3(3813.0f,0.0f,-8800.0f))
#define JAILER_KEY_POSITION2 (D3DXVECTOR3(3797.0f,0.0f,-7726.0f))
#define JAILER_KEY_POSITION3 (D3DXVECTOR3(-846.0f,0.0f,-8775.0f))
#define JAILER_KEY_POSITION4 (D3DXVECTOR3(-1908.0f,0.0f,-7777.0f))

#define MAP_POSITION1 (D3DXVECTOR3(2755.0f,0.0f,-8263.0f))
#define MAP_POSITION2 (D3DXVECTOR3(-855,0.0f,-7679.0f))

#define BATON_POSITION1 (D3DXVECTOR3(3835.0f,0.0f,-953.0f))
#define BATON_POSITION2 (D3DXVECTOR3(-1941.0f,0.0f,189.0f))


#define PLAYER1_POS (D3DXVECTOR3(3801.0f,0.0f,-9234.0f))
#define PLAYER2_POS (D3DXVECTOR3(-821.0f,0.0f,-8215.0f))

#define NEW_CAMERA_POS1 (D3DXVECTOR3(3282.0f,0.0f,-2019.0f))
#define NEW_CAMERA_POS2 (D3DXVECTOR3(605.0f,0.0f,-4000.0f))
#define NEM_CONTROL_POS1 (D3DXVECTOR3(3513.0f,0.0f,-931.0f))
#define NEW_CONTROL_POS2 (D3DXVECTOR3(-1606.0f,0.0f,200.3f))
#define NEW_ELECTRICAL_POS1 (D3DXVECTOR3(1685.0f,0.0f,-3169.9f))
#define NEW_ELECTRICAL_POS2 (D3DXVECTOR3(-1623.0f,0.0f,-2229.9f))
#define NEW_PC_POS1 (D3DXVECTOR3(3275.0f,0.0f,206.0f))
#define NEW_PC_POS2 (D3DXVECTOR3(686.4f,0.0f,-2279.0f))

CItemSpawn::CItemSpawn()
{
	//m_nPC_Electrical_key_number = 0;
	//memset(m_bPCKeyPosition,false,sizeof(m_bPCKeyPosition));
	//m_bPCKeyCreate = false;
	//memset(m_bElectricalKeyPosition,false,sizeof(m_bElectricalKeyPosition));
	//m_bElectricalKeyCreate = false;

	//m_nStorage_Control_key_number = 0;
	//memset(m_bStoragePosition,false,sizeof(m_bStoragePosition));
	//m_bStorageKeyCreate = false;
	//memset(m_bControlKeyPosition,false,sizeof(m_bControlKeyPosition));
	//m_bControlKeyCreate = false;

	m_nJailerNumber = 0;
	m_nCameraNumber = 0;
	m_nControlNumber = 0;
	m_nElectricalNumber = 0;
	m_nPCNumber = 0;
}

CItemSpawn::~CItemSpawn()
{
}

CItemSpawn * CItemSpawn::Create(void)
{
	// CItemSpawnのポインタ
	CItemSpawn *pItemSpawn = nullptr;

	// nullcheck
	if (pItemSpawn == nullptr)
	{
		// メモリ確保
		pItemSpawn = new CItemSpawn;
	}
	// ポインタを返す
	return pItemSpawn;
}

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
	PCKeyCreate();
	return S_OK;
}

void CItemSpawn::Update(void)
{
	//PC_Electrical_key_Create();
	//Storage_Control_KeyCreate();
}

//void CItemSpawn::PC_Electrical_key_Create(void)
//{
//	m_nPC_Electrical_key_number = rand() % 3;
//	switch (m_nPC_Electrical_key_number)
//	{
//	case 0:
//		if (m_bElectricalKeyPosition[0] == false && m_bPCKeyCreate == false)
//		{
//			CPCRoomKeyObject::Create(PC_ELECTRICAL_POSITION1, ZeroVector3);
//			m_bPCKeyPosition[0] = true;
//			m_bPCKeyCreate = true;
//		}
//		if (m_bPCKeyPosition[0] == false && m_bElectricalKeyCreate == false)
//		{
//			CElectricalRoomKeyObject::Create(PC_ELECTRICAL_POSITION1, ZeroVector3);
//			m_bElectricalKeyPosition[0] = true;
//			m_bElectricalKeyCreate = true;
//		}
//		break;
//	case 1:
//		if (m_bElectricalKeyPosition[1] == false && m_bPCKeyCreate == false)
//		{
//			CPCRoomKeyObject::Create(PC_ELECTRICAL_POSITION2, ZeroVector3);
//			m_bPCKeyPosition[1] = true;
//			m_bPCKeyCreate = true;
//		}
//		if (m_bPCKeyPosition[1] == false && m_bElectricalKeyCreate == false)
//		{
//			CElectricalRoomKeyObject::Create(PC_ELECTRICAL_POSITION2, ZeroVector3);
//			m_bElectricalKeyPosition[1] = true;
//			m_bElectricalKeyCreate = true;
//		}
//		break;
//	case 2:
//		if (m_bElectricalKeyPosition[2] == false && m_bPCKeyCreate == false)
//		{
//			CPCRoomKeyObject::Create(PC_ELECTRICAL_POSITION3, ZeroVector3);
//			m_bPCKeyPosition[2] = true;
//			m_bPCKeyCreate = true;
//		}
//		if (m_bPCKeyPosition[2] == false && m_bElectricalKeyCreate == false)
//		{
//			CElectricalRoomKeyObject::Create(PC_ELECTRICAL_POSITION3, ZeroVector3);
//			m_bElectricalKeyPosition[2] = true;
//			m_bElectricalKeyCreate = true;
//		}
//		break;
//	case 3:
//		if (m_bElectricalKeyPosition[3] == false && m_bPCKeyCreate == false)
//		{
//			CPCRoomKeyObject::Create(PC_ELECTRICAL_POSITION4, ZeroVector3);
//			m_bPCKeyPosition[3] = true;
//			m_bPCKeyCreate = true;
//		}
//		if (m_bPCKeyPosition[3] == false && m_bElectricalKeyCreate == false)
//		{
//			CElectricalRoomKeyObject::Create(PC_ELECTRICAL_POSITION4, ZeroVector3);
//			m_bElectricalKeyPosition[3] = true;
//			m_bElectricalKeyCreate = true;
//		}
//		break;
//	default:
//		break;
//	}
//}
//
//void CItemSpawn::Storage_Control_KeyCreate(void)
//{
//	m_nStorage_Control_key_number = rand() % 3;
//	switch (m_nStorage_Control_key_number)
//	{
//	case 0:
//		if (m_bControlKeyPosition[0] == false && m_bStorageKeyCreate == false)
//		{
//			CStorageKeyObject::Create(CONTROL_STORAGE_POSITION1, ZeroVector3);
//			m_bStoragePosition[0] = true;
//			m_bStorageKeyCreate = true;
//		}
//		if (m_bStoragePosition[0] == false && m_bControlKeyCreate == false)
//		{
//			CControlRoomKeyObject::Create(CONTROL_STORAGE_POSITION1, ZeroVector3);
//			m_bControlKeyPosition[0] = true;
//			m_bControlKeyCreate = true;
//		}
//		break;
//	case 1:
//		if (m_bControlKeyPosition[1] == false && m_bStorageKeyCreate == false)
//		{
//			CStorageKeyObject::Create(CONTROL_STORAGE_POSITION2, ZeroVector3);
//			m_bStoragePosition[1] = true;
//			m_bStorageKeyCreate = true;
//		}
//		if (m_bStoragePosition[1] == false && m_bControlKeyCreate == false)
//		{
//			CControlRoomKeyObject::Create(CONTROL_STORAGE_POSITION2, ZeroVector3);
//			m_bControlKeyPosition[1] = true;
//			m_bControlKeyCreate = true;
//		}
//		break;
//	case 2:
//		if (m_bControlKeyPosition[2] == false && m_bStorageKeyCreate == false)
//		{
//			CStorageKeyObject::Create(CONTROL_STORAGE_POSITION3, ZeroVector3);
//			m_bStoragePosition[2] = true;
//			m_bStorageKeyCreate = true;
//		}
//		if (m_bStoragePosition[2] == false && m_bControlKeyCreate == false)
//		{
//			CControlRoomKeyObject::Create(CONTROL_STORAGE_POSITION3, ZeroVector3);
//			m_bControlKeyPosition[2] = true;
//			m_bControlKeyCreate = true;
//		}
//		break;
//	case 3:
//		if (m_bControlKeyPosition[3] == false && m_bStorageKeyCreate == false)
//		{
//			CStorageKeyObject::Create(CONTROL_STORAGE_POSITION4, ZeroVector3);
//			m_bStoragePosition[3] = true;
//			m_bStorageKeyCreate = true;
//		}
//		if (m_bStoragePosition[3] == false && m_bControlKeyCreate == false)
//		{
//			CControlRoomKeyObject::Create(CONTROL_STORAGE_POSITION4, ZeroVector3);
//			m_bControlKeyPosition[3] = true;
//			m_bControlKeyCreate = true;
//		}
//		break;
//	default:
//		break;
//	}
//}

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

void CItemSpawn::PCKeyCreate(void)
{
	m_nPCNumber = rand() % 2;
	switch (m_nPCNumber)
	{
	case 0:
		CPCRoomKeyObject::Create(NEW_PC_POS1, ZeroVector3);
		break;
	case 1:
		CPCRoomKeyObject::Create(NEW_PC_POS2, ZeroVector3);
		break;
	default:
		break;
	}
}
