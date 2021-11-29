#ifndef _OBJECT_PRISON_DOOR_RIGHT_H_
#define _OBJECT_PRISON_DOOR_RIGHT_H_
//=============================================================================
// 牢屋ドアクラス [object_prison_door_right.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// 牢屋壁クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CPrison_Door_Right : public CObject
{
public:
	CPrison_Door_Right(PRIORITY Priority = PRIORITY_MAP);				// コンストラクタ
	~CPrison_Door_Right();												// デストラクタ
	static CPrison_Door_Right*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);						// 初期化処理
	void Uninit(void);													// 終了処理
	void Update(void);													// 更新処理
	void Draw(void);													// 描画処理
private:
};
#endif