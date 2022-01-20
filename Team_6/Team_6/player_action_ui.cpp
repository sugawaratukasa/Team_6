//=============================================================================
// プレイヤー行動UI [player_action_ui_1.cpp]
// Author : Sugawara Tsukasa
//=============================================================================

//=============================================================================
// インクルードファイル
// Author : Sugawara Tsukasa
//=============================================================================
#include "player_action_ui.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"
#include "resource_manager.h"
//=============================================================================
// マクロ定義
// Author : Sugawara Tsukasa
//=============================================================================
#define PLAYER1_POS_1	(D3DXVECTOR3(SCREEN_WIDTH / 4.0f,SCREEN_HEIGHT / 2.0f + 100.0f,0.0f))
#define PLAYER1_POS_2	(D3DXVECTOR3(SCREEN_WIDTH / 4.0f,SCREEN_HEIGHT / 2.0f + 150,0.0f))
#define PLAYER2_POS_1	(D3DXVECTOR3(SCREEN_WIDTH / 1.3f,SCREEN_HEIGHT / 2.0f + 100.0f,0.0f))
#define PLAYER2_POS_2	(D3DXVECTOR3(SCREEN_WIDTH / 1.3f,SCREEN_HEIGHT / 2.0f + 150.0f,0.0f))
#define SIZE_2D	(D3DXVECTOR3(361.0f, 87.0f,0.0f))
#define COL		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
//=============================================================================
// コンストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer_Action_UI::CPlayer_Action_UI()
{
	memset(m_apScene2D, NULL, sizeof(m_apScene2D));
	m_nPlayer_Type		= PLYER_TYPE_NONE;
	m_bInteract			= false;
	m_bItemGet			= false;
}
//=============================================================================
// デストラクタ
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer_Action_UI::~CPlayer_Action_UI()
{
}
//=============================================================================
// 生成処理関数
// Author : Sugawara Tsukasa
//=============================================================================
CPlayer_Action_UI * CPlayer_Action_UI::Create(int player_type)
{
	// CPlayer_Action_UIのポインタ
	CPlayer_Action_UI *pPlayer_Action_UI = nullptr;

	// nullcheck
	if (pPlayer_Action_UI == nullptr)
	{
		// メモリ確保
		pPlayer_Action_UI = new CPlayer_Action_UI;

		// !nullcheck
		if (pPlayer_Action_UI != nullptr)
		{
			// タイプ代入
			pPlayer_Action_UI->m_nPlayer_Type = player_type;

			// 初期化処理
			pPlayer_Action_UI->Init();
		}
	}
	// ポインタを返す
	return pPlayer_Action_UI;
}
//=============================================================================
// 初期化処理関数
// Author : Sugawara Tsukasa
//=============================================================================
HRESULT CPlayer_Action_UI::Init(void)
{
	return S_OK;
}
//=============================================================================
// 終了処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer_Action_UI::Uninit(void)
{
	// 最大数繰り返す
	for (int nCnt = ZERO_INT; nCnt < TYPE_MAX; nCnt++)
	{
		// !nullcheck
		if (m_apScene2D[nCnt] != nullptr)
		{
			m_apScene2D[nCnt]->Uninit();
			m_apScene2D[nCnt] = nullptr;
		}
	}
}
//=============================================================================
// 更新処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer_Action_UI::Update(void)
{
	// UI生成管理処理
	UI_Create_Management();
}
//=============================================================================
// UI生成管理処理関数
// Author : Sugawara Tsukasa
//=============================================================================
void CPlayer_Action_UI::UI_Create_Management(void)
{
	// アイテムを取得できる場合
	if (m_bItemGet == true)
	{
		// nullptrの場合
		if (m_apScene2D[TYPE_X] == nullptr)
		{
			// player1の場合
			if (m_nPlayer_Type == PLYER_TYPE_1)
			{
				// UI生成
				m_apScene2D[TYPE_X] = CScene2D::Create(PLAYER1_POS_1, SIZE_2D);
			}
			// player2の場合
			if (m_nPlayer_Type == PLYER_TYPE_2)
			{
				// UI生成
				m_apScene2D[TYPE_X] = CScene2D::Create(PLAYER2_POS_1, SIZE_2D);
			}
				// テクスチャの設定
				CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
				m_apScene2D[TYPE_X]->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_PICKUP));

				// 色設定
				m_apScene2D[TYPE_X]->SetCol(COL);
			
		}
	}
	// カメラを使用できる場合
	if (m_bInteract == true)
	{
		// nullptrの場合
		if (m_apScene2D[TYPE_A] == nullptr)
		{
			// player1の場合
			if (m_nPlayer_Type == PLYER_TYPE_1)
			{
				// UI生成
				m_apScene2D[TYPE_A] = CScene2D::Create(PLAYER1_POS_1, SIZE_2D);
			}
			// player2の場合
			if (m_nPlayer_Type == PLYER_TYPE_2)
			{
				// UI生成
				m_apScene2D[TYPE_A] = CScene2D::Create(PLAYER2_POS_1, SIZE_2D);
			}
			// !nullcheck
			if (m_apScene2D[TYPE_A] != nullptr)
			{
				// テクスチャの設定
				CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
				m_apScene2D[TYPE_A]->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_INTERACT));

				// 色設定
				m_apScene2D[TYPE_A]->SetCol(COL);
			}
		}
	}
	// カメラ、ドア、ダクトがfalseの場合
	if (m_bInteract == false)
	{
		// nullptrでない場合
		if (m_apScene2D[TYPE_A] != nullptr)
		{
			// 終了
			m_apScene2D[TYPE_A]->Uninit();

			// nullptr代入
			m_apScene2D[TYPE_A] = nullptr;
		}
	}
	// アイテムがfalseの場合
	if (m_bItemGet == false)
	{
		// nullptrでない場合
		if (m_apScene2D[TYPE_X] != nullptr)
		{
			// 終了
			m_apScene2D[TYPE_X]->Uninit();

			// nullptr代入
			m_apScene2D[TYPE_X] = nullptr;
		}
	}
	// アイテムとインタラクトの判定がある場合
	if (m_bItemGet == true && m_bInteract == true)
	{
		// X,Aがnullptrの場合
		if (m_apScene2D[TYPE_A] != nullptr && m_apScene2D[TYPE_X] != nullptr)
		{
			// player1の場合
			if (m_nPlayer_Type == PLYER_TYPE_1)
			{
				// UI生成
				m_apScene2D[TYPE_X]->SetPosition(PLAYER1_POS_1);
				m_apScene2D[TYPE_X]->SetVertex();

				// UI生成
				m_apScene2D[TYPE_A]->SetPosition(PLAYER1_POS_2);
				m_apScene2D[TYPE_A]->SetVertex();
			}
			// player2の場合
			if (m_nPlayer_Type == PLYER_TYPE_2)
			{
				// UI生成
				m_apScene2D[TYPE_X]->SetPosition(PLAYER2_POS_1);
				m_apScene2D[TYPE_X]->SetVertex();

				// UI生成
				m_apScene2D[TYPE_A]->SetPosition(PLAYER2_POS_2);
				m_apScene2D[TYPE_A]->SetVertex();
			}
		}
	}
}

void CPlayer_Action_UI::SetInteract(bool bCameraInteract)
{
	m_bInteract = bCameraInteract;
}

void CPlayer_Action_UI::SetbItemGet(bool bItemGet)
{
	m_bItemGet = bItemGet;
}
