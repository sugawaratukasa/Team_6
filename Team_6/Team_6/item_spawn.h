#ifndef _ITEM_SPAWN_H_
#define _ITEM_SPAWN_H_
//=============================================================================
//
// �A�C�e���������� [item_spawn.h]
// Author : Nikaido Taichi
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���錾
//=============================================================================

//=============================================================================
// �v���C���[�N���X
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
