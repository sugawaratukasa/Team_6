#ifndef _ELECTRICAL_ROOM_KEY_GUID_TEXTURE_H_
#define _ELECTRICAL_ROOM_KEY_GUID_TEXTURE_H_
//=============================================================================
//
// 電気室鍵の説明テクスチャ [electrical_room_key_texture.h]
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
class CElectricalRoomKeyGuidTexture : public CScene2D
{
public:
	CElectricalRoomKeyGuidTexture(PRIORITY Priority = PRIORITY_TEXTURE);						// コンストラクタ
	~CElectricalRoomKeyGuidTexture();													// デストラクタ
	static CElectricalRoomKeyGuidTexture * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 生成処理関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);									// 初期化処理
	void Uninit(void);																	// 終了処理
	void Update(void);																	// プレイヤーの制御
	void Draw(void);																	// 描画処理
private:
};
#endif
