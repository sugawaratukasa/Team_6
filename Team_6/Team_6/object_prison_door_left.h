#ifndef _PRISON_DOOR_LEFT_H_
#define _PRISON_DOOR_LEFT_H_
//=============================================================================
// 牢屋の扉 [object_prison_door_right.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "object_door.h"

//=============================================================================
// 牢屋の扉クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CPrison_Door_Left : public CDoor
{
public:
	CPrison_Door_Left(PRIORITY Priority = PRIORITY_MODEL);				// コンストラクタ
	~CPrison_Door_Left();													// デストラクタ
	static CPrison_Door_Left *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
	void Open(void);												// 開く処理
	void Close(void);												// 閉じる処理
private:
};
#endif