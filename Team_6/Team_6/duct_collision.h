#ifndef _DUCT_COLLISON_H_
#define _DUCT_COLLISON_H_
//=============================================================================
// ダクトの判定 [duct_collision.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "model.h"
#include "object_door.h"
//=============================================================================
// 前方宣言
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// ドアの判定クラス
// Author : Sugawara Tsukasa
//=============================================================================
class CDuct_Collision : public CModel
{
public:
	// 種類
	enum TYPE
	{
		TYPE_NONE = -1,
		TYPE_LEFT,
		TYPE_RIGHT,
		TYPE_MAX
	};
	CDuct_Collision(PRIORITY Priority = PRIORITY_DUCT);					// コンストラクタ
	virtual ~CDuct_Collision();														// デストラクタ

	static CDuct_Collision *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type);	// 生成処理
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);							// 初期化処理
	virtual void Uninit(void);														// 終了処理
	virtual void Update(void);														// 更新処理
	virtual void Draw(void);														// 描画処理
	int GetType(void) { return m_Type; }											// タイプ取得関数
private:
	TYPE m_Type;	// 種類
};
#endif