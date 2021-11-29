//=============================================================================
//
// テクスチャの管理クラス [texture.cpp]
// Author : Sugawara Tsukasa
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "texture.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CTexture::CTexture()
{
	memset(m_apTexture, 0, sizeof(m_apTexture));
}

//=============================================================================
// デストラクタ
//=============================================================================
CTexture::~CTexture()
{
	for (int nCount = 0; nCount < TEXTURE_TYPE_NUM_MAX; nCount++)
	{
		// 名前データのクリア
		m_aTexFileName[nCount].clear();
	}
}

//=============================================================================
// インスタンス生成
//=============================================================================
CTexture * CTexture::Create(void)
{
	// メモリ確保
	CTexture *pTexture = new CTexture;

	// nullcheck
	if (pTexture)
	{
		// 初期値
		pTexture->SetTextureName();
		return pTexture;
	}
	return pTexture;
}

//=============================================================================
// テクスチャの名前を設定
//=============================================================================
HRESULT CTexture::SetTextureName(void)
{
	// 通常テクスチャ
	m_aTexFileName[TEXTURE_TYPE_NUM_NORMAL] =
	{
		{"data/Texture/floor.jpg"},
		{"data/Texture/Sceneframe.png"},
		{"data/Texture/time_UI_frame.png"},
		{"data/Texture/time_UI_guage.png" },
		{"data/Texture/time_UI_guage2.png"},
		{"data/Texture/number_01.png"},
		{ "data/Texture/UI_frameI.png" },
		{ "data/Texture/baton.png" },
		{"data/Texture/Key_Item_PCroom.png"},
		{ "data/Texture/Key_Item_Warehouse.png" },
		{ "data/Texture/Key_Item_Prison.png" },
		{ "data/Texture/Key_Item_Jailer_room.png" },
		{"data/Texture/Map_ItemUI.png"},
		{ "data/Texture/Button_Start.png" },		// スタートボタン
		{ "data/Texture/Button_Ranking.png" },		// ランキングボタン
		{ "data/Texture/Button_Exit.png" },			// 終了ボタン
		{ "data/Texture/Button_ReturnGame.png" },	// ゲームに戻るボタン
		{"data/Texture/Button_ReturnTitle.png"},	// タイトルに戻るボタン
		{ "data/Texture/Button_HowTo.png" },		// 操作説明ボタン
		{ "data/Texture/bg_title.png" },			// タイトル背景
		{ "data/Texture/title_logo.png" },			// タイトルロゴ
		{"data/Texture/UI_frameI_Select.png"},
		{"data/Texture/map_texture.png"},
		{"data/Texture/y.png"}
	};

	// 分割テクスチャ
	m_aTexFileName[TEXTURE_TYPE_NUM_SEPARATE] =
	{

	};

	return E_NOTIMPL;
}

//=============================================================================
// 全てのテクスチャロード
//=============================================================================
void CTexture::LoadAll(void)
{
	// 通常テクスチャ
	NormalTexLoad();

	// 分割テクスチャ
	SeparateTexLoad();
}

//=============================================================================
// 全てのテクスチャアンロード
//=============================================================================
void CTexture::UnLoadAll(void)
{
	// 通常テクスチャ
	NormalTexUnLoad();

	// 分割テクスチャ
	SeparateTexUnLoad();
}

//=============================================================================
// テクスチャロード
//=============================================================================
HRESULT CTexture::NormalTexLoad(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	size_t size = m_aTexFileName[TEXTURE_TYPE_NUM_NORMAL].size();

	// テクスチャの読み込み
	for (size_t nCount = 0; nCount < size; nCount++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aTexFileName[TEXTURE_TYPE_NUM_NORMAL][nCount].data(), &m_apTexture[nCount]);
	}

	return S_OK;
}

//=============================================================================
// テクスチャアンロード
//=============================================================================
void CTexture::NormalTexUnLoad(void)
{
	for (int nCount = 0; nCount < TEXTURE_NUM_MAX; nCount++)
	{
		if (m_apTexture[nCount] != nullptr)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = nullptr;
		}
	}
}

//=============================================================================
// 分割テクスチャのロード
//=============================================================================
HRESULT CTexture::SeparateTexLoad(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	size_t size = m_aTexFileName[TEXTURE_TYPE_NUM_SEPARATE].size();

	// 分割テクスチャの読み込み
	for (size_t nCount = 0; nCount < size; nCount++)
	{
		D3DXCreateTextureFromFile(pDevice, m_aTexFileName[TEXTURE_TYPE_NUM_SEPARATE][nCount].data(), &m_apSeparateTexture[nCount].pSeparateTexture);
	}
	return S_OK;
}

//=============================================================================
// 分割テクスチャのアンロード
//=============================================================================
void CTexture::SeparateTexUnLoad(void)
{
	// テクスチャの解放
	for (int nCount = 0; nCount < SEPARATE_TEX_MAX; nCount++)
	{
		if (m_apSeparateTexture[nCount].pSeparateTexture != nullptr)
		{
			m_apSeparateTexture[nCount].pSeparateTexture->Release();
			m_apSeparateTexture[nCount].pSeparateTexture = nullptr;
		}
	}
}

//=============================================================================
// テクスチャ情報
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEXTURE_TYPE Tex_Num)
{
	if (Tex_Num < TEXTURE_NUM_MAX)
	{
		if (m_apTexture[Tex_Num] != nullptr)
		{
			return m_apTexture[Tex_Num];
		}
	}

	return nullptr;
}

//=============================================================================
// 分割テクスチャ情報
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetSeparateTexture(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// 配列より小さかったら
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// NULLcheck
		if (m_apSeparateTexture[SepaTex_Type].pSeparateTexture != nullptr)
		{
			// テクスチャ情報
			return m_apSeparateTexture[SepaTex_Type].pSeparateTexture;
		}
	}

	return nullptr;
}

//=============================================================================
// 分割テクスチャの情報
//=============================================================================
D3DXVECTOR2 CTexture::GetSparateTexInfo(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// 配列より小さかったら
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// テクスチャ情報
		return m_apSeparateTexture[SepaTex_Type].m_TexInfo;
	}

	return D3DXVECTOR2(0.0f, 0.0f);
}

//=============================================================================
// 分割テクスチャのループフラグ
//=============================================================================
bool CTexture::GetSparateTexLoop(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// 配列より小さかったら
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// テクスチャ情報
		return m_apSeparateTexture[SepaTex_Type].bLoop;
	}

	return false;
}