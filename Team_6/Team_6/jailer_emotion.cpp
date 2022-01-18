//=============================================================================
//
// 看守の感情クラス [jailer_emotion.cpp]
// Author : Yamada Ryota
//
//=============================================================================

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
	m_fCorrectionPos = ZERO_FLOAT;
	m_bIsAutoOut = false;
	m_nOutTime = ZERO_INT;
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
CJailer_Emotion * CJailer_Emotion::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const float fCorrection)
{
	CJailer_Emotion *pEmotion = nullptr;

	//インスタンス生成
	pEmotion = new CJailer_Emotion;

	if (pEmotion)
	{
		pEmotion->SetCorrectionPos(fCorrection);

		//初期化処理
		pEmotion->Init(pos, size);
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

	SetPosition(pos);

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
	if (m_bIsAutoOut)
	{
		AutoOut();
	}
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
	Pos.y = m_fCorrectionPos;

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

void CJailer_Emotion::AutoOut(void)
{
	if (m_eEmotionType == EMOTION_TYPE_NONE)
	{
		return;
	}

	m_nOutTime++;

	if (m_nOutTime >= 600)
	{
		SetEmotion(EMOTION_TYPE_NONE);

		m_nOutTime = ZERO_INT;
	}
}
