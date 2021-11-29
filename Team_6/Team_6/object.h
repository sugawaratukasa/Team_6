#ifndef _OBJECT_H_
#define _OBJECT_H_
//=============================================================================
// オブジェクト [object.h]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルード
// Author : Sugawara Tsukasa
//=============================================================================
#include "model.h"

//=============================================================================
// オブジェクトクラス
// Author : Sugawara Tsukasa
//=============================================================================
class CObject : public CModel
{
public:
	// 種類
	enum TYPE
	{
		TYPE_NONE = -1,
		TYPE_WALL,
		TYPE_SWITCH,
		TYPE_MAX
	};
	CObject(PRIORITY Priority = PRIORITY_MODEL);				// コンストラクタ
	virtual ~CObject();											// デストラクタ

	static CObject *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成処理
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		// 初期化処理
	virtual void Uninit(void);									// 終了処理
	virtual void Update(void);									// 更新処理
	virtual void Draw(void);									// 描画処理
	void SetType(TYPE type) { m_Type = type; }					// 種類の設定
	TYPE GetType(void) { return m_Type; }						// 種類取得
private:
	TYPE m_Type;	// 種類
};
#endif