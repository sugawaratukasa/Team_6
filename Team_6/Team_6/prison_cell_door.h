#ifndef _PRISON_CELL_DOOR_
#define _PRISON_CELL_DOOR_
//=============================================================================
// 独房の扉 [prison_cell_door.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "object_door.h"
#include "player.h"
//=============================================================================
// 前方宣言
// Author : Sugawara Tsukasa
//=============================================================================
class CPlayer;
//=============================================================================
// 独房の扉クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CPrison_Cell_Door : public CDoor
{
public:
	CPrison_Cell_Door(PRIORITY Priority = PRIORITY_MODEL);									// コンストラクタ
	~CPrison_Cell_Door();																	// デストラクタ
	static CPrison_Cell_Door *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CPlayer *pPlayer);	// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);											// 初期化処理
	void Uninit(void);																		// 終了処理
	void Update(void);																		// 更新処理
	void Draw(void);																		// 描画処理
	void Push(void);																		// ボタンが押された
private:
	CPlayer *m_pPlayer;	// CPlayerのポインタ
};
#endif