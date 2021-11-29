#ifndef _OBJECT_PRISON_WALL_H_
#define _OBJECT_PRISON_WALL_H_
//=============================================================================
// 牢屋壁クラス [object_prison_wall.h]
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
class CPrison_Wall : public CObject
{
public:
	CPrison_Wall(PRIORITY Priority = PRIORITY_MAP);					// コンストラクタ
	~CPrison_Wall();												// デストラクタ
	static CPrison_Wall*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
private:
};
#endif