//=============================================================================
// 監視カメラの判定 [security_camera_collision.cpp]
// Author : Sugawara Tsukasa
//=============================================================================
//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "security_camera_collision.h"
#include "manager.h"
#include "renderer.h"
#include "model_collision_box.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define COL_SIZE	(D3DXVECTOR3(600.0f,500.0f,100.0f))
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CSecurity_Camera_Collision::CSecurity_Camera_Collision(PRIORITY Priority) : CModel(Priority)
{
}
//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CSecurity_Camera_Collision::~CSecurity_Camera_Collision()
{
}
//=============================================================================
// 生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
CSecurity_Camera_Collision * CSecurity_Camera_Collision::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// CSecurity_Camera_Collisionのポインタ
	CSecurity_Camera_Collision * pSecurity_Camera_Collision = nullptr;

	// nullptrの場合
	if (pSecurity_Camera_Collision == nullptr)
	{
		// メモリ確保
		pSecurity_Camera_Collision = new CSecurity_Camera_Collision;

		// nullptrでない場合
		if (pSecurity_Camera_Collision != nullptr)
		{
			// 初期化処理
			pSecurity_Camera_Collision->Init(pos, rot);
		}
	}
	return nullptr;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CSecurity_Camera_Collision::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 初期化処理
	CModel::Init(pos, rot);

	// サイズ設定
	SetSize(COL_SIZE);

	// 判定確認用
	//CModelCollisionBox::Create(pos, rot, this);
	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CSecurity_Camera_Collision::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CSecurity_Camera_Collision::Update(void)
{

}
//=============================================================================
// 描画処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CSecurity_Camera_Collision::Draw(void)
{

}
//=============================================================================
// カメラ使用処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CSecurity_Camera_Collision::CameraUse(int nPlayer)
{
	// レンダラー取得
	CRenderer *pRenderer = CManager::GetRenderer();

	// nullptrでない場合
	if (pRenderer != nullptr)
	{
		// カメラ使用処理
		pRenderer->SwitchCam(nPlayer);
	}
}