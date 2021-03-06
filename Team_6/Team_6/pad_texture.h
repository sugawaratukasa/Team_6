#ifndef _PAD_TEXTURE_H_
#define _PAD_TEXTURE_H_
//=============================================================================
//
// コントローラーテクスチャヘッダー [pad_texture.h]
// Author : Nikaido Taichi
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "scene_2d.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// 前方宣言
//=============================================================================

//=============================================================================
// プレイヤークラス
//=============================================================================
class CPadTexture : public CScene2D
{
public:
	CPadTexture(PRIORITY Priority = PRIORITY_UI);					// コンストラクタ
	~CPadTexture();													// デストラクタ
	static CPadTexture * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);				// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// プレイヤーの制御
	void Draw(void);												// 描画処理
private:
};
#endif
