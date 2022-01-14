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
	void JailerKeyCreate(void);
	void CameraKeyCreate(void);
	void ControlKeyCreate(void);
	void ElectricalKeyCreate(void);
	void StorageKeyCreate(void);

	int m_nJailerNumber;
	int m_nCameraNumber;
	int m_nControlNumber;
	int m_nElectricalNumber;
	int m_nStorageNumber;
};
#endif
