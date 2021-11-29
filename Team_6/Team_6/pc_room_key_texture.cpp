#include "main.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "scene_2d.h"
#include "pc_room_key_texture.h"

//=============================================================================
// コンストラクタ
// Author : Nikaido Taichi
//=============================================================================
CPCRoomKeyTexture::CPCRoomKeyTexture(PRIORITY Priority) : CScene2D(Priority)
{
}

//=============================================================================
// デストラクタ
// Author : Nikaido Taichi
//=============================================================================
CPCRoomKeyTexture::~CPCRoomKeyTexture()
{
}

//=============================================================================
// 生成処理関数
// Author : Nikaido Taichi
//=============================================================================
CPCRoomKeyTexture * CPCRoomKeyTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CPCRoomKeyTextureのポインタ
	CPCRoomKeyTexture *pPCRoomKey = nullptr;

	// nullcheck
	if (pPCRoomKey == nullptr)
	{
		// メモリ確保
		pPCRoomKey = new CPCRoomKeyTexture;

		// !nullcheck
		if (pPCRoomKey != nullptr)
		{
			// 初期化処理
			pPCRoomKey->Init(pos, size);
		}
	}
	// ポインタを返す
	return pPCRoomKey;
}

//=============================================================================
// 初期化処理関数
// Author : Nikaido Taichi
//=============================================================================
HRESULT CPCRoomKeyTexture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン2Dの初期化処理関数呼び出し
	CScene2D::Init(pos, size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_PC_ROOM_KEY));
	return S_OK;
}

//=============================================================================
// 終了処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPCRoomKeyTexture::Uninit(void)
{
	// シーン2Dの終了処理関数呼び出し
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPCRoomKeyTexture::Update(void)
{
	// シーン2Dの更新処理関数呼び出し
	CScene2D::Update();
}

//=============================================================================
// 描画処理関数
// Author : Nikaido Taichi
//=============================================================================
void CPCRoomKeyTexture::Draw(void)
{
	// シーン2Dの描画処理関数呼び出し
	CScene2D::Draw();
}
