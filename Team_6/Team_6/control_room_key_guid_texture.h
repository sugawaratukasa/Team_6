#ifndef _CONTROL_ROOM_KEY_GUID_TEXTURE_H_
#define _CONTROL_ROOM_KEY_GUID_TEXTURE_H_
//=============================================================================
//
// 制御室鍵説明のテクスチャヘッダー [control_key_guid_texture.h]
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
class CControlRoomKeyGuidTexture : public CScene2D
{
public:
	CControlRoomKeyGuidTexture(PRIORITY Priority = PRIORITY_UI);					// コンストラクタ
	~CControlRoomKeyGuidTexture();													// デストラクタ
	static CControlRoomKeyGuidTexture * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 生成処理関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);								// 初期化処理
	void Uninit(void);																// 終了処理
	void Update(void);																// プレイヤーの制御
	void Draw(void);																// 描画処理
private:
};
#endif
