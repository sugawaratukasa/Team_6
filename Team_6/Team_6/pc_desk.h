#ifndef _PC_DESK_H_
#define _PC_DESK_H_
//=============================================================================
// PCの机 [pc_desk.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "object.h"

//=============================================================================
// PCの机クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CPC_Desk : public CObject
{
public:
	CPC_Desk(PRIORITY Priority = PRIORITY_MAP);					// コンストラクタ
	~CPC_Desk();													// デストラクタ
	static CPC_Desk*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);					// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
private:
};
#endif
