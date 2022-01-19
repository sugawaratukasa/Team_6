#ifndef JAILER_EMOTION
#define JAILER_EMOTION
//=============================================================================
//
// 看守の感情クラス [jailer_emotion.h]
// Author : Yamada Ryota
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "billboard.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define JAILER_EMOTION_SIZE D3DXVECTOR3(100.0f,100.0f,0.0f)	//サイズ
#define CAMERA_EMOTION_SIZE D3DXVECTOR3(80.0f,80.0f,0.0f)	//サイズ
#define JAILER_CORRECTION 300.0f
#define CAMERA_CORRECTION 320.0f

//=============================================================================
//看守感情クラス
//=============================================================================
class CJailer_Emotion : public CBillboard
{
public:
	//=========================================================================
	//感情タイプ
	//=========================================================================
	enum EMOTION_TYPE
	{
		EMOTION_TYPE_NONE = 0,	//通常状態
		EMOTION_TYPE_QUESTION,	//疑問状態
		EMOTION_TYPE_ANGER,		//怒り状態
		EMOTION_TYPE_MAX,
	};

	//=========================================================================
	//メンバ関数宣言
	//=========================================================================
	CJailer_Emotion();
	~CJailer_Emotion();

	static CJailer_Emotion *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size,const float fCorrection);	//クリエイト処理

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//初期化処理
	void Uninit(void);									//終了処理
	void Update(void);									//更新処理
	void Draw(void);									//描画処理

	void SetPosition(D3DXVECTOR3 Pos);													//位置設定処理
	void SetEmotion(const EMOTION_TYPE emotion);										//タイプ設定処理
	void SetCorrectionPos(const float fCorrection) { m_fCorrectionPos = fCorrection; }	//高さの補正値の設定
	void SetAutoOut(bool bIsUpdate) { m_bIsAutoOut = bIsUpdate; }						//自動フェードアウトするかどうか

private:
	void AutoOut(void);	//自動フェードアウト処理

	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	EMOTION_TYPE m_eEmotionType;	//エモーションの種類
	float m_fCorrectionPos;			//高さの補正値
	bool m_bIsAutoOut;				//自動フェードアウトするかどうか
	int m_nOutTime;					//タイマー
};
#endif // !JAILER_EMOTION
