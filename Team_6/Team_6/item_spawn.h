#ifndef _ITEM_SPAWN_H_
#define _ITEM_SPAWN_H_
//=============================================================================
//
// アイテム生成処理 [item_spawn.h]
// Author : Nikaido Taichi
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// 前方宣言
//=============================================================================

//=============================================================================
// プレイヤークラス
//=============================================================================
class CItemSpawn
{
public:
	CItemSpawn();
	~CItemSpawn();
	static CItemSpawn * Create(void);
	HRESULT Init(void);
	void Update(void);
private:
	//void PC_Electrical_key_Create(void);
	//void Storage_Control_KeyCreate(void);
	void JailerKeyCreate(void);
	void CameraKeyCreate(void);
	void ControlKeyCreate(void);
	void ElectricalKeyCreate(void);
	void PCKeyCreate(void);

	//int m_nPC_Electrical_key_number;
	//bool m_bPCKeyPosition[4];
	//bool m_bPCKeyCreate;
	//bool m_bElectricalKeyPosition[4];
	//bool m_bElectricalKeyCreate;

	//int m_nStorage_Control_key_number;
	//bool m_bStoragePosition[4];
	//bool m_bStorageKeyCreate;
	//bool m_bControlKeyPosition[4];
	//bool m_bControlKeyCreate;

	int m_nJailerNumber;
	int m_nCameraNumber;
	int m_nControlNumber;
	int m_nElectricalNumber;
	int m_nPCNumber;
};
#endif
