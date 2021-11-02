#include "door_pc_room.h"

CPCRoomDoor::CPCRoomDoor(PRIORITY Priority)
{
}

CPCRoomDoor::~CPCRoomDoor()
{
}

CPCRoomDoor * CPCRoomDoor::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CPCRoomKeyのポインタ
	CPCRoomDoor *pPCRoomDoor = nullptr;

	// nullcheck
	if (pPCRoomDoor == nullptr)
	{
		// メモリ確保
		pPCRoomDoor = new CPCRoomDoor;

		// !nullcheck
		if (pPCRoomDoor != nullptr)
		{
			// 初期化処理
			pPCRoomDoor->Init(pos, rot);
		}
	}
	// ポインタを返す
	return pPCRoomDoor;
}

HRESULT CPCRoomDoor::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ドアの初期化処理関数呼び出し
	CDoor::Init(pos, rot);
	// タイプを設定する
	SetType(CDoor::DOOR_PC_ROOM);
	return S_OK;
}

void CPCRoomDoor::Uninit(void)
{
	// ドアの終了処理関数呼び出し
	CDoor::Uninit();
}

void CPCRoomDoor::Update(void)
{
	// ドアの更新処理関数呼び出し
	CDoor::Update();
}

void CPCRoomDoor::Draw(void)
{
	// ドアの描画処理関数呼び出し
	CDoor::Draw();
}
