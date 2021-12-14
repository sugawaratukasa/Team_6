#include "item_guid_prison_key.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "prison_key_texture.h"
#include "keyboard.h"
#include "joypad.h"

CPrisonKeyGuid::CPrisonKeyGuid(PRIORITY Priority)
{
	m_pPrisonKeyTexture = nullptr;
}

CPrisonKeyGuid::~CPrisonKeyGuid()
{
}

CPrisonKeyGuid * CPrisonKeyGuid::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CJailerKeyTextureのポインタ
	CPrisonKeyGuid *pPrisonKeyGuid = nullptr;

	// nullcheck
	if (pPrisonKeyGuid == nullptr)
	{
		// メモリ確保
		pPrisonKeyGuid = new CPrisonKeyGuid;

		// !nullcheck
		if (pPrisonKeyGuid != nullptr)
		{
			// 初期化処理
			pPrisonKeyGuid->Init(pos, size);
		}
	}
	// ポインタを返す
	return pPrisonKeyGuid;
}

HRESULT CPrisonKeyGuid::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// シーン2Dの初期化処理関数呼び出し
	CScene2D::Init(pos, size);
	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_JAILER_KEY));
	if (m_pPrisonKeyTexture == nullptr)
	{
		m_pPrisonKeyTexture = CPrisonKeyTexture::Create(ZeroVector3, ZeroVector3);
	}
	return S_OK;
}

void CPrisonKeyGuid::Uninit(void)
{
	CScene2D::Uninit();
	if (m_pPrisonKeyTexture != nullptr)
	{
		m_pPrisonKeyTexture->Uninit();
		m_pPrisonKeyTexture = nullptr;
	}
}

void CPrisonKeyGuid::Update(void)
{
	CScene2D::Update();
	if (m_pPrisonKeyTexture != nullptr)
	{
		m_pPrisonKeyTexture->Update();
	}
	Input();
}

void CPrisonKeyGuid::Draw(void)
{
	CScene2D::Draw();
	if (m_pPrisonKeyTexture != nullptr)
	{
		m_pPrisonKeyTexture->Draw();
	}
}

void CPrisonKeyGuid::Input(void)
{
	// キーボード取得
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	// パッド取得
	CInputJoypad * pJoypad = CManager::GetJoypad();

	if (pKeyboard->GetTrigger(DIK_RETURN))
	{
		Uninit();
	}
}
