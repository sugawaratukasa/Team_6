//=============================================================================
//
// 看守の感情クラス [jailer_emotion.cpp]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//マクロ定義
//=============================================================================
#define EMOTION_SIZE D3DXVECTOR3(100.0f,100.0f,0.0f)	//サイズ

//=============================================================================
//インクルードファイル
//=============================================================================
#include "jailer_emotion.h"
#include "texture.h"
#include "resource_manager.h"
#include "manager.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CJailer_Emotion::CJailer_Emotion()
{
	m_eEmotionType = EMOTION_TYPE_NONE;
}

//=============================================================================
//デストラクタ
//=============================================================================
CJailer_Emotion::~CJailer_Emotion()
{
}

//=============================================================================
//クリエイト処理
//=============================================================================
CJailer_Emotion * CJailer_Emotion::Create(const D3DXVECTOR3 pos)
{
	CJailer_Emotion *pEmotion = nullptr;

	//インスタンス生成
	pEmotion = new CJailer_Emotion;

	if (pEmotion)
	{
		//初期化処理
		pEmotion->Init(pos, EMOTION_SIZE);
	}

	return pEmotion;
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CJailer_Emotion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//基底クラスの初期化
	CBillboard::Init(pos, size);

	//テクスチャクラスのポインタの取得
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

	//テクスチャの設定
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_EMOTION_ANGER));

	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CJailer_Emotion::Uninit(void)
{
	//基底クラスの終了
	CBillboard::Uninit();
}

//=============================================================================
//更新処理
//=============================================================================
void CJailer_Emotion::Update(void)
{
	//基底クラスの更新
	CBillboard::Update();
}

//=============================================================================
//描画処理
//=============================================================================
void CJailer_Emotion::Draw(void)
{
	if (m_eEmotionType != EMOTION_TYPE_NONE)
	{
		//基底クスの描画処理
		CBillboard::Draw();
	}
}

//=============================================================================
//位置の設定処理
//=============================================================================
void CJailer_Emotion::SetPosition(D3DXVECTOR3 Pos)
{
	Pos.y = 300.0f;
	SetPos(Pos);
}

//=============================================================================
//感情の設定
//=============================================================================
void CJailer_Emotion::SetEmotion(const EMOTION_TYPE emotion)
{
	m_eEmotionType = emotion;

	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

	switch (m_eEmotionType)
	{
	case CJailer_Emotion::EMOTION_TYPE_QUESTION:
		
		//テクスチャの設定
		BindTexture(pTexture->GetTexture(CTexture::TEXTURE_EMOTION_QUESTION));
		break;

	case CJailer_Emotion::EMOTION_TYPE_ANGER:
		
		//テクスチャの設定
		BindTexture(pTexture->GetTexture(CTexture::TEXTURE_EMOTION_ANGER));
		break;

	default:
		break;
	}
}