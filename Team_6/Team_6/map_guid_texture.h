#ifndef _MAP_GUID_TEXTURE_H_
#define _MAP_GUID_TEXTURE_H_
//=============================================================================
//
// 警棒説明テクスチャ [map_guid_texture.h]
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
class CMapGuidTexture : public CScene2D
{
public:
	CMapGuidTexture(PRIORITY Priority = PRIORITY_GUID_TEXTURE);						// コンストラクタ
	~CMapGuidTexture();														// デストラクタ
	static CMapGuidTexture * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// 生成処理関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);						// 初期化処理
	void Uninit(void);														// 終了処理
	void Update(void);														// プレイヤーの制御
	void Draw(void);														// 描画処理
private:
};
#endif
